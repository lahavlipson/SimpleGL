#include <system_error>
#include <string>

#include <GLFW/glfw3.h>

#define 	SIMPLEGL_INVALID_PARAM  0x00020001
#define 	SIMPLEGL_INVALID_OBJ_FILE  0x00020002
#define 	SIMPLEGL_OBJ_LOAD_FAIL  0x00020003


// ref: https://stackoverflow.com/questions/13093576/mapping-external-error-codes-to-stderror-condition
class SimpleGL_error : public std::error_category {
public:
    const char* name() const noexcept {return "SimpleGL status code";}
    std::string message( int errCode ) const {
        switch( errCode ) {
        // ref for glfw error codes: https://www.glfw.org/docs/latest/group__errors.html
        case GLFW_NOT_INITIALIZED: return "GLFW error: GLFW has not been initialized";
        case GLFW_NO_CURRENT_CONTEXT: return "GLFW error: GLFW no current context";
        case GLFW_INVALID_ENUM: return "GLFW error: GLFW invalid enum";
        case GLFW_INVALID_VALUE: return "GLFW error: GLFW invalid value";
        case GLFW_OUT_OF_MEMORY: return "GLFW error: GLFW out of memory";
        case GLFW_API_UNAVAILABLE: return "GLFW error: GLFW API unavailable";
        case GLFW_VERSION_UNAVAILABLE: return "GLFW error: GLFW version unavailable";
        case GLFW_PLATFORM_ERROR: return "GLFW error: GLFW platform error";
        case GLFW_FORMAT_UNAVAILABLE: return "GLFW error: GLFW format unavailable";
        case GLFW_NO_WINDOW_CONTEXT: return "GLFW error: GLFW window does not have an OpenGL context";
        case 0 : return "Success";
        case SIMPLEGL_INVALID_PARAM: return "SimpleGL status: invalid parameter";
        case SIMPLEGL_INVALID_OBJ_FILE: return "SimpleGL status: invalid file";
        case SIMPLEGL_OBJ_LOAD_FAIL: return "SimpleGL status: obj loader failed";
        // a couple of other error codes will be handled here
        default: return "Unknown status code";
        }
    }
    std::error_condition default_error_condition( int errCode ) const noexcept {
        return std::error_condition( errCode, *this );
    }
};
inline SimpleGL_error const& SimpleGL_error() {
    static class SimpleGL_error res;
    return res;
}

inline std::error_condition make_SimpleGL_error_condition( int status ) {
    return std::error_condition( status, SimpleGL_error() );
}
