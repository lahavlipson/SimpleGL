/*
 * A test for the SimpleGL library, specifically the composite objects.
 */
#include <iostream>

#include "simplegl.hpp"

using namespace sgl;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << *argv << " <path_to_kitten_obj>\n";
        return 0;
    }
    // initialize the scene.
    Scene s;

    glm::vec3 color = glm::vec3(0.7, 0.5, 0.5);
    obj_params oparams;
    std::unordered_map<std::string, int> mymap = {{"accuracy",7}};
    oparams.glp_params = argv[1];

    // add a composite object of a kitten mesh and a default cone.
    ObjId cone = s.add_obj(Shape::cone, color);
    color = glm::vec3(0.8, 0.6, 0.8);
    ObjId obj = s.add_obj("kitten", color, oparams);
    oparams.comp = {cone, obj};
    ObjId c1 = s.add_obj(Shape::composite, color, oparams);

    // order of transformations doesn't matter
    c1.scale(0.5);
    c1.translate(glm::vec3(-1, 0, 0));
    cone.translate(glm::vec3(0, 0.2, 0));
    cone.scale({0.1, 0.3, 0.1});
    obj.rotate(20, glm::vec3(0, 1, 0));

    // add the second composite of the same components' copies.
    // duplicate() adds a copy of the instance in the ObjId.
    oparams.comp = {cone.duplicate(), obj.duplicate()};
    ObjId c2 = s.add_obj(Shape::composite, color, oparams);
    c2.translate(glm::vec3(1, 0, 0));

    // add the third composite of the same components' copies.
    // by directly duplicating the composite. 
    ObjId c3 = c2.duplicate();
    c3.translate(glm::vec3(1, 1, 0));

    // render the scene.
    s.render();
}
