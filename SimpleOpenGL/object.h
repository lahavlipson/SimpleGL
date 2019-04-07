//
//  Object.hpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/6/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#ifndef OBJECT_H
#define OBJECT_H

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
#include "parse_obj.h"
#include "glp.h"

#pragma clang diagnostic pop

#include <vector>


class Object {
    
public:
    
    Shader *shader = nullptr;
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    std::vector<double> vertices;
    glm::vec3 color = {0,0,0};
    unsigned int VBO, VAO;
    
public:
    
    Object(){
        
    }
    
    Object(Shader *s):shader(s){
        vertices = glp::box(glm::dvec3(1.2, 1.2, 0.4));
        initVAO();
    };
    
    void initVAO();
    
    inline void setColor(glm::vec3 c){
        color = c;
    }
    
    inline void resetModel(){
        model = glm::mat4(1.0f);
    }
    
    inline void bind(){
        glBindVertexArray(VAO);
    }
    
    inline void draw(){
        shader->setMat4("model", model);
        shader->setVec3("objectColor", color[0], color[1], color[2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    inline void rotate(float angle, glm::vec3 axis){
        model = glm::rotate(model, glm::radians(angle), axis);
    }
    inline void translate(glm::vec3 translation){
        model = glm::translate(model, translation);
    }
    
    ~Object(){
        glDeleteVertexArrays(2, &VAO);
        glDeleteBuffers(2, &VBO);
    }
};

#endif /* Object_hpp */
