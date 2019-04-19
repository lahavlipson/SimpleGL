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

class Scene;

// mesh_id: represents the id to a specific instance of Mesh
// to modify its model matrix and color.
class Mesh_id {
public:
    Mesh_id(Shape shape, int mesh_id): mesh_shape(shape), id(mesh_id), scene_ptr(nullptr){}
    ~Mesh_id(){}
    
    int get_mesh_id(){
        return Mesh_id::id;
    }
    Shape get_shape(){
        return Mesh_id::mesh_shape;
    }
    Scene* get_scene_ptr(){
        return Mesh_id::scene_ptr;
    }

    void set_scene_ptr(Scene* ptr){
        scene_ptr = ptr;
    }


private:
    Shape mesh_shape;
    int id;
    Scene* scene_ptr;
};

class Scene {
public:
    Scene(char *vs = nullptr, char *fs = nullptr, 
          const int width = 800, const int height = 600);
    ~Scene();

    Mesh_id add_mesh(
        const Shape s, const glm::vec3 color = {0.4, 0.4, 0.4}, 
        const std::variant<std::map<std::string, int>, std::string> p = {});

    // Methods for manipulating mesh instances.
    void set_color(const Mesh_id m_id, const glm::vec3 c);
    void set_model(const Mesh_id m_id, const glm::mat4 model);
    void reset_model(const Mesh_id m_id);
    void translate(const Mesh_id m_id, const glm::vec3 translation);
    void translate_to(const Mesh_id m_id, const glm::vec3 destination);
    void rotate(const Mesh_id m_id, const float angle, glm::vec3 axis);
    void set_rotation(const Mesh_id m_id, const float angle, glm::vec3 axis);
    void scale(const Mesh_id m_id, const glm::vec3 factor);
    void scale(const Mesh_id m_id, const double factor);
    void set_scale(const Mesh_id m_id, const glm::vec3 factor);
    void set_scale(const Mesh_id m_id, const double factor);
    glm::vec3 get_loc(Mesh_id m_id);

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
    std::unordered_map<Shape, Mesh *> meshMap;
};

#endif
