#include <iostream>
#include <stdexcept>

#include "simplegl.hpp"

namespace sgl {

    // anonymous namespace to protect these values from being set by outside
    // while still allowing access within SimpleGL implementation
    namespace {
        // -- camera frame
        glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
        glm::vec3 camera_front(0.0f, 0.0f, -1.0f);
        glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
        // yaw is initialized to -90 degrees since a yaw of 0 results in a direction
        // vector pointing to the right, so we initially rotate a bit to the left.
        float yaw = -90.0f;
        float pitch = 0.0f;
        float fov = 45.0f;
        float last_x = 0.0f;
        float last_y = 0.0f;
        // -- lighting
        glm::vec3 light_pos(6.2f, 7.0f, 5.0f);
        bool shadow_enabled = true;
        // -- cursor
        bool first_mouse = true;
        // -- timing
        float delta_time = 0.0f; // time between current frame and last frame
        float last_frame = 0.0f;
        double frame_rate = 60; // dummy initial value
        double smoothing = 0.5; // initial smoothing
        std::chrono::milliseconds delta_frame_milli;
        // -- key control
        bool at_shape_level = true;
        std::vector<ObjType> obj_types;
        int type_idx = 0;
        int obj_count = 0;
        BaseObj *curr_obj = nullptr;
        int instance_idx = 0;
        // -- objects
        std::unordered_map<ObjType, BaseObj *> obj_map;
    }

