# SimpleGL

A simpler, beginner-friendly version of OpenGL. See the [wiki](https://github.com/Lahav174/SimpleGL/wiki) for the documentation and a [tutorial.md](tutorial.md).


## Directory Structure

All the library source files are `src/` folder.  
The `include/` folder contains required 3rd party libraries or code.  
And the test and demo files are in `test/` with test source code in 
`test/src` and various other files in `test/obj_files/` or `test/shader_files/`.

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


## Troubleshooting

If you get this error when running `make`: `xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun`

And you're running on a Mac, please install the xcode commandline tools: `xcode-select --install`

## Notes

This README referenced https://github.com/wodeni/Animate-plus-plus/blob/master/README.md

## TODO

- create version of kitten bouncing on springs without using SimpleGL
