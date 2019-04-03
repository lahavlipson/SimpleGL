# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glfw.Debug:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a:
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a


PostBuild.boing.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/boing.app/Contents/MacOS/boing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/boing.app/Contents/MacOS/boing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/boing.app/Contents/MacOS/boing


PostBuild.gears.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/gears.app/Contents/MacOS/gears
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/gears.app/Contents/MacOS/gears:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/gears.app/Contents/MacOS/gears


PostBuild.heightmap.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/heightmap.app/Contents/MacOS/heightmap
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/heightmap.app/Contents/MacOS/heightmap:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/heightmap.app/Contents/MacOS/heightmap


PostBuild.particles.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/particles.app/Contents/MacOS/particles
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/particles.app/Contents/MacOS/particles:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/particles.app/Contents/MacOS/particles


PostBuild.simple.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/simple.app/Contents/MacOS/simple
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/simple.app/Contents/MacOS/simple:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/simple.app/Contents/MacOS/simple


PostBuild.splitview.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/splitview.app/Contents/MacOS/splitview
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/splitview.app/Contents/MacOS/splitview:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/splitview.app/Contents/MacOS/splitview


PostBuild.wave.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/wave.app/Contents/MacOS/wave
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/wave.app/Contents/MacOS/wave:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Debug/wave.app/Contents/MacOS/wave


PostBuild.clipboard.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/clipboard
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/clipboard:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/clipboard


PostBuild.cursor.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/cursor
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/cursor:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/cursor


PostBuild.empty.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/empty.app/Contents/MacOS/empty
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/empty.app/Contents/MacOS/empty:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/empty.app/Contents/MacOS/empty


PostBuild.events.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/events
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/events:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/events


PostBuild.gamma.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/gamma
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/gamma:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/gamma


PostBuild.glfwinfo.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/glfwinfo
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/glfwinfo:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/glfwinfo


PostBuild.icon.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/icon.app/Contents/MacOS/icon
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/icon.app/Contents/MacOS/icon:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/icon.app/Contents/MacOS/icon


PostBuild.iconify.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/iconify
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/iconify:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/iconify


PostBuild.joysticks.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/joysticks
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/joysticks:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/joysticks


PostBuild.monitors.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/monitors
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/monitors:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/monitors


PostBuild.msaa.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/msaa
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/msaa:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/msaa


PostBuild.reopen.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/reopen
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/reopen:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/reopen


PostBuild.sharing.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/sharing.app/Contents/MacOS/sharing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/sharing.app/Contents/MacOS/sharing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/sharing.app/Contents/MacOS/sharing


PostBuild.tearing.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/tearing.app/Contents/MacOS/tearing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/tearing.app/Contents/MacOS/tearing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/tearing.app/Contents/MacOS/tearing


PostBuild.threads.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/threads.app/Contents/MacOS/threads
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/threads.app/Contents/MacOS/threads:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/threads.app/Contents/MacOS/threads


PostBuild.timeout.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/timeout.app/Contents/MacOS/timeout
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/timeout.app/Contents/MacOS/timeout:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/timeout.app/Contents/MacOS/timeout


PostBuild.title.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/title.app/Contents/MacOS/title
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/title.app/Contents/MacOS/title:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/title.app/Contents/MacOS/title


PostBuild.windows.Debug:
PostBuild.glfw.Debug: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/windows.app/Contents/MacOS/windows
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/windows.app/Contents/MacOS/windows:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Debug/windows.app/Contents/MacOS/windows


PostBuild.glfw.Release:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a:
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a


PostBuild.boing.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/boing.app/Contents/MacOS/boing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/boing.app/Contents/MacOS/boing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/boing.app/Contents/MacOS/boing


PostBuild.gears.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/gears.app/Contents/MacOS/gears
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/gears.app/Contents/MacOS/gears:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/gears.app/Contents/MacOS/gears


PostBuild.heightmap.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/heightmap.app/Contents/MacOS/heightmap
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/heightmap.app/Contents/MacOS/heightmap:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/heightmap.app/Contents/MacOS/heightmap


PostBuild.particles.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/particles.app/Contents/MacOS/particles
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/particles.app/Contents/MacOS/particles:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/particles.app/Contents/MacOS/particles


PostBuild.simple.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/simple.app/Contents/MacOS/simple
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/simple.app/Contents/MacOS/simple:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/simple.app/Contents/MacOS/simple


PostBuild.splitview.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/splitview.app/Contents/MacOS/splitview
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/splitview.app/Contents/MacOS/splitview:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/splitview.app/Contents/MacOS/splitview


PostBuild.wave.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/wave.app/Contents/MacOS/wave
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/wave.app/Contents/MacOS/wave:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/Release/wave.app/Contents/MacOS/wave


