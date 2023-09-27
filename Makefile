# To generate the static library, go to C:\raylib\raylib\src, and run the command: mingw32-make PLATFORM=PLATFORM_DESKTOP.
# From there, you will want to get libraylib.a, put that file along with raylib.h, raymath.h, rlgl.h inside your project.

CXX = g++
CXXFLAGS = -O2 -Wall -Wno-missing-braces -lraylib -lopengl32 -lgdi32 -lwinmm
OUT = program.exe

SRC = $(wildcard ./*/src/*.cpp)

default: $(SRC)
	@$(info $(SRC))
	$(CXX) $^ -o $(OUT) -I ./ -L ./raylib/lib/ $(CXXFLAGS)

