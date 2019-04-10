


class Scene {
public:
    Scene(char *vs, char *fs);
    
    GLFWwindow* window = nullptr;
    
    Shader shader;
    
    void render();
    
    std::vector<Mesh *> meshes;
    
   
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow *window);
    
};
