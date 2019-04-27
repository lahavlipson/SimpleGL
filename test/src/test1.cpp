/*
 * A hello-world test for the SimpleGL library.
 */
#include <iostream>

#include "simplegl.hpp"

using namespace sgl;

int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        Scene s;

        // world space positions for the ten boxes
        glm::vec3 box_positions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        // add ten boxes
        glm::vec3 color = glm::vec3(1.0,0.5,0.71);
        for (unsigned int i = 0; i < 10; i++) {
            Mesh_id m_id = s.add_mesh(Shape::box, color);
            m_id.translate(box_positions[i]);
            float angle = 20.0f * i;
            m_id.rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
        }
        
        // add two spheres
        color = glm::vec3(0.7, 0.5, 0.5);
        std::unordered_map<std::string, int> mymap = {{"accuracy",7}};
        Mesh_id m_id = s.add_mesh(Shape::sphere, color, mymap );
        m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
        m_id.scale(0.5);
        m_id = s.add_mesh(Shape::sphere, color);
        m_id.translate(glm::vec3(-0.6,-0.6,0.6));
        m_id.scale(0.3);
        
        // add pyramid
        mymap = {{"sides",7}};
        m_id = s.add_mesh(Shape::pyramid, color, mymap );
        m_id.translate(glm::vec3(4.2,1.2,-0.2));
        m_id.scale(0.5);
        
        Mesh_id floor = s.add_mesh(Shape::box, {0.6, 0.6, 0.6} );
        floor.translate(glm::vec3( -35, -4, -35));
        floor.scale({70, 0.01, 70});
    
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
