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

Run `make`. This will generate a libSimplegl.a file in the generated build/ directory.

Run `make test` to create the test executable which will be created in the build/ directory as well.

Run `make compare` to create the comparison executable which does not use SimpleGL at all. This  will be created in the build/ directory.

Run `make clean` to remove all the created files including the libSimplegl.a file and the created
object and executable files.

## Sample Usage

After running `make`, run `./build/test <obj_file_path>` to render the default scene.
TODO: More on how to use the API of Scene class.

## Troubleshooting

If you get this error when running `make`: `xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun`

And you're running on a Mac, please install the xcode commandline tools: `xcode-select --install`

## Notes

This README heavily referenced from https://github.com/wodeni/Animate-plus-plus/blob/master/README.md

## TODO

- add composite objects
- add error checking
   - make sure the user doesn't create more than one scene instance
   - make sure the user calls render() exactly one time. Otherwise our program crashes!
- create physics demo of bunny bouncing on springs 
   - add a version of this that doesn't use our library (we can use the first commit as a starting point)
- make the parameter list a dictionary (i.e. std::map<std::string, double>) as opposed to a std::vector<double>
   - maybe we should limit the parameter list to non-linear transformations
- add a default color for objects
- put shader.hpp in 3rd party libs. We didn't create it ourselves, and we don't wanna confuse the TAs
