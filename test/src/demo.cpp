/*
 * A hello-world test for the SimpleGL library.
 */
#include <iostream>
#include <functional>
#include <math.h>
#include "simplegl.hpp"


using namespace sgl;

int main(int argc, char *argv[]) {
    try {
        // initialize the scene.
        Scene s(true);
	
        s.set_shadow(true);
        s.set_light_pos({30,30,-30});
        
        const double radius = 5;
        for (int i=0; i<10; i++){
            double angle = (M_PI/4)*(1+i);
            ObjId id = s.add_obj(Shape::sphere, RED);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(2+i);
            id = s.add_obj(Shape::truncatedCone, BLUE);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(3+i);
            id = s.add_obj(Shape::cylinder, GREEN);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(4+i);
            id = s.add_obj(Shape::cone, YELLOW);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(5+i);
            id = s.add_obj(Shape::pyramid, PINK);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(6+i);
            id = s.add_obj(Shape::torus, GREEN, {.r1 = 0.7, .r2 = 0.4, .accuracy=5});
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(7+i);
            id = s.add_obj(Shape::box, TEAL);
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            angle = (M_PI/4)*(8+i);
            id = s.add_obj("cat", ORANGE, {.filepath = "./test/obj_files/kitten.obj"});
            id.translate({radius*cos(angle),radius*sin(angle), -5 - i*6});
            id.scale(2);
        }
        
        ObjId floor = s.add_obj(Shape::box, {0.6, 0.6, 0.6} );
        floor.translate(glm::vec3(-35, -7, -35));
        floor.scale({70, 0.01, 70});
        
        // render the scene.
        s.render();
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
    }
}