PostBuild.clipboard.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/clipboard
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/clipboard:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/clipboard


PostBuild.cursor.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/cursor
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/cursor:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/cursor


PostBuild.empty.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/empty.app/Contents/MacOS/empty
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/empty.app/Contents/MacOS/empty:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/empty.app/Contents/MacOS/empty


PostBuild.events.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/events
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/events:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/events


PostBuild.gamma.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/gamma
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/gamma:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/gamma


PostBuild.glfwinfo.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/glfwinfo
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/glfwinfo:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/glfwinfo


PostBuild.icon.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/icon.app/Contents/MacOS/icon
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/icon.app/Contents/MacOS/icon:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/icon.app/Contents/MacOS/icon


PostBuild.iconify.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/iconify
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/iconify:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/iconify


PostBuild.joysticks.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/joysticks
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/joysticks:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/joysticks


PostBuild.monitors.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/monitors
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/monitors:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/monitors


PostBuild.msaa.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/msaa
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/msaa:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/msaa


PostBuild.reopen.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/reopen
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/reopen:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/reopen


PostBuild.sharing.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/sharing.app/Contents/MacOS/sharing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/sharing.app/Contents/MacOS/sharing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/sharing.app/Contents/MacOS/sharing


PostBuild.tearing.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/tearing.app/Contents/MacOS/tearing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/tearing.app/Contents/MacOS/tearing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/tearing.app/Contents/MacOS/tearing


PostBuild.threads.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/threads.app/Contents/MacOS/threads
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/threads.app/Contents/MacOS/threads:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/threads.app/Contents/MacOS/threads


PostBuild.timeout.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/timeout.app/Contents/MacOS/timeout
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/timeout.app/Contents/MacOS/timeout:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/timeout.app/Contents/MacOS/timeout


PostBuild.title.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/title.app/Contents/MacOS/title
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/title.app/Contents/MacOS/title:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/title.app/Contents/MacOS/title


PostBuild.windows.Release:
PostBuild.glfw.Release: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/windows.app/Contents/MacOS/windows
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/windows.app/Contents/MacOS/windows:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/Release/windows.app/Contents/MacOS/windows


PostBuild.glfw.MinSizeRel:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a


PostBuild.boing.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/boing.app/Contents/MacOS/boing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/boing.app/Contents/MacOS/boing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/boing.app/Contents/MacOS/boing


PostBuild.gears.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/gears.app/Contents/MacOS/gears
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/gears.app/Contents/MacOS/gears:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/gears.app/Contents/MacOS/gears


PostBuild.heightmap.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/heightmap.app/Contents/MacOS/heightmap
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/heightmap.app/Contents/MacOS/heightmap:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/heightmap.app/Contents/MacOS/heightmap


PostBuild.particles.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/particles.app/Contents/MacOS/particles
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/particles.app/Contents/MacOS/particles:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/particles.app/Contents/MacOS/particles


PostBuild.simple.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/simple.app/Contents/MacOS/simple
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/simple.app/Contents/MacOS/simple:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/simple.app/Contents/MacOS/simple


PostBuild.splitview.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/splitview.app/Contents/MacOS/splitview
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/splitview.app/Contents/MacOS/splitview:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/splitview.app/Contents/MacOS/splitview


PostBuild.wave.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/wave.app/Contents/MacOS/wave
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/wave.app/Contents/MacOS/wave:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/MinSizeRel/wave.app/Contents/MacOS/wave


PostBuild.clipboard.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/clipboard
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/clipboard:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/clipboard


PostBuild.cursor.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/cursor
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/cursor:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/cursor


PostBuild.empty.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/empty.app/Contents/MacOS/empty
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/empty.app/Contents/MacOS/empty:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/empty.app/Contents/MacOS/empty


PostBuild.events.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/events
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/events:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/events


PostBuild.gamma.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/gamma
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/gamma:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/gamma


PostBuild.glfwinfo.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/glfwinfo
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/glfwinfo:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/glfwinfo


PostBuild.icon.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/icon.app/Contents/MacOS/icon
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/icon.app/Contents/MacOS/icon:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/icon.app/Contents/MacOS/icon


PostBuild.iconify.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/iconify
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/iconify:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/iconify


PostBuild.joysticks.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/joysticks
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/joysticks:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/joysticks


PostBuild.monitors.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/monitors
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/monitors:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/monitors


PostBuild.msaa.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/msaa
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/msaa:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/msaa


PostBuild.reopen.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/reopen
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/reopen:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/reopen


PostBuild.sharing.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/sharing.app/Contents/MacOS/sharing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/sharing.app/Contents/MacOS/sharing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/sharing.app/Contents/MacOS/sharing


