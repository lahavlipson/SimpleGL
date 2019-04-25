#ifndef SCENE_HPP
#define SCENE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <variant>

#include "glp_wrapper.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "simplegl_error.hpp"

// mesh_id: represents the id to a specific instance of Mesh
// to modify its model matrices and color.
class Mesh_id {
public:
    Mesh_id(int mesh_id, Mesh* mesh_p): id(mesh_id), mesh_ptr(mesh_p) {}
    ~Mesh_id() {}
    
    int get_mesh_id() {
        return id;
    }
    
    Mesh* get_mesh_ptr() {
        return mesh_ptr;
    }

    // Methods for manipulating mesh instances.
    void remove() {
        hide();
    }

    void hide() {
        mesh_ptr->hide_instance(id);
    }

    void show() {
        mesh_ptr->show_instance(id);
    }

    void set_color(glm::vec3 c) {
        mesh_ptr->set_color(id, c);
    }

    void set_model(glm::mat4 m) {
        mesh_ptr->set_model(id, m);
    }

    void reset_model() {
        mesh_ptr->reset_model(id);
    }

    void translate(glm::vec3 translation) {
        mesh_ptr->translate(id, translation);
    }

    void set_translation(const glm::vec3 translation) {
        mesh_ptr->set_translation(id, translation);
    }

    void scale(glm::vec3 factor) {
        mesh_ptr->scale(id, factor);
    }

    void scale(double factor) {
        mesh_ptr->scale(id, {factor, factor, factor});
    }

    void set_scale(const glm::vec3 factor) {
        mesh_ptr->set_scale(id, factor);
    }

    void set_scale(const double factor) {
        mesh_ptr->set_scale(id, {factor, factor, factor});
    }

    void rotate(float angle, glm::vec3 axis) {
        mesh_ptr->rotate(id, angle, axis);
    }

    void set_rotation(const float angle, glm::vec3 axis) {
        mesh_ptr->set_rotation(id, angle, axis);
    }

    glm::vec3 get_loc() {
        return mesh_ptr->get_loc(id);
    }

    bool operator ==(const Mesh_id &b) const{
        return id == b.id && mesh_ptr == b.mesh_ptr;
    }

    int id;
    Mesh* mesh_ptr;
};

namespace std {

    template <>
    struct hash<Mesh_id>
    {
        std::size_t operator()(const Mesh_id& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            return ((hash<int>()(k.id)
                     ^ (hash<Mesh *>()(k.mesh_ptr) << 1)) >> 1);
        }
    };
}

class Scene {
public:
    Scene(char *vs = nullptr, char *fs = nullptr, 
          const int width = 800, const int height = 600);
    ~Scene();

    Mesh_id add_mesh(
        std::variant<Shape, std::string> s, 
        const glm::vec3 color = {0.4, 0.4, 0.4}, 
        std::variant<std::unordered_map<std::string, int>, std::string> p = {});
    
    void remove_mesh_all(std::variant<Shape, std::string> s);
    
    inline void toggleShadows() { shadowsEnabled = !shadowsEnabled; }
    
    std::error_condition render();

    // GLFW callbacks.
    static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
    static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
    static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);
    static void process_input(GLFWwindow *window);
    static void error_callback(int error, const char* description);

private:
    bool shadowsEnabled = true;
    int scr_width, scr_height;
    GLFWwindow *window = nullptr;
    Shader *shader;
    Shader *simpleDepthShader;
    std::unordered_map<std::variant<Shape, std::string>, Mesh *> meshMap;
};

#endif
