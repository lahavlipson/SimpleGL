#include "simplegl.hpp"

using namespace sgl;

int main(int argc, char** argv) {

    Scene s; // create a Scene object

    // add a default sphere and default box
    ObjId my_sphere = s.add_obj(Shape::sphere);
    ObjId my_box = s.add_obj(Shape::box);

    // add a default box with a color
    color my_color(0.6, 0.6, 0.6);
    ObjId my_box2 = s.add_obj(Shape::box, my_color);

    // add pyramid with 7 sides 
    obj_params oparams;
    oparams.sides = 7;
    ObjId my_pyramid = s.add_obj(Shape::pyramid, my_color, oparams);

    // add a composite object
    obj_params op_composite;
    op_composite.comp = {my_sphere.duplicate(), my_box.duplicate()};
    ObjId c = s.add_obj(Shape::composite, my_color, op_composite);

    // add an object loaded from .obj file
    obj_params op_kitten;
    op_kitten.filepath = "/path/to/kitten.obj"; // replace with correct path
    ObjId my_kitten = s.add_obj("kitten", my_color, op_kitten);

    // perform translations
    my_pyramid.translate(glm::vec3(-0.2, 1.2, -0.2));
    my_pyramid.scale(0.2);
    my_pyramid.set_color({1.0, 0.5, 0.3});	

    my_sphere.translate(glm::vec3(2, 0.8, -0.5));
    my_sphere.scale(0.4);
    my_sphere.set_color({0.4, 0.2, 0.3});	

    my_box.translate(glm::vec3(0.1, 1, -0.8));
    my_box.scale(0.2);
    my_box.set_color({0.2, 0.8, 0.9});	
    my_box.rotate(30, glm::vec3(1, 1, 0));

    // make this a floor
    my_box2.translate(glm::vec3(-35, -4, -35));
    my_box2.scale({70, 0.01, 70}); // make this box REALLY big
    c.translate(glm::vec3(1, .1, -0.2));
    c.scale(0.3);	
    c.set_color({0.1, 0.8, 0.6});	

    my_kitten.scale(0.5);
    my_kitten.set_color({0.8, 0.6, 0.8});

    s.render();

}
