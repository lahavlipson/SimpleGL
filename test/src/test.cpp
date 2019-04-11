#include <iostream>

#include "mesh.h"
#include "shapes.h"
#include "scene.hpp"

int main(int argc, char *argv[]){
    if (argc < 3) {
        std::cout << "Usage: " << *argv << " <vshader_fpath> <fshader_fpath>.\n";
        return 0;
    }
    Scene s(*(argv+1), *(argv+2));

    Mesh *cubeObj = new Box;
    cubeObj->setColor({1,0.5,0.71});
    s.meshes.push_back(cubeObj);
    s.render();
}