PostBuild.tearing.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/tearing.app/Contents/MacOS/tearing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/tearing.app/Contents/MacOS/tearing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/tearing.app/Contents/MacOS/tearing


PostBuild.threads.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/threads.app/Contents/MacOS/threads
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/threads.app/Contents/MacOS/threads:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/threads.app/Contents/MacOS/threads


PostBuild.timeout.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/timeout.app/Contents/MacOS/timeout
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/timeout.app/Contents/MacOS/timeout:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/timeout.app/Contents/MacOS/timeout


PostBuild.title.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/title.app/Contents/MacOS/title
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/title.app/Contents/MacOS/title:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/title.app/Contents/MacOS/title


PostBuild.windows.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/windows.app/Contents/MacOS/windows
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/windows.app/Contents/MacOS/windows:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/MinSizeRel/windows.app/Contents/MacOS/windows


PostBuild.glfw.RelWithDebInfo:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a


PostBuild.boing.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/boing.app/Contents/MacOS/boing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/boing.app/Contents/MacOS/boing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/boing.app/Contents/MacOS/boing


PostBuild.gears.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/gears.app/Contents/MacOS/gears
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/gears.app/Contents/MacOS/gears:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/gears.app/Contents/MacOS/gears


PostBuild.heightmap.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/heightmap.app/Contents/MacOS/heightmap
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/heightmap.app/Contents/MacOS/heightmap:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/heightmap.app/Contents/MacOS/heightmap


PostBuild.particles.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/particles.app/Contents/MacOS/particles
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/particles.app/Contents/MacOS/particles:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/particles.app/Contents/MacOS/particles


PostBuild.simple.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/simple.app/Contents/MacOS/simple
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/simple.app/Contents/MacOS/simple:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/simple.app/Contents/MacOS/simple


PostBuild.splitview.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/splitview.app/Contents/MacOS/splitview
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/splitview.app/Contents/MacOS/splitview:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/splitview.app/Contents/MacOS/splitview


PostBuild.wave.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/wave.app/Contents/MacOS/wave
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/wave.app/Contents/MacOS/wave:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/examples/RelWithDebInfo/wave.app/Contents/MacOS/wave


PostBuild.clipboard.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/clipboard
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/clipboard:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/clipboard


PostBuild.cursor.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/cursor
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/cursor:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/cursor


PostBuild.empty.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/empty.app/Contents/MacOS/empty
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/empty.app/Contents/MacOS/empty:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/empty.app/Contents/MacOS/empty


PostBuild.events.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/events
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/events:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/events


PostBuild.gamma.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/gamma
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/gamma:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/gamma


PostBuild.glfwinfo.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/glfwinfo
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/glfwinfo:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/glfwinfo


PostBuild.icon.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/icon.app/Contents/MacOS/icon
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/icon.app/Contents/MacOS/icon:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/icon.app/Contents/MacOS/icon


PostBuild.iconify.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/iconify
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/iconify:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/iconify


PostBuild.joysticks.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/joysticks
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/joysticks:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/joysticks


PostBuild.monitors.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/monitors
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/monitors:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/monitors


PostBuild.msaa.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/msaa
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/msaa:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/msaa


PostBuild.reopen.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/reopen
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/reopen:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/reopen


PostBuild.sharing.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/sharing.app/Contents/MacOS/sharing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/sharing.app/Contents/MacOS/sharing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/sharing.app/Contents/MacOS/sharing


PostBuild.tearing.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/tearing.app/Contents/MacOS/tearing
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/tearing.app/Contents/MacOS/tearing:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/tearing.app/Contents/MacOS/tearing


PostBuild.threads.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/threads.app/Contents/MacOS/threads
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/threads.app/Contents/MacOS/threads:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/threads.app/Contents/MacOS/threads


PostBuild.timeout.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/timeout.app/Contents/MacOS/timeout
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/timeout.app/Contents/MacOS/timeout:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/timeout.app/Contents/MacOS/timeout


PostBuild.title.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/title.app/Contents/MacOS/title
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/title.app/Contents/MacOS/title:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/title.app/Contents/MacOS/title


PostBuild.windows.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/windows.app/Contents/MacOS/windows
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/windows.app/Contents/MacOS/windows:\
	/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a
	/bin/rm -f /Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/tests/RelWithDebInfo/windows.app/Contents/MacOS/windows




# For each target create a dummy ruleso the target does not have to exist
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Debug/libglfw3.a:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/MinSizeRel/libglfw3.a:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/RelWithDebInfo/libglfw3.a:
/Users/lahavlipson/Personal\ Projects/Learn_OpenGL/build/src/Release/libglfw3.a:
