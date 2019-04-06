//
//  Object.hpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/6/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
#include "parse_obj.h"
#include <vector>

class Object {
    
    Shader *shader = nullptr;

    
public:
    
    std::vector<double> vertices;
    
    Object(Shader *s, std::vector<double> verts):shader(s),vertices(verts){
        glGenVertexArrays(2, &VAO);
        glGenBuffers(2, &VBO);
        
        glBindVertexArray(VAO);
        
        std::cout << verts.size() << " SEE?\n";
        
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(double), vertices.data(), GL_STATIC_DRAW);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)(3 * sizeof(double)));
        glEnableVertexAttribArray(1);

    }
    
    

    inline void resetModel(){
        model = glm::mat4(1.0f);
    }
    
    inline void bind(){
        glBindVertexArray(VAO);
        
        
    }
    
    inline void draw(){
        shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    void rotate(float angle, glm::vec3 axis);
    void translate(glm::vec3 translation);
    
    float color[3] = {0,0,0};
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    
    
    unsigned int VBO, VAO;
    
    ~Object(){
        glDeleteVertexArrays(2, &VAO);
        glDeleteBuffers(2, &VBO);
    }
};

#endif /* Object_hpp */
