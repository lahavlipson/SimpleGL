/*
 * Test the error of giving invalid parameters to GLP. 
 * Expect add_obj() to throw an error, and the output would be
 * "SimpleGL status: invalid parameter".
 */

#include <iostream>

#include "scene.hpp"

int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        Scene s;
        
        // add one sphere with too low accuracy
        glm::vec3 color = glm::vec3(0.7, 0.5, 0.5);
        obj_params params;
        std::unordered_map<std::string, int> mmap = {{"accuracy", 1}};
        params.glp_params = mmap;
        ObjId m_id = s.add_obj(Shape::sphere, color, params);
        m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
        m_id.scale(0.5);
    
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
