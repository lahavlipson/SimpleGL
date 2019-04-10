//
//  shapes.cpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/10/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#include <stdio.h>

#include "shapes.h"

unsigned int Box::instanceCount = 0;
unsigned int Box::VBO;
unsigned int Box::VAO;
unsigned int Pyramid::instanceCount = 0;
unsigned int Pyramid::VBO;
unsigned int Pyramid::VAO;


void Box::initVAO(std::vector<double> vertices){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
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

void Pyramid::initVAO(std::vector<double> vertices){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
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
