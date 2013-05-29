all: thuquhux

thuquhux: main.cpp 
	g++ -std=c++0x main.cpp Simplexnoise.cpp TerrainGenerator.cpp Geometry/Parametric_Surface.cpp PhysObject.cpp PointVector.cpp Geometry/Graph.cpp Geometry/Geometry.cpp -lglut -lGLU -o ./dist/Debug/GNU-Linux-x86/thuquhux
