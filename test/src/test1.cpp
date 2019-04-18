/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>

#include "glp_wrapper.hpp"
#include "scene.hpp"
#include <thread>
#include <unistd.h>

class Simulation {
    
public:
    
    bool stopSim = false;
    
    Scene *s = nullptr;
    
    inline void cancel(){
        stopSim = true;
        std::cout << "canceled\n";
    }
    
    Simulation(Scene *scn):s(scn){}
    
    inline void physics(std::vector<mesh_id> ids)
    {
        const double t = 0.1;
        double v1 = 0;
        while (!stopSim){
            
            double ball1Height = s->get_loc(ids[1])[1];
            double F1 = (4.0 - ball1Height);
            //std::cout << ball1Height << " " << F1 << " " << v1 << " " << t*v1 << " " << float(t*v1) << "\n";

            v1 += t*F1;

//            std::cout << F1 << "\n";

            s->translate(ids[1], {0.0, v1*t, 0.0});
            
            double newBall1Height = s->get_loc(ids[1])[1];
            s->scale(ids[2], glm::vec3(1, newBall1Height/ball1Height, 1));
            
            usleep(10000);
            
//            s->translate(ids[1], glm::vec3(0.0,0.000001,0.0));
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
    s.translate(spring_id, glm::vec3(0, 0.45, -3));
    s.scale(spring_id, {0.4, 0.6, 0.4});
    
    
    Simulation sim(&s);
    
    std::vector<mesh_id> ids = {id_1, id_2, spring_id};
    std::thread t1(&Simulation::physics, &sim, ids);
    
    // render the scene.
    s.render();
    
    sim.cancel();
    
    t1.join();
}
