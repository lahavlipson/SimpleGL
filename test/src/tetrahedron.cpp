/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>

#include "scene.hpp"
#include <thread>
#include <set>
#include <unistd.h>

class Mass {
    
public:
    
    Mesh_id id;
    glm::vec3 vel = {0,0,0};
    glm::vec3 force = {0,0,0};
    
    Mass(Mesh_id mid):id(mid){}
    
    inline glm::vec3 get_loc(){
        return id.get_loc();
    }
    
    inline void translate(glm::vec3 t){
        id.translate(t);
    }
  
    inline void set_scale(glm::vec3 s){
        id.set_scale(s);
    }
    
    inline void set_rotation(double angle, glm::vec3 ax){
        id.set_rotation(angle, ax);
    }
    
};

class Spring {

public:

    Spring(Mass &a, Mass &b, Mesh_id s, double restL, double constant):id1(a),id2(b),k(constant), obj_id(s) {
        rest = length();
    }

    Mass &id1;
    Mass &id2;
    Mesh_id obj_id;
    const float k;
    float rest;

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
    
    const float t = 0.001f;
    const glm::vec3 gravity = {0, -0.8, 0};
    
    bool stopSim = false;
    
    inline void cancel(){
        stopSim = true;
    }
    
    Simulation(){}
    
    
    inline void physics(std::vector<Spring> springs, std::vector<Mass> masses)
    {

        
        while (!stopSim){
            
            for (Spring &spr : springs){
                double rel_h = spr.id1.get_loc()[1] + 7;
                if (rel_h < 0)
                    spr.id1.force = gravity + glm::vec3(0, -100*rel_h, 0);
                else
                    spr.id1.force = gravity;
                
                    
                    rel_h = spr.id2.get_loc()[1] + 7;
                if (rel_h < 0)
                    spr.id2.force = gravity + glm::vec3(0, -100*rel_h, 0);
                else
                    spr.id2.force = gravity;
            }
            
            for (Spring &spr : springs){
               spr.id2.force += spr.force();
               spr.id1.force -= spr.force();
            }

            springs[0].id1.vel += springs[0].id1.force*t;
            springs[1].id1.vel += springs[1].id1.force*t;
            springs[2].id1.vel += springs[2].id1.force*t;
            springs[0].id2.vel += springs[0].id2.force*t;
            
            springs[0].id1.vel*= 0.99999;
            springs[1].id1.vel*= 0.99999;
            springs[2].id1.vel*= 0.99999;
            springs[0].id2.vel*= 0.99999;
            
            springs[0].id1.translate(springs[0].id1.vel*t);
            springs[1].id1.translate(springs[1].id1.vel*t);
            springs[2].id1.translate(springs[2].id1.vel*t);
            springs[0].id2.translate(springs[0].id2.vel*t);
            
            for (Spring &spr : springs){
                spr.obj_id.set_translation(spr.id1.get_loc());
                glm::vec3 crossProd = glm::cross(glm::vec3(0,1,0.000001), spr.dir());
                float angleDiff = glm::degrees(float(acos(glm::dot(spr.dir(), {0,1,0}))));
                spr.obj_id.set_rotation(angleDiff, crossProd);
                spr.obj_id.set_scale({0.4,spr.length()*0.17,0.4});
            }
           // usleep(30);
        }
    }
    
};



// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]){
    // initialize the scene.
    Scene s;
    const double height = 2.5;
    
    color col = glm::vec3(0.7, 0.5, 0.5);
    std::vector<Mass> masses;
    
    Mesh_id ball_0 = s.add_mesh(Shape::sphere, col );
    ball_0.translate(glm::vec3(-1.5,height + 3,-3));
    ball_0.scale(0.5);
    Mass m0(ball_0);
    masses.push_back(m0);

    Mesh_id ball_1 = s.add_mesh(Shape::sphere, col );
    ball_1.translate(glm::vec3(0, height, -3));
    ball_1.scale(0.5);
    Mass m1(ball_1);
    masses.push_back(m1);
    
    Mesh_id ball_2 = s.add_mesh(Shape::sphere, col );
    ball_2.translate(glm::vec3(-3, height, -3));
    ball_2.scale(0.5);
    Mass m2(ball_2);
    masses.push_back(m2);
    
    Mesh_id ball_3 = s.add_mesh(Shape::sphere, col );
    ball_3.translate(glm::vec3(-1.5, height, -6));
    ball_3.scale(0.5);
    Mass m3(ball_3);
    masses.push_back(m3);
    
    std::vector<Spring> springs;
    const double spring_constant = 32.5;
    
    
    
    
    Mesh_id spring_1 = s.add_mesh("spring_1", {0.4, 0.4, 0.4}, argv[1]);
    spring_1.translate(glm::vec3(0, height, -3));
    springs.push_back(Spring(m1, m0, spring_1, 4.0, spring_constant));
    
    Mesh_id spring_2 = s.add_mesh("spring_2", {0.4, 0.4, 0.4}, argv[1]);
    spring_2.translate(glm::vec3(-3, height, -3));
    springs.push_back(Spring(m2 ,m0, spring_2, 4.0, spring_constant));
    
    Mesh_id spring_3 = s.add_mesh("spring_3", {0.4, 0.4, 0.4}, argv[1]);
    spring_3.translate(glm::vec3(-1.5, height, -6));
    springs.push_back(Spring(m3, m0, spring_3, 4.0, spring_constant));

    Mesh_id spring_4 = s.add_mesh("spring_4", {0.4, 0.4, 0.4}, argv[1]);
    spring_4.translate(glm::vec3(0, height, -3));
    springs.push_back(Spring(m1, m2, spring_4, 4.0, spring_constant));
    
    Mesh_id spring_5 = s.add_mesh("spring_5", {0.4, 0.4, 0.4}, argv[1]);
    spring_5.translate(glm::vec3(0, height, -3));
    springs.push_back(Spring(m1, m3, spring_5, 4.0, spring_constant));
    
    Mesh_id spring_6 = s.add_mesh("spring_6", {0.4, 0.4, 0.4}, argv[1]);
    spring_6.translate(glm::vec3(0, height, -3));
    springs.push_back(Spring(m2, m3, spring_6, 4.0, spring_constant));
    
    
    
    Mesh_id floor = s.add_mesh(Shape::box, {0.6, 0.6, 0.6} );
    floor.translate(glm::vec3( -35, -7.5, -35));
    floor.scale({70, 0.01, 70});

    
    
    Simulation sim;
    
    std::thread t1(&Simulation::physics, &sim, springs, masses);
    
    // render the scene.
    s.render();
    
    sim.cancel();
    
    t1.join();
}
