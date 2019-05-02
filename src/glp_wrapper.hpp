#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <iostream>
#include <unordered_map>
#include <variant>

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include "base_obj.hpp"
#include "simplegl_error.hpp"

enum Shape {sphere, truncatedCone, cylinder, cone, pyramid, torus, box, composite};

struct obj_params {    
    components comp;
    int accuracy = 6;
    int sides = 3;
    std::string filepath;

    bool is_primitive() const {
        return filepath.empty();
    }
};

typedef std::variant<Shape, std::string> obj_type;

inline std::ostream& operator<<(std::ostream& os, obj_type& t) {
    if (std::holds_alternative<Shape>(t)) {
        Shape s = std::get<Shape>(t);
        switch (s) {
            case box: return os << "box"; 
            case composite: return os << "composite"; 
            case cone: return os << "cone"; 
            case cylinder: return os << "cylinder"; 
            case pyramid: return os << "pyramid"; 
            case sphere: return os << "sphere"; 
            case torus: return os << "torus"; 
            case truncatedCone: return os << "truncatedCone";
        }
    } else {
        return os << std::get<std::string>(t);
    }
    return os << "unknown type";
}

inline std::variant<std::vector<double>, std::error_condition> createGLPObj(
    const obj_type t, const obj_params varP) {
    
    if (std::holds_alternative<Shape>(t)) {
        // --- Creating GLP primitive ---
        if (varP.is_primitive()) {
            // Get GLP parameters from the input params.
            auto paramsP = varP;
            if (paramsP.accuracy <= 1 || paramsP.sides <= 0) {
                // Error: invalid GLP parameters
                return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
            }
            switch (std::get<Shape>(t)) {
            case sphere:
                return glp::sphere(paramsP.accuracy, 1);
            case truncatedCone:
                return glp::truncatedCone(paramsP.accuracy, 1, 1, 1);
            case cylinder:
                return glp::cylinder(paramsP.accuracy, 1, 1);
            case cone:
                return glp::cone(paramsP.accuracy, 1, 1);
            case pyramid:
                return glp::pyramid(paramsP.sides, 1, 1);
            case torus:
                return glp::torus(1, 1, 1, 1);
            case box:
                return glp::box(glm::dvec3(1, 1, 1));
            default:
                // Error: no such GLP primitive
                return make_SimpleGL_error_condition(SIMPLEGL_SHAPE_NOT_FOUND);
            }
        } else {
            // Error: didn't provide GLP parameters
            return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);   
        }
    } else {
        // --- Loading from .obj file ---
        const std::string filepath = varP.filepath;
        if (filepath.substr(filepath.find_last_of(".") + 1) == "obj") {
            // Get the filepath to the .obj file and load the vertices.
            std::string filepath = varP.filepath;
            objl::Loader loader;
            if (!loader.LoadFile(filepath)) {
                return make_SimpleGL_error_condition(SIMPLEGL_INVALID_OBJ_FILE);
            }
            std::vector<double> output;
            for (int i = 0; i < loader.LoadedVertices.size(); i++) {
                output.push_back(loader.LoadedVertices[i].Position.X);
                output.push_back(loader.LoadedVertices[i].Position.Y);
                output.push_back(loader.LoadedVertices[i].Position.Z);
                output.push_back(loader.LoadedVertices[i].Normal.X);
                output.push_back(loader.LoadedVertices[i].Normal.Y);
                output.push_back(loader.LoadedVertices[i].Normal.Z);
            }
            if (output.size() != (6 * loader.LoadedVertices.size())) {
                return make_SimpleGL_error_condition(SIMPLEGL_OBJ_LOAD_FAIL);
            }
            return output;
        } else {
            // Error: didn't provide a .obj filepath
            return make_SimpleGL_error_condition(SIMPLEGL_OBJ_NO_FILE);
        }
    }
}

#endif
