/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>

#include "glp_wrapper.hpp"
#include "scene.hpp"
#include <thread>
#include <unistd.h>

class Spring {

public:

    Spring(mesh_id a, mesh_id b, mesh_id s, double restL, double constant):id1(a),id2(b),k(constant), rest(restL), obj_id(s) {}

    mesh_id id1;
    mesh_id id2;
    mesh_id obj_id;
    const float k;
    const float rest;

    inline glm::vec3 getP1(Scene *s){
        return s->get_loc(id1);
    }
    
    inline glm::vec3 getP2(Scene *s){
        return s->get_loc(id2);
    }
    
    inline float length(Scene *s){
        const glm::vec3 p1 = getP1(s);
        const glm::vec3 p2 = getP2(s);
        return glm::distance(p1, p2);
    }
    
    inline glm::vec3 dir(Scene *s){
        return glm::normalize(getP2(s) - getP1(s));
    }

    inline glm::vec3 force(Scene *s){
        return k*(rest - length(s))*dir(s);
    }

};

class Simulation {
    
public:
    
    bool stopSim = false;
    
    Scene *s = nullptr;
    
    inline void cancel(){
        stopSim = true;
    }
    
    Simulation(Scene *scn):s(scn){}
    
    
    inline void physics(Spring spr)
    {
        
        s->reset_model(spr.obj_id);
        s->translate(spr.obj_id, glm::vec3(0, 0, -3));
        s->scale(spr.obj_id, {0.4, 0.6, 0.4});
        
        s->rotate(spr.obj_id, 0, glm::vec3(-1,0,0));
        const float t = 0.1f;
        glm::vec3 v1 = {0, 0, -0.3};
        while (!stopSim){
            
            double ball1Height = spr.getP2(s) [1];
            const glm::vec3 oldDir = spr.dir(s);
            glm::vec3 F1 = spr.force(s);

            v1 += F1*t;

            s->translate(spr.id2, v1*t);
            
            double newBall1Height = spr.getP2(s)[1];
            glm::vec3 crossProd = glm::cross(glm::vec3(0,1,0.000001), spr.dir(s));
            
            float angleDiff = glm::degrees(float(acos(glm::dot(spr.dir(s), oldDir))));
            s->rotate(spr.obj_id, angleDiff, glm::vec3(-1,0,0));
            
            //s->scale(spr.obj_id, {1,ball1Height/newBall1Height,1});
            usleep(10000);
            
        }
    }
    
};



// takes one command line argument to a filepath to a .obj file to be rendered
int main(int argc, char *argv[]){
    // initialize the scene.
    Scene s;

    
    // add two spheres
    color col = glm::vec3(0.7, 0.5, 0.5);
    mesh_id id_1 = s.add_mesh(Shape::sphere, col );
    s.translate(id_1, glm::vec3(0, 0, -3));
    s.scale(id_1, 0.5);
    mesh_id id_2 = s.add_mesh(Shape::sphere, col);
    s.translate(id_2, glm::vec3(0,3.5,-3));
    s.scale(id_2, 0.5);
    
    mesh_id spring_id = s.add_mesh(Shape::obj, {0.4, 0.4, 0.4}, argv[1]);
    
    
    
    Simulation sim(&s);
    
    std::vector<mesh_id> ids = {id_1, id_2, spring_id};
    Spring spring(id_1, id_2, spring_id, 4.0, 2.0);
    
    std::thread t1(&Simulation::physics, &sim, spring);
    
    // render the scene.
    s.render();
    
    sim.cancel();
    
    t1.join();
}
