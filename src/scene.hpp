#ifndef SCENE_HPP
#define SCENE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <variant>

#include "mesh.hpp"
#include "shader.hpp"

// mesh_id: represents the id to a specific instance of Mesh
// to modify its model matrix and color.
typedef std::pair<Shape, int> mesh_id;

class Scene {
public:
    Scene(char *vs= NULL, char *fs= NULL, int width = 800, int height = 600);
    ~Scene();

    mesh_id add_mesh(Shape s, std::variant<std::vector<double>, std::string> p,
                     glm::vec3 color, glm::mat4 model, bool isDefault = true);

    // Methods for manipulating mesh instances.
    void set_color(mesh_id m_id, glm::vec3 c);
    void set_model(mesh_id m_id, glm::mat4 model);
    void reset_model(mesh_id m_id);
    void translate(mesh_id m_id, glm::vec3 translation);
    void rotate(mesh_id m_id, float angle, glm::vec3 axis);

    void render();

    // GLFW callbacks.
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void process_input(GLFWwindow *window);

private:
    unsigned int scr_width, scr_height;
    GLFWwindow *window = nullptr;
    Shader *shader;
    std::unordered_map<Shape, Mesh *> meshMap;
};

#endif
