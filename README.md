# SimpleGL

A simpler, beginner-friendly version of OpenGL.

## Directory Structure

All the library source files are `src/` folder.  
The `include/` folder contains required 3rd party libraries or code.  
And the test and demo files are in `test/src/`.

## Dependencies

- C++17
- clang: macOS version `Apple LLVM version 10.0.1 (clang-1001.0.46.3)`
- ar (command line tool)
- glfw3

## Getting Started

Make sure glfw3 is installed first. Run `brew install glfw3` if using Mac OS.

Run `make`. This will generate a libSimplegl.a file in the generated `build/` directory.

Run `make tests` to create the test executables in the `build/` directory. You can also run `make <test_name>` to create one specific test executable.

Run `make clean` to remove all the created files including the `libSimplegl.a` file and the created build directory and everything therein.

## Sample Usage

To use SimpleGL, include "simplegl.hpp" and link the -lSimplegl when compiling. 

All of SimpleGL is inside the sgl namespace.

To start using SimpleGL, create a Scene object.

Objects in SimpleGL are called "meshes". These can be one of the default types provided by SimpleGL (sphere, truncated cone, cylinder, cone, pyramid, torus, box) which are identified in the Shape namespace or a custom object which can be initialized from a .obj file.

To add these meshes to your scene, take the scene object and use the `add_mesh()` function.

These meshes can then be transformed via various methods like translate(), rotate(), and scale(). See documentation.md for a more detailed description of the API.

Then, the scene can be rendered via `s.render();`.

For a more detailed tutorial see tutorial.md.


### Interactive Key Controls

Space bar: default to cycle through different shape categories, e.g. box, pyramid, obj1, obj2, composite

Down arrow key: move to specific instances of the current shape category

Left arrow key: previous instance in the current shape category

Right arrow key: next instance in the current shape category

Up arrow key: move to top level, cycling through shape categories again

WASD: move the camera up, left, down, right

Cursor: change the viewing direction of the camera

(TODO) P: print the current configuration. 

H: hide/remove the current instance or all instances in this category.

U: unhide the current instance or all instances in this category.

1: decrease the current instance's X position

2: increase the current instance's X position

3: decrease the current instance's Y position

4: increase the current instance's Y position

5: decrease the current instance's Z position

6: increase the current instance's Z position

7: rotate the current instance around X axis

8: rotate the current instance around Y axis

9: rotate the current instance around Z axis

## Troubleshooting

If you get this error when running `make`: `xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun`

And you're running on a Mac, please install the xcode commandline tools: `xcode-select --install`

## Notes

This README heavily referenced from https://github.com/wodeni/Animate-plus-plus/blob/master/README.md

## TODO

- create version of kitten bouncing on springs without using SimpleGL
- add configuration parsing and storing
