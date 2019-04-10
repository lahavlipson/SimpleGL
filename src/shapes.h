//
//  box.h
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/6/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#ifndef box_h
#define box_h

#include "glp.h"
#include "mesh.h"

class Box : public Mesh {
public:
    
    static unsigned int VBO, VAO, instanceCount;
    
    Box(Shader *s = nullptr, double w=1, double h=1, double d=1){
        this->shader = s;
        auto vertices = glp::box(glm::dvec3(w, h, d));
        std::cout << "instance count: " << instanceCount << std::endl;
        if (instanceCount++ == 0)
            initVAO(vertices);
    }
    
    inline void bind(){
        glBindVertexArray(VAO);
    }
    
    void initVAO(std::vector<double> vertices);
    
};

class Pyramid : public Mesh {
public:
    
    static unsigned int VBO, VAO, instanceCount;
    
    Pyramid(Shader *s = nullptr, int sides=10, double h=3, double r=1){
        this->shader = s;
        auto vertices = glp::pyramid(sides, h, r);
        std::cout << "instance count: " << instanceCount << std::endl;
        if (instanceCount++ == 0)
            initVAO(vertices);
    }
    
    inline void bind(){
        glBindVertexArray(VAO);
    }
    
    void initVAO(std::vector<double> vertices);
    
};



#endif /* box_h */
