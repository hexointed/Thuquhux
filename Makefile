all: thuquhux

thuquhux: main.cpp 
	g++ main.cpp Simplexnoise.cpp TerrainGenerator.cpp NURBSSEV.cpp PhysObject.cpp PointVector.cpp -lglut -lGLU -o ./dist/Debug/GNU-Linux-x86/thuquhux
