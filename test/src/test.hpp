
class Scene {
public:
    Scene(char *vs, char *fs);
    
    GLFWwindow* window = nullptr;
    
    Shader shader;
    
    void render();
    
};
