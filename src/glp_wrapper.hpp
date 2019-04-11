#ifndef GLP_WRAPPER_HPP
#define GLP_WRAPPER_HPP

#include <glp/glp.h>

enum Shape { custom, sphere, truncatedCone, cylinder, cone, pyramid, torus, box};

inline std::vector<double> createGLPObj(Shape s, std::vector<double> p, bool isDefault = true) {
	switch(s) {
		case custom:
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
	}
}

#endif
