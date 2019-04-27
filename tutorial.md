# SimpleGL Tutorial

## Required Environment and Preliminary Steps

- C++17
- clang: macOS version `Apple LLVM version 10.0.1 (clang-1001.0.46.3)`
- ar (command line tool)
- glfw3: Run `brew install glfw3` if using Mac OS.

Download the source code in this repository and then run `make` in the top level. This will generate a libSimplegl.a file in the generated `build/` directory.

(You can run `make clean` if you ever need to remove all the created files.)

## Sample Usage

To use SimpleGL, include "simplegl.hpp" and link with -lSimplegl when compiling. 

All of SimpleGL is inside the sgl namespace.

To start using SimpleGL create a Scene object (you can use the default constructor or construct a scene object with custom parameters):
`Scene s;` or `Scene s(char *vertex_shader_filepath, char *frag_shader_filepath, int width, int height);`

Objects in SimpleGL are called "meshes". These meshes can be one of the default types provided by SimpleGL (sphere, truncated cone, cylinder, cone, pyramid, torus, box) which are identified in the Shape namespace or a custom object which can be initialized from a .obj file.

To add these meshes to your scene, take the scene object and use the `add_mesh()` function which returns a `Mesh_id` object that identifies a particular mesh. This method takes a type, an optional glm::vec3 color vector, and an optional std::unordered_map<std::string, int> parameter map with "accuracy" and/or "size" specified as keys. If any optional field is not specified, default values are used. Some sample use cases are shown here:
```
glm::vec3 color = glm::vec3(1.0,0.5,0.71);
Mesh_id m_id = s.add_mesh(Shape::box, color);
   
std::unordered_map<std::string, int> mymap = {{"accuracy",7}};
Mesh_id m_id = s.add_mesh(Shape::sphere, color, mymap );

Mesh_id obj_m_id = s.add_mesh("kitten", color, "<filepath_to_kitten_obj>");
```

These meshes can then be transformed via various methods like translate(), rotate(), scale() and so on. Some samples are shown below:
```
m_id.translate(glm::vec3(4.2,1.2,-0.2));
m_id.scale(0.5);
```

Then after you are satisfied with the transformations and are ready to render the scene, simply call `s.render();` which will open up a window with the scene rendered. The window will be open until you close it by hitting the esc key. You can use your mouse or the keyboard controls stated in the README to move around the scene and manipulate the objects and view.
