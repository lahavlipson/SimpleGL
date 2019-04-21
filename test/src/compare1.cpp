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
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(ID);
    glUniform3f(glGetUniformLocation(ID, "lightColor"),  1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(ID, "lightPos"),  6.2f, 7.0f, 5.0f);
    unsigned int VBO, VAO, vao_sphere, vbo_sphere, vao_p, vbo_p, vao_obj, vbo_obj;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
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
        
        // render boxes
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(double), vertices.data(), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)(3 * sizeof(double)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);            
            glDrawArrays(GL_TRIANGLES, 0, (int) (vertices.size() / 6));
        }

        // render spheres
        auto color = glm::vec3(0.7, 0.5, 0.5);
        auto verticesSphere = glp::sphere(7, 1);
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

        glBindVertexArray(vao_sphere);
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(-0.2,-0.2,-0.2));
        model = glm::scale(model, glm::vec3(.5,.5,.5));
        glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model[0][0]);            
        glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &color[0]);
        glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));

        glm::mat4 model2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model2 = glm::translate(model2, glm::vec3(-0.6,-0.6,-0.6));
        model2 = glm::scale(model2, glm::vec3(.3,.3,.3));
        glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model2[0][0]);            
        glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &color[0]);
        glDrawArrays(GL_TRIANGLES, 0, (int) (verticesSphere.size() / 6));

        // render pyramid
        auto verticesPyramid = glp::pyramid(7, 1, 1);
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

        glBindVertexArray(vao_p);
        glm::mat4 modelp = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        modelp = glm::translate(modelp, glm::vec3(4.2,1.2,-0.2));
        modelp = glm::scale(modelp, glm::vec3(.5,.5,.5));
        glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &modelp[0][0]);            
        glUniform3fv(glGetUniformLocation(ID, "objectColor"), 1, &color[0]);
        glDrawArrays(GL_TRIANGLES, 0, (int) (verticesPyramid.size() / 6));

        // render .obj files
        if (argc > 3) {
            objl::Loader loader;
            loader.LoadFile(*(argv+3));
            std::vector<double> verticesObj;
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
            glBindVertexArray(vao_obj);
            glm::mat4 model3 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glUniformMatrix4fv(glGetUniformLocation(ID,"model"), 1, GL_FALSE, &model3[0][0]);  
            model3 = glm::scale(model3, glm::vec3(.08,.08,.08));  
            model3 = glm::translate(model3, glm::vec3(-0.6,-70.2,-0.6));        
            glDrawArrays(GL_TRIANGLES, 0, (int) (verticesObj.size() / 6));
        }
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &vao_obj);
    glDeleteBuffers(1, &vbo_obj);
    glDeleteVertexArrays(1, &vao_sphere);
    glDeleteBuffers(1, &vbo_sphere);
    glDeleteVertexArrays(1, &vao_p);
    glDeleteBuffers(1, &vbo_p);   
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