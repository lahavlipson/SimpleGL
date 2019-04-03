# SimpleOpenGL

## To get Running (on Xcode at least):

Linker flags: `-lglfw`

Header Search Paths: `full/path/to/SimpleOpenGL/build/Third_prty_libs/Includes`

Run `brew install glfw3` then set
Library Search Paths: `/usr/local/Cellar/glfw/3.2.1/lib`

Editor->Add Build Setting->Add User-Defined Setting.
Name the user defined setting `CC` and set its value to `/usr/local/opt/llvm/bin/clang`

Go into Build Phases and under Link Binary with Libraries, add the following frameworks:
- Cocoa
- IOKit
- OpenGL
- CoreVideo
