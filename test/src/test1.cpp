/*
 * A hello-world test for the SimpleGL library.
 */

#include <iostream>
#include <math.h>

#include "simplegl.hpp"

using namespace sgl;

void print_frame_rate(Scene *scene_ptr) {
    std::cout << "Framerate: " << scene_ptr->get_frame_rate() << "\n";
}

int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        Scene s(true);
	    s.set_callback(print_frame_rate);
        s.set_shadow(true);
        s.set_light_pos({30,30,-30});
        
        ObjId floor = s.add_obj(Shape::box, {0.6, 0.6, 0.6});
        const double radius = 5;
        for (int i=0; i<10; i++){
            ObjId sphere = s.add_obj(Shape::sphere, RED);
            ObjId truncated_cone = s.add_obj(Shape::truncatedCone, BLUE);
            ObjId cylinder = s.add_obj(Shape::cylinder, GREEN);
            ObjId cone = s.add_obj(Shape::cone, YELLOW);
            ObjId pyramid = s.add_obj(Shape::pyramid, PINK);
            ObjId torus = s.add_obj(Shape::torus, GREEN, {.r1 = 0.7, .r2 = 0.4, .accuracy = 5});
            ObjId box = s.add_obj(Shape::box, TEAL);
            ObjId kitten = s.add_obj("kitten", ORANGE, {.filepath = "./test/obj_files/kitten.obj"});
            
            double angle = (M_PI/4)*(1+i);
            sphere.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(2+i);
            truncated_cone.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(3+i);
            cylinder.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(4+i);
            cone.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(5+i);
            pyramid.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(6+i);
            torus.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(7+i);
            box.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(8+i);
            kitten.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            kitten.scale(2);
        }
        floor.translate(glm::vec3(-35, -7, -35));
        floor.scale({70, 0.01, 70});
        
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
