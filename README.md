# SimpleOpenGL

## Directory Structure

All the library source files are src/ folder. The include/ folder contains required 3rd party libraries.
And the test files and demo files are in test/src/.

## To compile the library:

Make sure glfw3 is installed first. Run `brew install glfw3` if using Mac OS.

Run `make`. This will generate a libSimplegl.a file in the generated build/ directory.

Run `make test` to create the test executable which will be created in the build/ directory as well.

Run `make clean` to remove all the created files including the libSimplegl.a file and the created
object and executable files.
