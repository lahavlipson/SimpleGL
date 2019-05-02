#ifndef SIMPLEGL_HPP
#define SIMPLEGL_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <functional>
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
        Scene(bool use_full_ctrl = false, char *vs = nullptr, 
            char *fs = nullptr, const int width = 800, const int height = 600);
        ~Scene();

        ObjId add_obj(ObjType t, const Color c = {0.4, 0.4, 0.4},
                      ObjParams params = ObjParams());
            
        void remove_obj_all(ObjType t);

        std::error_condition render();

        double get_frame_rate() const;
        std::chrono::milliseconds get_delta_frame_milli() const;
        void set_smooth(const double smooth);
        void set_shadow(bool enable);
        void set_light_pos(const glm::vec3 pos);
        inline void set_callback(
            std::function<void(Scene *)> callback) { user_callback = callback; }
        
        // GLFW callbacks.
        static void error_callback(int error, const char* description);
        static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
        static void process_input(GLFWwindow *window);
        static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);

    private:
        // glfw window
        int scr_width, scr_height;
        GLFWwindow *window;
        // light and shadow shading
        unsigned int depth_map_fbo;
        unsigned int depth_map;
        const float border_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        Shader *light_shader;
        Shader *depth_shader;
        // custom render loop callback
        std::function<void(Scene *)> user_callback = nullptr;
        // private helper
        void render_meshes(Shader *sh);
    };
}

#endif
