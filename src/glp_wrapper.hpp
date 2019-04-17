#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include <variant>
#include <map>

enum Shape { sphere, truncatedCone, cylinder, cone, pyramid, torus, box, obj };

inline std::vector<double> createGLPObj(
    const Shape s, const std::variant<std::map<std::string, double>, std::string> varP, 
    const bool isDefault = true) {
    
	std::map<std::string, double> params;
	std::string filepath;
	if (std::holds_alternative<std::map<std::string, double>>(varP)) {
		params = std::get<std::map<std::string, double>>(varP);
	} else {
		filepath = std::get<std::string>(varP);
	}

	switch (s) {
		
	case sphere:
		if (isDefault) {
			return glp::sphere((int) 1, 1);
		}
		return glp::sphere((int) 1, 1, glm::dvec3(1,1,1));

	case truncatedCone:
		if (isDefault) {
			return glp::truncatedCone((int) 1, 1, 1, 1);
		}
		return glp::truncatedCone((int) 1, 1, 1, 1, glm::dvec3(1,1,1));

	case cylinder:
		if (isDefault) {
			return glp::cylinder((int) 1, 1, 1);
		}
		return glp::cylinder((int) 1, 1, 1, glm::dvec3(1,1,1));

	case cone:
		if (isDefault) {
			return glp::cone((int) 1, 1, 1);
		}
		return glp::cone((int) 1, 1, 1, glm::dvec3(1,1,1));
	
	case pyramid:
		if (isDefault) {
			return glp::pyramid((int) 1, 1, 1);
		}
		return glp::pyramid((int) 1, 1, 1, glm::dvec3(1,1,1));

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
		loader.LoadFile(filepath);
		std::vector<double> output;
		for (int i = 0; i < loader.LoadedVertices.size(); i++){
			output.push_back(loader.LoadedVertices[i].Position.X);
			output.push_back(loader.LoadedVertices[i].Position.Y);
			output.push_back(loader.LoadedVertices[i].Position.Z);
			output.push_back(loader.LoadedVertices[i].Normal.X);
			output.push_back(loader.LoadedVertices[i].Normal.Y);
			output.push_back(loader.LoadedVertices[i].Normal.Z);
		}
		assert (output.size() == 6 * loader.LoadedVertices.size());
		return output;
	}
}

#endif
