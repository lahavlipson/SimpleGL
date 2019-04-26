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

Run `make tests` to create the all test executables which will be created in the `build/` directory as well. The test executables are named `test1`, `test2`, `compare1`, `compare2`, and so on. You can also run `make <test_name>` to create one specific test executable.

Run `make clean` to remove all the created files including the `libSimplegl.a` file and the created
build directory and everything therein.

## Sample Usage

After running `make`, run `./build/test1 <obj_file_path>` to render the default scene with an optional .obj file item.

### Scene Class API
TODO: More on how to use the API of Scene class.

### Interactive Key Controls

Space bar: default to cycle through different shape categories, e.g. box, pyramid, obj1, obj2, composite

Down arrow key: move to specific instances of the current shape category

Left arrow key: previous instance in the current shape category

Right arrow key: next instance in the current shape category

Up arrow key: move to top level, cycling through shape categories again

WASD: move the camera up, left, down, right

Cursor: change the viewing direction of the camera

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
- add configuration and key controls callback
