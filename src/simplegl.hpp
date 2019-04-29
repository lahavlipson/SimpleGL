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

namespace sgl {

    class Scene {
    public:
        Scene(char *vs = nullptr, char *fs = nullptr, 
              const int width = 800, const int height = 600, 
              bool use_full_ctrl = false);
        ~Scene();

        ObjId add_obj(obj_type t, const color c = {0.4, 0.4, 0.4},
                      obj_params params = obj_params());
            
        void remove_obj_all(obj_type t);
        
        std::error_condition render();

        // GLFW callbacks.
        static void error_callback(int error, const char* description);
        static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
        static void process_input(GLFWwindow *window);
        static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);

    private:
        // for glfw window
        int scr_width, scr_height;
        GLFWwindow *window;

        // for light & shadow shading
        unsigned int depthMapFBO;
        unsigned int depthMap;
        float borderColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        Shader *lightShader;
        Shader *depthShader;

        void render_meshes(Shader *sh);
    };
}
#endif
