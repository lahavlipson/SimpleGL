#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glp/glp.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <obj_loader/obj_loader.h>

// a lot of this file is referenced from the learnopengl.com tutorial
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void checkCompileErrors(GLuint shader, std::string type);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;
float pitch =  0.0f;
float fov   =  45.0f;
float lastX =  0.0f;
float lastY =  0.0f;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(6.2f, 7.0f, 5.0f);

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "Usage: " << *argv << " <vshader_fpath> <fshader_fpath> [optional_.obj_path]\n";
        return 0;
    }
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    lastX = (float) SCR_WIDTH / 2.0;
    lastY = (float) SCR_HEIGHT / 2.0;
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SimpleGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    
    // build and compile our shader program
     // 1. retrieve the vertex/fragment source code from filePath
    unsigned int ID;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(*(argv+1));
        fShaderFile.open(*(argv+2));
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    auto vertices = glp::box(glm::dvec3(1,1,1));
    // world space positions of our cubes

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(ID);
    glUniform3f(glGetUniformLocation(ID, "lightColor"),  1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(ID, "lightPos"),  6.2f, 7.0f, 5.0f);
    unsigned int vbo_box, vao_box, vao_sphere, vbo_sphere, vao_p, vbo_p, vao_obj, vbo_obj, vao_cone, vbo_cone, vao_torus, vbo_torus, vao_cylinder, vbo_cylinder, vbo_tcone, vao_tcone;
    
    const glm::vec3 RED(0.95, 0.02, 0.02), BLUE(0.21, 0.25, 1), GREEN(0.02, 0.82, 0.02), YELLOW(0.98, 0.98, 0.30), ORANGE(0.99, 0.59, 0.21),
    PINK(0.98, 0.32, 0.91), TEAL(0.28, 0.98, 0.64), GREY(0.38, 0.38, 0.38);

    std::chrono::milliseconds delta_frame_milli;
    double frame_rate = 60; // dummy initial value
    double smoothing = 0.5; // initial smoothing
    
    // render boxes
    glGenVertexArrays(1, &vao_box);
    glBindVertexArray(vao_box);
    glGenBuffers(1, &vbo_box);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_box);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(double), vertices.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)(3 * sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render spheres
    auto verticesSphere = glp::sphere(3, 1);
    glGenVertexArrays(1, &vao_sphere);
    glBindVertexArray(vao_sphere);
    glGenBuffers(1, &vbo_sphere);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere);
    glBufferData(GL_ARRAY_BUFFER, verticesSphere.size()*sizeof(double), verticesSphere.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render toruses
    auto verticesTorus = glp::torus(10, 10, 0.7, 0.4);
    glGenVertexArrays(1, &vao_torus);
    glBindVertexArray(vao_torus);
    glGenBuffers(1, &vbo_torus);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_torus);
    glBufferData(GL_ARRAY_BUFFER, verticesTorus.size()*sizeof(double), verticesTorus.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render cones
    auto verticesCone = glp::cone(4, 2, 1);
    glGenVertexArrays(1, &vao_cone);
    glBindVertexArray(vao_cone);
    glGenBuffers(1, &vbo_cone);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cone);
    glBufferData(GL_ARRAY_BUFFER, verticesCone.size()*sizeof(double), verticesCone.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render truncated cones
    auto verticesTCone = glp::truncatedCone(32, 2, 1, 0.2);
    glGenVertexArrays(1, &vao_tcone);
    glBindVertexArray(vao_tcone);
    glGenBuffers(1, &vbo_tcone);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tcone);
    glBufferData(GL_ARRAY_BUFFER, verticesTCone.size()*sizeof(double), verticesTCone.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render cylinders
    auto verticesCylinder = glp::cylinder(6, 1, 1);
    glGenVertexArrays(1, &vao_cylinder);
    glBindVertexArray(vao_cylinder);
    glGenBuffers(1, &vbo_cylinder);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cylinder);
    glBufferData(GL_ARRAY_BUFFER, verticesCylinder.size()*sizeof(double), verticesCylinder.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    // render pyramid
    auto verticesPyramid = glp::pyramid(3, 1, 1);
    glGenVertexArrays(1, &vao_p);
    glBindVertexArray(vao_p);
    glGenBuffers(1, &vbo_p);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_p);
    glBufferData(GL_ARRAY_BUFFER, verticesPyramid.size()*sizeof(double), verticesPyramid.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
    glEnableVertexAttribArray(1);
    
    //render obj
    std::vector<double> verticesObj;
    if (argc > 3) {
        objl::Loader loader;
        loader.LoadFile(*(argv+3));
        for (int i = 0; i < loader.LoadedVertices.size(); i++){
            verticesObj.push_back(loader.LoadedVertices[i].Position.X);
            verticesObj.push_back(loader.LoadedVertices[i].Position.Y);
            verticesObj.push_back(loader.LoadedVertices[i].Position.Z);
            verticesObj.push_back(loader.LoadedVertices[i].Normal.X);
            verticesObj.push_back(loader.LoadedVertices[i].Normal.Y);
            verticesObj.push_back(loader.LoadedVertices[i].Normal.Z);
        }
        assert (verticesObj.size() == 6 * loader.LoadedVertices.size());
        glGenVertexArrays(1, &vao_obj);
        glBindVertexArray(vao_obj);
        glGenBuffers(1, &vbo_obj);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_obj);
        glBufferData(GL_ARRAY_BUFFER, verticesObj.size()*sizeof(double), verticesObj.data(), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE,6*sizeof(double), (void*)(3*sizeof(double)));
        glEnableVertexAttribArray(1);
    }
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // start measuring frame time
        auto t0 = std::chrono::high_resolution_clock::now();
        
        // input
        processInput(window);
        
        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // activate shader
        glUseProgram(ID);
        
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
       
        glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        
        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // pass camera/view transformation to shade
        glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniform3f(glGetUniformLocation(ID, "objectColor"), 1.0f, 0.5f, 0.71f);
        
        //floor
        glBindVertexArray(vao_box);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, {-35, -7, -35});
        model = glm::scale(model, glm::vec3(70, 0.2, 70));
        glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
        glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &GREY[0]);
        glDrawArrays(GL_TRIANGLES, 0, (int) (vertices.size() / 6));
        
        double angle;
        const double radius = 5;
        
        for (int i=0; i<10; i++){
            glBindVertexArray(vao_box);
            // calculate the model matrix for each object and pass it to shader before drawing
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(7+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &TEAL[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (vertices.size() / 6));
            
            glBindVertexArray(vao_sphere);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(1+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &RED[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));
            
            glBindVertexArray(vao_cone);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(4+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &YELLOW[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));
            
            glBindVertexArray(vao_tcone);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(2+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &BLUE[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));
            
            glBindVertexArray(vao_cylinder);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(3+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &GREEN[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));
            
            glBindVertexArray(vao_torus);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(6+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &GREEN[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));

            glBindVertexArray(vao_p);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            angle = (M_PI/4)*(5+i);
            model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &PINK[0]);
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesPyramid.size() / 6));

            if (argc > 3) {
                glBindVertexArray(vao_obj);
                model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                angle = (M_PI/4)*(8+i);
                model = glm::translate(model, {radius*cos(angle),radius*sin(angle), -5 - i*6});
                model = glm::scale(model, glm::vec3(2,2,2));
                glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &ORANGE[0]);
                glDrawArrays(GL_TRIANGLES, 0, (int) (verticesObj.size() / 6));
            }
        }
        
        // compute frame time and frame rate.
        auto t1 = std::chrono::high_resolution_clock::now();
        delta_frame_milli = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
        frame_rate = (frame_rate * smoothing) + ((1.0/(delta_frame_milli.count()/1000.0)) * (1.0-smoothing));
        std::cout << "frame rate: " << frame_rate << "\n";
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &vao_box);
    glDeleteBuffers(1, &vbo_box);
    glDeleteVertexArrays(1, &vao_obj);
    glDeleteBuffers(1, &vbo_obj);
    glDeleteVertexArrays(1, &vao_sphere);
    glDeleteBuffers(1, &vbo_sphere);
    glDeleteVertexArrays(1, &vao_p);
    glDeleteBuffers(1, &vbo_p);
    glDeleteVertexArrays(1, &vao_cylinder);
    glDeleteBuffers(1, &vbo_cylinder);
    glDeleteVertexArrays(1, &vao_tcone);
    glDeleteBuffers(1, &vbo_tcone);
    glDeleteVertexArrays(1, &vao_cone);
    glDeleteBuffers(1, &vbo_cone);
    glDeleteVertexArrays(1, &vao_torus);
    glDeleteBuffers(1, &vbo_torus);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

void checkCompileErrors(GLuint shader, std::string type)
{
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
}
