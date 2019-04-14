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
    Scene(char *vs= nullptr, char *fs= nullptr, const int width = 800, const int height = 600);
    ~Scene();

    mesh_id add_mesh(const Shape s, const std::variant<std::vector<double>, std::string> p,
                     const glm::vec3 color, const glm::mat4 model, const bool isDefault = true);

    // Methods for manipulating mesh instances.
    void set_color(const mesh_id m_id, const glm::vec3 c);
    void set_model(const mesh_id m_id, const glm::mat4 model);
    void reset_model(const mesh_id m_id);
    void translate(const mesh_id m_id, const glm::vec3 translation);
    void rotate(const mesh_id m_id, const float angle, glm::vec3 axis);
    void scale(const mesh_id m_id, const glm::vec3 factor);
    void scale(const mesh_id m_id, const double factor);

    void render();

    // GLFW callbacks.
    static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
    static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
    static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);
    static void process_input(GLFWwindow *window);

private:
    unsigned int scr_width, scr_height;
    GLFWwindow *window = nullptr;
    Shader *shader;
    std::unordered_map<Shape, Mesh *> meshMap;
};

#endif
