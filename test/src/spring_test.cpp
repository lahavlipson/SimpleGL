/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>

#include "scene.hpp"
#include <thread>
#include <unistd.h>

class Spring {

public:

    Spring(Mesh_id a, Mesh_id b, Mesh_id s, double restL, double constant):id1(a),id2(b),k(constant), rest(restL), obj_id(s) {}

    Mesh_id id1;
    Mesh_id id2;
    Mesh_id obj_id;
    const float k;
    const float rest;

    inline glm::vec3 getP1(){
        return id1.get_loc();
    }
    
    inline glm::vec3 getP2(){
        return id2.get_loc();
    }
    
    inline float length(){
        const glm::vec3 p1 = getP1();
        const glm::vec3 p2 = getP2();
        return glm::distance(p1, p2);
    }
    
    inline glm::vec3 dir(){
        return glm::normalize(getP2() - getP1());
    }

    inline glm::vec3 force(){
        return k*(rest - length())*dir();
    }

};

class Simulation {
    
public:
    
    const float t = 0.1f;
    const glm::vec3 gravity = {0, -0.3, 0};
    
    bool stopSim = false;
    
    inline void cancel(){
        stopSim = true;
    }
    
    Simulation(){}
    
    
    inline void physics(Spring spr)
    {
        
        glm::vec3 v1 = {0.3, 0, -0.3};
        while (!stopSim){
            
            glm::vec3 F1 = spr.force() + gravity;

            v1 += F1*t;

            spr.id2.translate(v1*t);
            
            glm::vec3 crossProd = glm::cross(glm::vec3(0,1,0.000001), spr.dir());
            float angleDiff = glm::degrees(float(acos(glm::dot(spr.dir(), {0,1,0}))));
            spr.obj_id.set_rotation(angleDiff, crossProd);
            spr.obj_id.set_scale({0.4,spr.length()*0.17,0.4});
            
            
            usleep(12000);
        }
    }
    
};



// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]){
    // initialize the scene.
    Scene s;

    
    color col = glm::vec3(0.7, 0.5, 0.5);
    Mesh_id ball_1 = s.add_mesh(Shape::sphere, col );
    ball_1.translate(glm::vec3(0, 0, -3));
    ball_1.scale(0.5);
    Mesh_id spring_1 = s.add_mesh("spring_1", {0.4, 0.4, 0.4}, argv[1]);
    spring_1.translate(glm::vec3(0, 0, -3));
    
    Mesh_id center_ball = s.add_mesh(Shape::sphere, col);
    center_ball.translate(glm::vec3(0,3.5,-3));
    center_ball.scale(0.5);
    
    
    
    
    
    
    
    
    
    
    
    
    Simulation sim;
    
    std::vector<Mesh_id> ids = {ball_1, center_ball, spring_1};
    Spring spring(ball_1, center_ball, spring_1, 4.0, 2.0);
    
    std::thread t1(&Simulation::physics, &sim, spring);
    
    // render the scene.
    s.render();
    
    sim.cancel();
    
    t1.join();
}
