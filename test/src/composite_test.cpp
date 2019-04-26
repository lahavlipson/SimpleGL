/*
 * A test for the SimpleGL library, specifically the composite objects.
 */

#include <iostream>

#include "scene.hpp"

// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << *argv << " <path_to_kitten_obj>\n";
        return 0;
    }
    // initialize the scene.
    Scene s;

    // add a composite object of a kitten mesh and a default cone.
    glm::vec3 color = glm::vec3(0.7, 0.5, 0.5);
    Mesh_id cone = s.add_mesh(Shape::cone, color);
    color = glm::vec3(0.8, 0.6, 0.8);
    Mesh_id obj = s.add_mesh("kitten", color, *(argv+1));
    Comp_id c1 = s.add_composite({cone, obj});

    // order of transformations doesn't matter
    c1.scale(0.5);
    c1.translate(glm::vec3(-1, 0, 0));
    cone.translate(glm::vec3(0, 0.2, 0));
    cone.scale({0.1, 0.3, 0.1});
    obj.rotate(20, glm::vec3(0, 1, 0));

    // add another composite of the same components' copies.
    // duplicate() adds a copy of the instance in the Mesh_id.
    Comp_id c2 = s.add_composite({cone.duplicate(), obj.duplicate()});
    c2.translate(glm::vec3(1, 0, 0));

    // render the scene.
    s.render();
}
