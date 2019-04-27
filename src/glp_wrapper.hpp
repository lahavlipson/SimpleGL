#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <iostream>
#include <unordered_map>
#include <variant>

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include "simplegl_error.hpp"

enum Shape { sphere, truncatedCone, cylinder, cone, pyramid, torus, box, composite };

struct obj_params {
    std::variant<std::unordered_map<std::string, int>, std::string> glp_params;
    components comp;
};

typedef std::variant<Shape, std::string> obj_type;

std::ostream& operator<<(std::ostream& os, obj_type t) {
	if (std::holds_alternative<Shape>(t)) {
		Shape s = std::get<Shape>(t);
		switch (s) {
			case box: os << "box"; break;
			case composite: os << "composite"; break;
			case cone: os << "cone"; break;
			case cylinder: os << "cylinder"; break;
			case pyramid: os << "pyramid"; break;
			case sphere: os << "sphere"; break;
			case torus: os << "torus"; break;
			case truncatedCone: os << "truncatedCone"; break;
			default: os << int(s); break;
		}
	} else {
		os << std::get<std::string>(t);
	}
    return os;
}

inline std::variant<std::vector<double>, std::error_condition> createGLPObj(
    const obj_type t, 
	const std::variant<std::unordered_map<std::string, int>, std::string> varP) {

    if (std::holds_alternative<Shape>(t)) { 
    	// --- GLP Primitive ---
    	int accuracy = 6;
    	int sides = 3;

		if (std::holds_alternative<std::unordered_map<std::string, int>>(varP)) {
			// Get GLP parameters from the input params map.
			auto params = std::get<std::unordered_map<std::string, int>>(varP);
	        if (params.find("accuracy") != params.end()) {
	            accuracy = params["accuracy"];
	        	if (accuracy <= 1) {
	        		return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
	        	}
	        }
	        if (params.find("sides") != params.end()) {
	            sides = params["sides"];
	        	if (sides <= 0) {
	        		return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
	        	}
	        }
		} else {
			// provided a filepath when we need a params map 
			return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);	
		}

		switch (std::get<Shape>(t)) {
		case sphere:
			return glp::sphere(accuracy, 1);
		case truncatedCone:
			return glp::truncatedCone(accuracy, 1, 1, 1);
		case cylinder:
			return glp::cylinder(accuracy, 1, 1);
		case cone:
			return glp::cone(accuracy, 1, 1);
		case pyramid:
			return glp::pyramid(sides, 1, 1);
		case torus:
			return glp::torus(1, 1, 1, 1);
		case box:
			return glp::box(glm::dvec3(1, 1, 1));
		default:
			// no such GLP primitive
    		return make_SimpleGL_error_condition(SIMPLEGL_SHAPE_NOT_FOUND);
		}
    } else {
    	// --- Loading from .obj file ---
		if (std::holds_alternative<std::string>(varP)) {
			// Get the filepath to the .obj file and load the vertices.
			std::string filepath = std::get<std::string>(varP);
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
			// provided a params map when we need a .obj filepath
    		return make_SimpleGL_error_condition(SIMPLEGL_OBJ_NO_FILE);	
		}
    }
}

#endif
