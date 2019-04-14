#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <glp/glp.h>
#include <obj_loader/obj_loader.h>

#include <variant>

enum Shape { custom, sphere, truncatedCone, cylinder, cone, pyramid, torus, box, obj };

inline std::vector<double> createGLPObj(
    const Shape s, const std::variant<std::vector<double>, std::string> varP, const bool isDefault = true) {
    
	std::vector<double> p;
	std::string filepath;
	if (std::holds_alternative<std::vector<double>>(varP)) {
		p = std::get<std::vector<double>>(varP);
	} else {
		filepath = std::get<std::string>(varP);
	}

	switch (s) {
	case custom:
		// p is the vertices for Shape::custom, directly return
		return p;
		
	case sphere:
		if (isDefault) {
			return glp::sphere((int) p[0], p[1]);
		}
		return glp::sphere((int) p[0], p[1], glm::dvec3(p[2],p[3],p[4]));

	case truncatedCone:
		if (isDefault) {
			return glp::truncatedCone((int) p[0], p[1], p[2], p[3]);
		}
		return glp::truncatedCone((int) p[0], p[1], p[2], p[3], glm::dvec3(p[4],p[5],p[6]));

	case cylinder:
		if (isDefault) {
			return glp::cylinder((int) p[0], p[1], p[2]);
		}
		return glp::cylinder((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));

	case cone:
		if (isDefault) {
			return glp::cone((int) p[0], p[1], p[2]);
		}
		return glp::cone((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));
	
	case pyramid:
		if (isDefault) {
			return glp::pyramid((int) p[0], p[1], p[2]);
		}
		return glp::pyramid((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));

	case torus:
		if (isDefault) {
			return glp::torus((int) p[0], (int) p[1], p[2], p[3]);
		}
		return glp::torus((int) p[0], (int) p[1], p[2], p[3], glm::dvec3(p[4],p[5],p[6]));

	case box:
		if (isDefault) {
			return glp::box(glm::dvec3(p[0],p[1],p[2]));
		}
		return glp::box(glm::dvec3(p[0],p[1],p[2]), glm::dvec3(p[3],p[4],p[5]));

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
