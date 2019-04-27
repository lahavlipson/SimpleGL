#include <iostream>
#include <stdexcept>

#include "simplegl.hpp"

// camera frame
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

// lighting info
// -------------
glm::vec3 lightPos(6.2f, 7.0f, 5.0f);

bool firstMouse = true;
// yaw is initialized to -90 degrees since a yaw of 0 results in a direction
// vector pointing to the right, so we initially rotate a bit to the left.
float yaw   = -90.0f;
float pitch =  0.0f;
float fov   =  45.0f;
float lastX =  0.0f;
float lastY =  0.0f;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// Note: either both of the shaders are default or neither are default
Scene::Scene(char *vs, char *fs, int width, int height) {
    // glfw: initialize and configure
    glfwSetErrorCallback(Scene::error_callback);
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
    lastX = (float) scr_width / 2.0;
    lastY = (float) scr_height / 2.0;
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        abort();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Scene::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Scene::mouse_callback);
    glfwSetScrollCallback(window, Scene::scroll_callback);

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
        lightShader = new Shader(vs, fs);
    } else {
        lightShader = new Shader(ShaderType::light);
    }
    depthShader = new Shader(ShaderType::depth);
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    lightShader->use();
    lightShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lightShader->setVec3("lightPos", 6.2f, 7.0f, 5.0f);
    
    // configure depth map FBO
    // -----------------------
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Scene::~Scene() {
    // Clean up composite pointers; must be before cleaning up Mesh*.
    for (auto& p : composite_list) {
        delete p;
    }
    // Clean up mesh pointers.
    for (auto& p : mesh_map) {
        delete p.second;
    }
    // Delete shaders.
    delete lightShader;
    delete depthShader;
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

Mesh_id Scene::add_mesh(
    std::variant<Shape, std::string> s, const glm::vec3 color, 
    std::variant<std::unordered_map<std::string, int>, std::string> p) {

    int id = 0;
    Mesh *mesh_ptr;
    if (mesh_map.find(s) != mesh_map.end()) { // contains(s) is c++20
        // adding an instance of this shape to the scene
        mesh_ptr = mesh_map[s];
        id = mesh_ptr->add_instance(color);
    } else { 
        // first time adding this shape to the scene
        auto res = createGLPObj(s, p);
        if (std::holds_alternative<std::vector<double>>(res)) {
            mesh_ptr = new Mesh(std::get<std::vector<double>>(res), color);
            mesh_map.insert(std::make_pair(s, mesh_ptr));
        } else {
            // consideration: the user needs to use throw-try-catch 
            // to handle the error case themselves
            throw std::runtime_error{std::get<std::error_condition>(res).message()};
        }
    }
    return Mesh_id(id, mesh_ptr);
}

Comp_id Scene::add_composite(std::initializer_list<Mesh_id> l) {
    Composite *comp_ptr = new Composite(l);
    composite_list.push_back(comp_ptr);
    return Comp_id(comp_ptr);
}

void Scene::remove_mesh_all(std::variant<Shape, std::string> s) {
    if (mesh_map.find(s) != mesh_map.end()) { // contains(s) is c++20
        delete mesh_map[s];
        mesh_map.erase(s);
    }
}

std::error_condition Scene::render() {
    if (mesh_map.empty()) {
        std::cout << "Current scene has nothing to render.\n";
    }
    
    // shader configuration
    // --------------------
    lightShader->setInt("shadowMap", 0);
    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
    
    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        process_input(window);
        
        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float near_plane = 1.0f, far_plane = 17.5f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                          glm::vec3( 0.0f, 0.0f,  0.0f),
                                          glm::vec3( 0.0f, 1.0f,  0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;
        depthShader->use();
        depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
        
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        render_meshes(depthShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        // 2. render scene as normal using the generated depth/shadow map
        // --------------------------------------------------------------
        glViewport(0, 0, scr_width, scr_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightShader->use();
        glCullFace(GL_FRONT);
        // (note that in this case matrices below could change every frame)
        // pass projection matrix to shader
        glm::mat4 projection = glm::perspective(
            glm::radians(fov), (float)scr_width/(float)scr_height, 0.1f, 100.0f);
        lightShader->setMat4("projection", projection);
        // pass camera/view transformation to shade
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        lightShader->setMat4("view", view);
        // set light uniforms
        lightShader->setVec3("viewPos", cameraPos);
        lightShader->setVec3("lightPos", lightPos);
        lightShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
        lightShader->setBool("shadowEnabled", shadowsEnabled);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        
        render_meshes(lightShader);
        glCullFace(GL_BACK);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return make_SimpleGL_error_condition(0);
}

void Scene::render_meshes(Shader *sh) {
    for (auto& entry : mesh_map) {
        Mesh *mesh_ptr = entry.second;
        mesh_ptr->bindVAO();
        int v_size = mesh_ptr->get_v_size();
        for (auto& info : mesh_ptr->mesh_infos()) {
            if (info.second.hidden) { continue; }
            sh->setVec3("objectColor", info.first);
            sh->setMat4("model", info.second.get_model());
            glDrawArrays(GL_TRIANGLES, 0, (int) (v_size / 6));
        }
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Scene::process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cameraPos += cameraUp * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        cameraPos += -cameraUp * cameraSpeed;
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
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    
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
    cameraFront = glm::normalize(front);
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
