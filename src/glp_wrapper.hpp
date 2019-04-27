#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <variant>

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include "simplegl_error.hpp"

enum Shape { sphere, truncatedCone, cylinder, cone, pyramid, torus, box };

struct params {
	int accuracy = 6;
	int sides = 3;
};

inline std::variant<std::vector<double>, std::error_condition> createGLPObj(
    const std::variant<Shape, std::string> s, 
	const std::variant<params, std::string> varP) {

    if (std::holds_alternative<Shape>(s)) {
		if (std::holds_alternative<params>(varP)) {
			// Get GLP parameters from the input params.
			auto paramsP = std::get<params>(varP);
			if (paramsP.accuracy <= 1 || paramsP.sides <= 0) {
				return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
			}
			switch (std::get<Shape>(s)) {
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
				// no such GLP primitive
	    		return make_SimpleGL_error_condition(SIMPLEGL_SHAPE_NOT_FOUND);
			}
		} else {
			// provided a filepath when we need params 
			return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);	
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
			// provided params when we need a .obj filepath
    		return make_SimpleGL_error_condition(SIMPLEGL_OBJ_NO_FILE);	
		}
    }
}

#endif
