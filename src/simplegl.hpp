#ifndef SIMPLEGL_HPP
#define SIMPLEGL_HPP

#include <GLFW/glfw3.h>
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
        Scene(char *vs = nullptr, char *fs = nullptr, 
              const int width = 800, const int height = 600, 
              bool use_full_ctrl = false);
        ~Scene();

        ObjId add_obj(obj_type t, const color c = {0.4, 0.4, 0.4},
                      obj_params params = obj_params());
            
        void remove_obj_all(obj_type t);

        std::error_condition render();

        double getFramerate() const;
        std::chrono::milliseconds getDeltaFrameTime();
        void setSmoothing(const double smooth);
        inline void setShadows(bool enableShadow) { shadowsEnabled = enableShadow; }
        inline void setLightPos(const glm::vec3 pos) { lightPos = pos; }
        inline void setCallback(std::function<void(Scene *)> callback) {
            userCallback = callback;
        }
        
        // GLFW callbacks.
        static void error_callback(int error, const char* description);
        static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow *window, const double xpos, const double ypos);
        static void process_input(GLFWwindow *window);
        static void scroll_callback(GLFWwindow *window, const double xoffset, const double yoffset);
        
        // anonymous namespace to protect these values while still allowing access
        // camera frame
        static glm::vec3 cameraPos;
        static glm::vec3 cameraFront;
        static glm::vec3 cameraUp;
        
        // lighting info
        glm::vec3 lightPos = {-2.0f, 4.0f, -1.0f};
        const glm::vec3 LIGHT_COLOR = {1.0f, 1.0f, 1.0f};
        
        static bool firstMouse;
        // yaw is initialized to -90 degrees since a yaw of 0 results in 
        // a direction vector pointing to the right, so we initially 
        // rotate a bit to the left.
        static float yaw = -90.0f;
        static float pitch;
        static float fov;
        static float lastX;
        static float lastY;
        
        // timing
        static float deltaTime; // time between current frame and last frame
        float lastFrame = 0.0f;
        double framerate = 60; // dummy initial value
        std::chrono::milliseconds deltaFrame;
        double smoothing = 0.5;
        
        // key control
        static bool shadowsEnabled;
        static bool atShapeLevel;
        static std::vector<obj_type> obj_types;
        static int type_idx;
        static int instance_idx;
        static int obj_count;
        static BaseObj *curr_obj;
        
        // objects
        static std::unordered_map<obj_type, BaseObj *> obj_map;

    private:
        // glfw window
        int scr_width, scr_height;
        GLFWwindow *window;

        // light and shadow shading
        unsigned int depthMapFBO;
        unsigned int depthMap;
        float borderColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        Shader *lightShader;
        Shader *depthShader;

        // custom render loop callback
        std::function<void(Scene *)> userCallback = nullptr;

        // private helper
        void render_meshes(Shader *sh);
    };
}
#endif
