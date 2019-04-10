//
//  scene.cpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/9/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#include "scene.hpp"

Scene::Scene(char *vs, char *fs){
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        abort();
    }
    
    // Initialize Shader
    shader = Shader(vs, fs);
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader.use();
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos", lightPos);
    
    
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    
}


