/*
 * Test loading multiple .obj files and related errors.
 */

#include <iostream>
#include <sstream>

#include "simplegl.hpp"
std::string get_obj_name(std::string obj_arg) {
    std::stringstream ss(obj_arg);
    std::string item;
    while (std::getline(ss, item, '/')) {}
    return item.substr(0, item.length() - 4);
}

int main(int argc, char *argv[]) {
    try {
        // add multiple objs to the scene.
        if (argc > 1) {
            // initialize the scene.
            Scene s;
            int i = 1;
            while (i < argc) {
                std::string fpath(*(argv+i));
                std::cout << i << " " << fpath << "\n";

                // Expected error: if fpath doesn't exist, will terminate.
                Mesh_id obj_m_id = s.add_mesh(get_obj_name(fpath), 
                    glm::vec3(0.1*i, 0.15*i, 0.2*i), fpath);
                /* Comment the above and uncommment the following two lines to 
                 * see the expected error when we didn't provide a filepath. */
                // std::unordered_map<std::string, int> mmap = {{"accuracy", 1}};
                // Mesh_id obj_m_id = s.add_mesh(get_obj_name(fpath), 
                //     glm::vec3(0.5, 0.7, 0.3), mmap);
                
                obj_m_id.rotate(i, glm::vec3(1, 1, 1));
                obj_m_id.translate(glm::vec3(i, i, i));
                obj_m_id.scale(glm::vec3(0.1*i, 0.15*i, 0.2*i));
                i++;
            }
            // render the scene.
            s.render();
        } else {
            std::cout << "Usage: " << *argv << " <obj1_filepath> [optional_obj2_path] [optional_obj3_path] ...\n";
            return 0;
        }
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
