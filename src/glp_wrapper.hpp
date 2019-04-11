#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP


#include <glp/glp.h>

enum Shape { custom, sphere, truncatedCone, cylinder, cone, pyramid, torus, box};

inline std::vector<double> createGLPObj(Shape s, std::vector<double> p, bool isDefault = true){
switch(s) {
	case custom:
		return p;
		
	case sphere:
		return glp::sphere((int) p[0], p[1], glm::dvec3(p[2],p[3],p[4]));

	case truncatedCone:
		return glp::truncatedCone((int) p[0], p[1], p[2], p[3], glm::dvec3(p[4],p[5],p[6]));

	case cylinder:
		return glp::cylinder((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));

	case cone:
		return glp::cone((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));
	
	case pyramid:
		return glp::pyramid((int) p[0], p[1], p[2], glm::dvec3(p[3],p[4],p[5]));

	case torus:
		return glp::torus((int) p[0], (int) p[1], p[2], p[3], glm::dvec3(p[4],p[5],p[6]));

	case box:
		return glp::box(glm::dvec3(p[0],p[1],p[2]), glm::dvec3(p[3],p[4],p[5]));
}

}


#endif
