/*
 * A hello-world test for the SimpleGL library.
 */
#include <iostream>

#include "simplegl.hpp"

using namespace sgl;

void callbackFunc(Scene *){
    std::cout << "hello world!\n";
}

int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        // Scene s(argv[1], argv[2], 800, 600, true);
        Scene s;
        s.set_callback(callbackFunc);

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
            ObjId m_id = s.add_obj(Shape::box, color);
            m_id.translate(box_positions[i]);
            float angle = 20.0f * i;
            m_id.rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
        }
        
        color = glm::vec3(0.7, 0.5, 0.5);
        obj_params oparams;
        params p = {.accuracy = 7};
        oparams.glp_params = p;
        
        // add two spheres
        ObjId m_id = s.add_obj(Shape::sphere, color, oparams);
        m_id.translate(glm::vec3(-0.2,-0.2,-0.2));
        m_id.scale(0.5);
        m_id = s.add_obj(Shape::sphere, color);
        m_id.translate(glm::vec3(-0.6,-0.6,0.6));
        m_id.scale(0.3);
        
        // add pyramid
        p = {.sides = 7};
        oparams.glp_params = p;
        m_id = s.add_obj(Shape::pyramid, color, oparams);
        m_id.translate(glm::vec3(4.2,1.2,-0.2));
        m_id.scale(0.5);
        
        ObjId floor = s.add_obj(Shape::box, {0.6, 0.6, 0.6} );
        floor.translate(glm::vec3( -35, -4, -35));
        floor.scale({70, 0.01, 70});
    
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
