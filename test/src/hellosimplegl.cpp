#include "simplegl.hpp"

using namespace sgl;

int main(int argc, char** argv){

	Scene s; // create a Scene object

	// add a default sphere and default box
	ObjId my_sphere = s.add_obj(Shape::sphere);
	ObjId my_box = s.add_obj(Shape::box);

	// add a default box with a color
	color myColor = glm::vec3(0.6, 0.6, 0.6);
	ObjId my_box2 = s.add_obj(Shape::box, myColor);

	// add pyramid with 7 sides 
	obj_params oparams;
	params p = {.sides = 7};
	oparams.glp_params = p;
	ObjId my_pyramid = s.add_obj(Shape::pyramid, myColor, oparams); // myColor is defined above

	// add a composite object
	obj_params opComposite;
	opComposite.comp = {my_sphere.duplicate(), my_box.duplicate()};
	ObjId c1 = s.add_obj(Shape::composite, myColor, opComposite);

	// add an object loaded from .obj file
	obj_params oparamKitten;
	oparamKitten.glp_params = "/Users/crystalren/SimpleGL/test/obj_files/kitten.obj"; // replace this with your filepath
	ObjId my_kitten = s.add_obj("kitten", myColor, oparamKitten);

	// perform translations
	my_pyramid.translate(glm::vec3(-.2,1.2,-0.2));
	my_pyramid.scale(0.2);
	my_pyramid.set_color({1.0, 0.5, 0.31});	

	my_sphere.translate(glm::vec3(2,.8,-0.5));
	my_sphere.scale(0.4);
	my_sphere.set_color({.4, 0.2, 0.31});	

	my_box.translate(glm::vec3(.1,1,-0.8));
	my_box.scale(0.2);
	my_box.set_color({.2, 0.8, 0.9});	
	my_box.rotate(30, glm::vec3(1, 1, 0));

	// make this a floor
	my_box2.translate(glm::vec3( -35, -4, -35));
	my_box2.scale({70, 0.01, 70});

	c1.translate(glm::vec3(1,.1,-0.2));
	c1.scale(0.3);	
	c1.set_color({.1, 0.8, 0.6});	

	my_kitten.scale(0.5);
	my_kitten.set_color({0.8, 0.6, 0.8});

	s.render();

}
