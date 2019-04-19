#ifndef SCENE_HPP
#define SCENE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <variant>
#include <map>

#include "mesh.hpp"
#include "shader.hpp"
#include "simplegl_error.hpp"
#include "glp_wrapper.hpp"

// mesh_id: represents the id to a specific instance of Mesh
// to modify its model matrix and color.
class Mesh_id {
public:
    Mesh_id(int mesh_id, Mesh* mesh_p): id(mesh_id), mesh_ptr(mesh_p){}
    ~Mesh_id(){}
    
    int get_mesh_id(){
        return id;
    }
    Mesh* get_mesh_ptr(){
        return mesh_ptr;
    }

    // Methods for manipulating mesh instances.
    void set_color(const glm::vec3 c);
    void set_model(const glm::mat4 model);
    void reset_model();
    void translate(const glm::vec3 translation);
    void translate_to(const glm::vec3 destination);
    void rotate(const float angle, glm::vec3 axis);
    void set_rotation(const float angle, glm::vec3 axis);
    void scale(const glm::vec3 factor);
    void scale(const double factor);
    void set_scale(const glm::vec3 factor);
    void set_scale(const double factor);
    glm::vec3 get_loc();

private:
    int id;
    Mesh* mesh_ptr;
};


class Scene {
public:
    Scene(char *vs = nullptr, char *fs = nullptr, 
          const int width = 800, const int height = 600);
    ~Scene();

    Mesh_id add_mesh(std::variant<Shape, std::string> s, const glm::vec3 color = {0.4, 0.4, 0.4}, 
        std::variant<std::map<std::string, int>, std::string> p={});
    
    std::error_condition render();

    // GLFW callbacks.
    static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
    static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
    static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);
    static void process_input(GLFWwindow *window);
    static void error_callback(int error, const char* description);

private:
    unsigned int scr_width, scr_height;
    GLFWwindow *window = nullptr;
    Shader *shader;
    std::unordered_map<std::variant<Shape, std::string>, Mesh *> meshMap;
};

#endif
