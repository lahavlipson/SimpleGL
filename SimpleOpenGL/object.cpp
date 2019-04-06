//
//  Object.cpp
//  SimpleOpenGL
//
//  Created by Lahav Lipson on 4/6/19.
//  Copyright © 2019 Lahav Lipson. All rights reserved.
//

#include "object.h"

void Object::rotate(float angle, glm::vec3 axis){
    model = glm::rotate(model, glm::radians(angle), axis);
}
void Object::translate(glm::vec3 translation){
    model = glm::translate(model, translation);
}
