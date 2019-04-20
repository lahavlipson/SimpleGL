/*
 * Test the error of giving invalid parameters to GLP. 
 * Expect add_mesh() to throw an error, and the output would be
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
        std::unordered_map<std::string, int> mmap = {{"accuracy", 1}};
        Mesh_id m_id = s.add_mesh(Shape::sphere, color, mmap);
        m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
        m_id.scale(0.5);
    
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
