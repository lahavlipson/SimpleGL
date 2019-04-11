#include <iostream>

#include "glp_wrapper.hpp"
#include "scene.hpp"

int main(int argc, char *argv[]){
    if (argc < 3) {
        std::cout << "Usage: " << *argv << " <vshader_fpath> <fshader_fpath>.\n";
        return 0;
    }
    
    Scene s(*(argv+1), *(argv+2));
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
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
    std::vector<double> box_params = {1,1,1};
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 color = glm::vec3(1,0.5,0.71);
    for (unsigned int i = 0; i < 10; i++) {
        mesh_id m_id = s.add_mesh(Shape::box, box_params, color, model);
        // s.reset_model(m_id);
        s.translate(m_id, cubePositions[i]);
        float angle = 20.0f * i;
        s.rotate(m_id, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    }
    s.render();
}
