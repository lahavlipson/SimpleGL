#include "simplegl.hpp"
using namespace sgl;
int main(int argc, char** argv){

Scene s; // default screen size is 800 x 600

// add a default sphere and default box
ObjId my_sphere = s.add_obj(Shape::sphere);
ObjId my_box = s.add_obj(Shape::box);
// add a default box with a color
color myColor = glm::vec3(0.8, 0.6, 0.8);
ObjId my_box2 = s.add_obj(Shape::box, myColor);

// add pyramid with 7 sides 
obj_params oparams;
params p = {.accuracy = 7};
oparams.glp_params = p;
ObjId my_pyramid = s.add_obj(Shape::pyramid, myColor, oparams); // myColor is defined above

// we created my_sphere and my_box above
obj_params opComposite;
opComposite.comp = {my_sphere, my_box};
ObjId c1 = s.add_obj(Shape::composite, myColor, opComposite);



obj_params oparamKitten;
oparamKitten.glp_params = "/path/to/test/obj_files/kitten.obj"; // replace this with your filepath
ObjId my_kitten = s.add_obj("kitten", myColor, oparamKitten);


my_pyramid.translate(glm::vec3(4.2,1.2,-0.2));
my_pyramid.scale(0.5);

s.render();

}
