#ifndef SIMPLEGL_HPP
#define SIMPLEGL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <variant>

#include "composite.hpp"
#include "glp_wrapper.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "simplegl_error.hpp"

namespace sgl{

    class Scene {
    public:
        Scene(char *vs = nullptr, char *fs = nullptr, 
              const int width = 800, const int height = 600);
        ~Scene();

        Mesh_id add_mesh(
            std::variant<Shape, std::string> s, 
            const glm::vec3 color = {0.4, 0.4, 0.4}, 
            std::variant<params, std::string> p = {});
        
        Comp_id add_composite(std::initializer_list<Mesh_id> l);
        
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
        Shader *lightShader;
        Shader *depthShader;
        std::unordered_map<std::variant<Shape, std::string>, Mesh *> mesh_map;
        std::vector<Composite *> composite_list;

        // for shadow depth map
        unsigned int depthMapFBO;
        unsigned int depthMap;
        float borderColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        
        void render_meshes(Shader *sh);
    };
}
#endif
