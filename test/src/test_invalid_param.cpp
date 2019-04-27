/*
 * Test the error of giving invalid parameters to GLP. 
 * Expect add_obj() to throw an error, and the output would be
 * "SimpleGL status: invalid parameter".
 */

#include <iostream>

#include "simplegl.hpp"

using namespace sgl;
int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        Scene s;
        
        // add one sphere with too low accuracy
        glm::vec3 color = glm::vec3(0.7, 0.5, 0.5);
        obj_params oparams;
        params p = {.accuracy = 1};
        oparams.glp_params = p;
        ObjId m_id = s.add_obj(Shape::sphere, color, oparams);
        m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
        m_id.scale(0.5);
    
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
