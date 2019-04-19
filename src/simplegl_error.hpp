#ifndef SIMPLEGL_ERROR_HPP
#define SIMPLEGL_ERROR_HPP

#include <system_error>
#include <string>

#include <GLFW/glfw3.h>

#define SIMPLEGL_INVALID_PARAM 0x00020001
#define SIMPLEGL_INVALID_OBJ_FILE 0x00020002
#define SIMPLEGL_OBJ_LOAD_FAIL 0x00020003

// ref: https://stackoverflow.com/questions/13093576/mapping-external-error-codes-to-stderror-condition
class SimpleGL_error : public std::error_category {
public:
    const char* name() const noexcept { return "SimpleGL status code"; }
    std::string message(int errCode) const {
        switch(errCode) {
        // ref for glfw error codes: https://www.glfw.org/docs/latest/group__errors.html
        case 0: return "Success";
        case SIMPLEGL_INVALID_PARAM: return "SimpleGL status: invalid parameter";
        case SIMPLEGL_INVALID_OBJ_FILE: return "SimpleGL status: invalid file";
        case SIMPLEGL_OBJ_LOAD_FAIL: return "SimpleGL status: obj loader failed";
        // a couple of other error codes will be handled here
        default: return "Unknown status code";
        }
    }
    std::error_condition default_error_condition(int errCode) const noexcept {
        return std::error_condition(errCode, *this);
    }
};

inline SimpleGL_error const& SimpleGL_error_static() {
    static class SimpleGL_error res;
    return res;
}

inline std::error_condition make_SimpleGL_error_condition(int status) {
    return std::error_condition(status, SimpleGL_error_static());
}
#endif