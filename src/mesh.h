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

#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
#include <glp/glp.h>

#pragma clang diagnostic pop

#include <vector>


struct Translation {
    glm::vec3 rotationAxis;
    double rotationDeg;
    glm::vec3 translation;
    glm::vec3 color;
};

/*
 
 NOTE: WE MAY WANT TO MAKE THIS CLASS ABSTRACT
 
 */

class Mesh {
    
public:
    
    Shader *shader = nullptr;
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::vec3 color = {0,0,0};
    std::vector<double> vertices;
//    static unsigned int VBO, VAO;
//
//    static int instanceCount;
    
public:
    
    Mesh(){
        // init VAO
        // bind VAO
    }
    
    /*Mesh(Shader *s):shader(s){
        if (instanceCount++ == 0)
            initVAO();
    };*/
    
    virtual void initVAO(std::vector<double> vertices) = 0;
    
    virtual inline void bind() = 0;

    
    inline void setColor(glm::vec3 c){
        color = c;
    }
    
    inline void resetModel(){
        model = glm::mat4(1.0f);
    }
    
    inline void draw(){
        shader->setMat4("model", model);
        shader->setVec3("objectColor", color[0], color[1], color[2]);
        glDrawArrays(GL_TRIANGLES, 0, (int) (vertices.size() / 6));
    }
    
    inline void rotate(float angle, glm::vec3 axis){
        model = glm::rotate(model, glm::radians(angle), axis);
    }
    inline void translate(glm::vec3 translation){
        model = glm::translate(model, translation);
    }
    
    ~Mesh(){
//        instanceCount--;
////        glDeleteVertexArrays(1, &VAO);
////        glDeleteBuffers(1, &VBO);
    }
};

#endif /* Object_hpp */
