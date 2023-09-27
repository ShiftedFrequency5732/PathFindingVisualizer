# To generate the static library, go to C:\raylib\raylib\src, and run the command: mingw32-make PLATFORM=PLATFORM_DESKTOP.
# From there, you will want to get libraylib.a, put that file along with raylib.h, raymath.h, rlgl.h inside your project.

default:
	g++ ./src/*.cpp -o program.exe -O3 -Wall -Wno-missing-braces -I ./include/ -L ./raylib//lib/ -lraylib -lopengl32 -lgdi32 -lwinmm