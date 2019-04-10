//
//  scene.hpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/9/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include "shader_s.h"
#include <GLFW/glfw3.h>

class Scene {
    
    
    
public:
    
    Shader shader;
    
    Scene(char *vs, char *fs);
    
    // lighting
    glm::vec3 lightPos = glm::vec3(6.2f, 7.0f, 5.0f);
    
    GLFWwindow* window = nullptr;
    
};

#endif /* scene_hpp */
