all: opengl-test

opengl-test: main.cpp 
	g++ main.cpp -lglut -lGLU -lGLEW -o ./dist/Debug/GNU-Linux-x86/opengl-test
