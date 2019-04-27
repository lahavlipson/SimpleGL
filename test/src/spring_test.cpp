#include <iostream>
#include <thread>
#include <unistd.h>

#include "simplegl.hpp"

using namespace sgl;

class Spring {

public:
    Spring(Mesh_id a, Mesh_id b, Mesh_id s, double restL, double constant):id1(a),id2(b), obj_id(s),k(constant), rest(restL) {}

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
    
    
    inline void physics(std::vector<Spring> springs)
    {
        
        glm::vec3 vel = {0.3, 0, -0.3};
        while (!stopSim){
            
            glm::vec3 force = gravity;
            for (Spring &spr : springs)
                force += spr.force();

            vel += force*t;
            springs[0].id2.translate(vel*t);
            
            for (Spring &spr : springs){
                glm::vec3 crossProd = glm::cross(glm::vec3(0,1,0.000001), spr.dir());
                float angleDiff = glm::degrees(float(acos(glm::dot(spr.dir(), {0,1,0}))));
                spr.obj_id.set_rotation(angleDiff, crossProd);
                spr.obj_id.set_scale({0.4,spr.length()*0.17,0.4});
            }
            
            usleep(12000);
        }
    }
    
};



// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]){
    if (argc < 3) {
        std::cout << "Usage: " << *argv << " <coil_obj_filepath> <other_obj_filepath> \n";
        return 0;
    }
    // initialize the scene.
    Scene s;
    const double height = -2.5;
    
    color col = glm::vec3(0.7, 0.5, 0.5);
    Mesh_id center_obj = s.add_mesh("kitten", col, argv[2]);
    center_obj.translate(glm::vec3(0,height + 3.5,-3));
    center_obj.scale(3.0);

    
    std::vector<Spring> springs;
    const double spring_constant = 1.0;
    
    Mesh_id ball_1 = s.add_mesh(Shape::sphere, col );
    ball_1.translate(glm::vec3(0, height, -3));
    ball_1.scale(0.5);
    Mesh_id spring_1 = s.add_mesh("spring_1", {0.4, 0.4, 0.4}, argv[1]);
    spring_1.translate(glm::vec3(0, height, -3));
    springs.push_back(Spring(ball_1, center_obj, spring_1, 4.0, spring_constant));
    
    Mesh_id ball_2 = s.add_mesh(Shape::sphere, col );
    ball_2.translate(glm::vec3(-3, height, -3));
    ball_2.scale(0.5);
    Mesh_id spring_2 = s.add_mesh("spring_2", {0.4, 0.4, 0.4}, argv[1]);
    spring_2.translate(glm::vec3(-3, height, -3));
    springs.push_back(Spring(ball_2, center_obj, spring_2, 4.0, spring_constant));
    
    
    Mesh_id ball_3 = s.add_mesh(Shape::sphere, col );
    ball_3.translate(glm::vec3(-1.5, height, -6));
    ball_3.scale(0.5);
    Mesh_id spring_3 = s.add_mesh("spring_3", {0.4, 0.4, 0.4}, argv[1]);
    spring_3.translate(glm::vec3(-1.5, height, -6));
    springs.push_back(Spring(ball_3, center_obj, spring_3, 4.0, spring_constant));
    
    Simulation sim;
    
    std::thread t1(&Simulation::physics, &sim, springs);
    
    // render the scene.
    s.render();
    
    sim.cancel();
    
    t1.join();
}
