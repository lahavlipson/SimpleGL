#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <variant>
#include <map>

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include "simplegl_error.hpp"

enum Shape { sphere, truncatedCone, cylinder, cone, pyramid, torus, box, obj };

inline std::variant<std::vector<double>,std::error_condition>  createGLPObj(
    const Shape s, const std::variant<std::map<std::string, double>, std::string> varP, 
    const bool isDefault = true) {
    
	std::map<std::string, double> params;
	std::string filepath;
    int accuracy = 6;
    int sides = 3;

	if (std::holds_alternative<std::map<std::string, double>>(varP)) {
		params = std::get<std::map<std::string, double>>(varP);
        if ( params.find("accuracy") != params.end() ){
            accuracy = params["accuracy"];
        	if (accuracy <= 0){
        		return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
        	}
        }
        if ( params.find("sides") != params.end() ){
            sides = params["sides"];
        	if (sides <= 0){
        		return make_SimpleGL_error_condition(SIMPLEGL_INVALID_PARAM);
        	}        
        }
	} else {
		filepath = std::get<std::string>(varP);
	}

	switch (s) {
		
	case sphere:
		if (isDefault) {
			return glp::sphere(accuracy, 1);
		}
		return glp::sphere(accuracy, 1, glm::dvec3(1,1,1));

	case truncatedCone:
		if (isDefault) {
			return glp::truncatedCone(accuracy, 1, 1, 1);
		}
		return glp::truncatedCone(accuracy, 1, 1, 1, glm::dvec3(1,1,1));

	case cylinder:
		if (isDefault) {
			return glp::cylinder(accuracy, 1, 1);
		}
		return glp::cylinder(accuracy, 1, 1, glm::dvec3(1,1,1));

	case cone:
		if (isDefault) {
			return glp::cone(accuracy, 1, 1);
		}
		return glp::cone(accuracy, 1, 1, glm::dvec3(1,1,1));
	
	case pyramid:
		if (isDefault) {
			return glp::pyramid(sides, 1, 1);
		}
		return glp::pyramid(sides, 1, 1, glm::dvec3(1,1,1));

	case torus:
		if (isDefault) {
			return glp::torus((int) 1, (int) 1, 1, 1);
		}
		return glp::torus((int) 1, (int) 1, 1, 1, glm::dvec3(1,1,1));

	case box:
		if (isDefault) {
			return glp::box(glm::dvec3(1,1,1));
		}
		return glp::box(glm::dvec3(1,1,1), glm::dvec3(1,1,1));

	case obj:
		objl::Loader loader;
		if (!loader.LoadFile(filepath)){
        		return make_SimpleGL_error_condition(SIMPLEGL_INVALID_OBJ_FILE);
		}
		std::vector<double> output;
		for (int i = 0; i < loader.LoadedVertices.size(); i++){
			output.push_back(loader.LoadedVertices[i].Position.X);
			output.push_back(loader.LoadedVertices[i].Position.Y);
			output.push_back(loader.LoadedVertices[i].Position.Z);
			output.push_back(loader.LoadedVertices[i].Normal.X);
			output.push_back(loader.LoadedVertices[i].Normal.Y);
			output.push_back(loader.LoadedVertices[i].Normal.Z);
		}
		if (output.size() != (6 * loader.LoadedVertices.size())){
        		return make_SimpleGL_error_condition(SIMPLEGL_OBJ_LOAD_FAIL);
		}
		return output;
	}
}

#endif
