###Thuquhux makefile###

#Compiler
CC = g++

#Flags
ERRFLAGS = -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -fstrict-overflow -Wstrict-overflow=3
CFLAGS = -c -std=c++0x $(ERRFLAGS)

#Linked libraries
LIBS = -lglut -lGLU -lGLEW

#Executable output file
EXECUTABLE = ./dist/Debug/GNU-Linux-x86/thuquhux

all: thuquhux

thuquhux: .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Graph.o .Shaders.o
	$(CC) .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Graph.o .Shaders.o $(LIBS) -o $(EXECUTABLE)

.main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o .main.o
	
.Simplexnoise.o: Simplexnoise.cpp Simplexnoise.h
	$(CC) $(CFLAGS) $< -o $@
	
.TerrainGenerator.o: TerrainGenerator.cpp TerrainGenerator.h
	$(CC) $(CFLAGS) $< -o $@
	
.Parametric_Surface.o: ./Geometry/Parametric_Surface.cpp ./Geometry/Parametric_Surface.h
	$(CC) $(CFLAGS) $< -o $@
	
.PhysObject.o: PhysObject.cpp PhysObject.h
	$(CC) $(CFLAGS) $< -o $@
	
.PointVector.o: PointVector.cpp PointVector.h
	$(CC) $(CFLAGS) $< -o $@
	
.Material.o: Material.cpp Material.h
	$(CC) $(CFLAGS) $< -o $@
	
.Graph.o: Geometry/Graph.cpp Geometry/Graph.h
	$(CC) $(CFLAGS) $< -o $@
	
.Geometry.o: ./Geometry/Geometry.cpp ./Geometry/Geometry.h
	$(CC) $(CFLAGS) $< -o $@

.Shaders.o: ./Shaders/Shaders.cpp ./Shaders/Shaders.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f .*.o