    // Note: either both of the shaders are default or neither are default
    Scene::Scene(char *vs, char *fs, int width, int height, bool use_full_ctrl) {
        // glfw: initialize and configure
        glfwSetErrorCallback(error_callback);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    #ifdef __APPLE__
        // uncomment this statement to fix compilation on OS X
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    #endif

        // glfw window creation
        scr_width = width;
        scr_height = height;
        window = glfwCreateWindow(scr_width, scr_height, "SimpleGL", nullptr, nullptr);
        glfwGetFramebufferSize(window, &scr_width, &scr_height);
        last_x = (float) scr_width / 2.0;
        last_y = (float) scr_height / 2.0;
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            abort();
        }
        glfwMakeContextCurrent(window);
        if (use_full_ctrl) {
            glfwSetKeyCallback(window, key_callback);
        }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            abort();
        }
        
        // configure global opengl state
        glEnable(GL_DEPTH_TEST);
        
        // build and compile our shader program
        if (vs && fs) {
            light_shader = new Shader(vs, fs);
        } else {
            light_shader = new Shader(ShaderType::light);
        }
        depth_shader = new Shader(ShaderType::depth);
        
        // configure depth map FBO
        glGenFramebuffers(1, &depth_map_fbo);
        // create depth texture
        glGenTextures(1, &depth_map);
        glBindTexture(GL_TEXTURE_2D, depth_map);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Scene::~Scene() {
        // Clean up obj pointers.
        for (auto& entry : obj_map) {
            delete entry.second;
        }
        // Delete shaders.
        delete light_shader;
        delete depth_shader;
        // glfw: terminate, clearing all previously allocated GLFW resources.
        glfwTerminate();
    }

    ObjId Scene::add_obj(ObjType t, const Color c, ObjParams params) {
        int id = 0;
        BaseObj *obj_ptr;
        if (obj_map.find(t) != obj_map.end()) { // contains(s) is c++20
            // adding an instance of this shape to the scene
            obj_ptr = obj_map[t];
            if (std::holds_alternative<Shape>(t)
                && std::get<Shape>(t) == Shape::composite) {
                id = obj_ptr->add_instance(c, params.comp);
            } else {
                id = obj_ptr->add_instance(c);
            }
        } else {
            // first time adding this shape to the scene
            if (std::holds_alternative<Shape>(t)
                && std::get<Shape>(t) == Shape::composite) {
                obj_ptr = new Composite();
                id = obj_ptr->add_instance(c, params.comp);
            } else {
                auto res = createGLPObj(t, params);
                if (std::holds_alternative<std::vector<double>>(res)) {
                    obj_ptr = new Mesh(std::get<std::vector<double>>(res), c);
                    obj_map.insert(std::make_pair(t, obj_ptr));
                } else {
                    // consideration: the user needs to use throw-try-catch 
                    // to handle the error case themselves
                    throw std::runtime_error{
                            std::get<std::error_condition>(res).message()};
                }
            }
        }
        return ObjId(id, obj_ptr);
    }

    void Scene::remove_obj_all(ObjType t) {
        if (obj_map.find(t) != obj_map.end()) { // contains(s) is c++20
            delete obj_map[t];
            obj_map.erase(t);
        }
    }

    std::error_condition Scene::render() {
        if (obj_map.empty()) {
            std::cout << "Current scene has nothing to render.\n";
            return make_SimpleGL_error_condition(SIMPLEGL_EMPTY_SCENE);
        } else {
            for (auto& entry : obj_map) {
                obj_types.push_back(entry.first);
            }
            curr_obj = obj_map[obj_types[type_idx]];
            obj_count = curr_obj->count();
        }
        
        // render loop
        while (!glfwWindowShouldClose(window)) {
            // start measuring frame time
            auto t0 = std::chrono::high_resolution_clock::now();
            // per-frame time logic
            float current_frame = glfwGetTime();
            delta_time = current_frame - last_frame;
            last_frame = current_frame;

            // input
            process_input(window);
            
            // start rendering
            glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            float near_plane = 1.0f, far_plane = 17.5f;
            glm::mat4 light_pojection = glm::ortho(
                -10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            glm::mat4 light_view = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                               glm::vec3( 0.0f, 0.0f,  0.0f),
                                               glm::vec3( 0.0f, 1.0f,  0.0f));
            glm::mat4 light_space_matrix = light_pojection * light_view;
            
            // 1. render shadows if enabled
            if (shadow_enabled) {
                depth_shader->use();
                depth_shader->setMat4("lightSpaceMatrix", light_space_matrix);
                glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
                glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
                glClear(GL_DEPTH_BUFFER_BIT);
                render_meshes(depth_shader);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                light_shader->setInt("shadowMap", 0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, depth_map);
            }
            
            // 2. render scene as normal using the generated depth/shadow map
            glViewport(0, 0, scr_width, scr_height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            light_shader->use();
            glCullFace(GL_FRONT);
            // (note that in this case matrices below could change every frame)
            // pass projection matrix to shader
            glm::mat4 projection = glm::perspective(
                glm::radians(fov), (float)scr_width/(float)scr_height, 0.1f, 100.0f);
            light_shader->setMat4("projection", projection);
            // pass camera/view transformation to shade
            glm::mat4 view = glm::lookAt(
                camera_pos, camera_pos + camera_front, camera_up);
            light_shader->setMat4("view", view);
            // set light uniforms
            light_shader->setVec3("viewPos", camera_pos);
            light_shader->setVec3("lightPos", light_pos);
            light_shader->setMat4("lightSpaceMatrix", light_space_matrix);
            light_shader->setBool("shadowEnabled", shadow_enabled);        
            render_meshes(light_shader);
            glCullFace(GL_BACK);

            // swap buffers and poll IO events (keys, mouse etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();

            // compute frame time and frame rate.
            auto t1 = std::chrono::high_resolution_clock::now();
            delta_frame_milli = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
            frame_rate = (frame_rate * smoothing) + ((1.0/(delta_frame_milli.count()/1000.0)) * (1.0-smoothing));
            
            // call user-defined callback
            if (user_callback) { user_callback(this); }
        }

        return make_SimpleGL_error_condition(0);
    }

    void Scene::render_meshes(Shader *sh) {
        for (auto& [t, obj_ptr] : obj_map) {
            // never draw composite because it is made up of mesh instances.
            if (obj_ptr->is_composite()) { continue; }
            // draw all visible instances of the current mesh.
            obj_ptr->bindVAO();
            int v_size = obj_ptr->get_v_size();
            for (auto& info : obj_ptr->obj_infos()) {
                if (info.second.hidden) { continue; }
                sh->setVec3("objectColor", info.first);
                sh->setMat4("model", info.second.get_model());
                glDrawArrays(GL_TRIANGLES, 0, (int) (v_size / 6));
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////
    // SHORT METHODS THAT INVOLVE GLOBAL VARIABLES
    //////////////////////////////////////////////////////////////////

    double Scene::get_frame_rate() const { return frame_rate; }
    std::chrono::milliseconds Scene::get_delta_frame_milli() const 
        { return delta_frame_milli; }
    void Scene::set_smooth(const double smooth) { smoothing = smooth; }
    void Scene::set_shadow(bool enable) { shadow_enabled = enable; }
    void Scene::set_light_pos(const glm::vec3 pos) { light_pos = pos; }

    //////////////////////////////////////////////////////////////////
    // STATIC CALLBACK FUNCTIONS
    //////////////////////////////////////////////////////////////////

    // process all input: 
    // query GLFW which keys are pressed/released this frame and act accordingly
    void Scene::process_input(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        } else {
            float cameraSpeed = 2.5 * delta_time;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                camera_pos += cameraSpeed * camera_front;
            } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                camera_pos -= cameraSpeed * camera_front;
            } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                camera_pos -= glm::normalize(
                    glm::cross(camera_front, camera_up)) * cameraSpeed;
            } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                camera_pos += glm::normalize(
                    glm::cross(camera_front, camera_up)) * cameraSpeed;
            } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                camera_pos += camera_up * cameraSpeed;
            } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
                camera_pos += -camera_up * cameraSpeed;
            } else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
                shadow_enabled = !shadow_enabled;
            }
        }
    }

    void Scene::key_callback(
        GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (at_shape_level) {
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
                type_idx = (type_idx + 1) % obj_types.size();
                if (obj_map.find(obj_types[type_idx]) != obj_map.end()) {
                    curr_obj = obj_map[obj_types[type_idx]];
                    obj_count = curr_obj->count();
                }
                std::cout << "switched to shape category " 
                          << obj_types[type_idx] << "\n";
            } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
                at_shape_level = false;
                instance_idx = 0;
                std::cout << "at instance level\n";
            } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
                curr_obj->hide_all();
            } else if (key == GLFW_KEY_U && action == GLFW_PRESS) {
                curr_obj->show_all();
            }
        } else {
            float speed = 5.0 * delta_time;
            float rot_angle = 10.0 * delta_time;
            if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
                instance_idx = (instance_idx + 1) % obj_count;
                std::cout << "switched to instance at idx " << instance_idx << "\n";
            } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
                instance_idx = (instance_idx - 1) % obj_count;
                if (instance_idx < 0) instance_idx += obj_count;
                std::cout << "switched to instance at idx " << instance_idx << "\n";
            } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
                at_shape_level = true;
                std::cout << "at shape level\n";
            } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
                curr_obj->hide_instance(instance_idx);
            } else if (key == GLFW_KEY_U && action == GLFW_PRESS) {
                curr_obj->show_instance(instance_idx);
            } else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {-speed, 0, 0});
            } else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {speed, 0, 0});
            } else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {0, -speed, 0});
            } else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {0, speed, 0});
            } else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {0, 0, -speed});
            } else if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
                curr_obj->translate(instance_idx, {0, 0, speed});
            } else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
                curr_obj->rotate(instance_idx, rot_angle, {1, 0, 0});
            } else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
                curr_obj->rotate(instance_idx, rot_angle, {0, 1, 0});
            } else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
                curr_obj->rotate(instance_idx, rot_angle, {0, 0, 1});
            } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
                RenderInfo info = curr_obj->get_instance_info(instance_idx);
                std::cout << "\ncolor: " << info.first
                          << "\ntransformation: " << info.second << "\n";
            }
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    // glfw: whenever the mouse moves, this callback is called
    void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        if (first_mouse) {
            last_x
 = xpos;
            last_y = ypos;
            first_mouse = false;
        }
        
        float xoffset = xpos - last_x;
        float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top
        last_x = xpos;
        last_y = ypos;
        
        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        
        yaw += xoffset;
        pitch += yoffset;
        
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front = glm::normalize(front);
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    void Scene::scroll_callback(
        GLFWwindow* window, double xoffset, double yoffset) {
        if (fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if (fov <= 1.0f)
            fov = 1.0f;
        if (fov >= 45.0f)
            fov = 45.0f;
    }

    // ref: https://www.glfw.org/docs/latest/quick.html#quick_capture_error
    void Scene::error_callback(int error, const char* description) {
        std::cerr << "Terminating. GLFW Error:" << description << "\n";
        std::exit(error);
    }

}
