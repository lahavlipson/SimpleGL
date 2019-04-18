/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>

#include "scene.hpp"

// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]){
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
    // add the ten boxes
    glm::vec3 color = glm::vec3(1.0,0.5,0.71);
    for (unsigned int i = 0; i < 10; i++) {
        mesh_id m_id = s.add_mesh(Shape::box, color);
        s.translate(m_id, box_positions[i]);
        float angle = 20.0f * i;
        s.rotate(m_id, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    }
    
    // add two spheres
    color = glm::vec3(0.7, 0.5, 0.5);
    std::map<std::string, double> mymap = {{"accuracy",7}};
    mesh_id m_id = s.add_mesh(Shape::sphere, color, mymap);
    s.translate(m_id, glm::vec3(-0.2,-0.2,-0.2));
    m_id = s.add_mesh(Shape::sphere, color, mymap);
    s.translate(m_id, glm::vec3(-0.6,-0.6,-0.6));

    // add one obj
    if (argc > 1) {
        mesh_id obj_m_id = s.add_mesh(Shape::obj, color, *(argv+1));
        s.scale(obj_m_id, 0.08);
    }
    
    // render the scene.
    s.render();
}
