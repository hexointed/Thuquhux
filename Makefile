all: thuquhux

thuquhux: main.cpp 
	g++ main.cpp Simplexnoise.cpp TerrainGenerator.cpp -lglut -lGLU -lGLEW -o ./dist/Debug/GNU-Linux-x86/thuquhux
