all: thuquhux

thuquhux: main.cpp 
	g++ -std=c++0x main.cpp Simplexnoise.cpp TerrainGenerator.cpp Parametric_Surface.cpp PhysObject.cpp PointVector.cpp Graph.cpp Geometry.cpp -lglut -lGLU -o ./dist/Debug/GNU-Linux-x86/thuquhux
