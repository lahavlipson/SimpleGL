/*
 * A test for the SimpleGL library, specifically manipulating meshes.
 */
#include <iostream>

#include "simplegl.hpp"

using namespace sgl;

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
    // add ten boxes and remove all instances of box
    Color pink(1.0,0.5,0.71);
    for (unsigned int i = 0; i < 10; i++) {
        ObjId m_id = s.add_obj(Shape::box, pink);
        m_id.translate(box_positions[i]);
        float angle = 20.0f * i;
        m_id.rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
    }
    s.remove_obj_all(Shape::box);

    // add two spheres and hide the first one
    Color pink_gray(0.7, 0.5, 0.5);
    ObjId m_id = s.add_obj(Shape::sphere, pink_gray, {.accuracy = 7});
    m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
    m_id.hide();
    m_id = s.add_obj(Shape::sphere, pink_gray, {.accuracy = 7});
    m_id.translate(glm::vec3(-0.6,-0.6,-0.6));
    m_id.show();
    // s.remove_obj_all(Shape::sphere);

    // add one obj
    if (argc > 1) {
        ObjId obj_m_id = s.add_obj("object1", pink_gray, {.filepath = argv[1]});
        obj_m_id.scale(0.08);
    }
    // s.remove_obj_all("object1");

    // render the scene.
    s.render();
}
