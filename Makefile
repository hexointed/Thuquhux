###Thuquhux makefile###

#Compiler
CC = g++-4.8

#Flags
ERRFLAGS = -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -fstrict-overflow -Wstrict-overflow=3
CFLAGS = -c -std=c++0x $(ERRFLAGS)

#Linked libraries
LIBS = -lglut -lGLU -lGLEW

#Executable output file
EXECUTABLE = ./thuquhux.elf

all: thuquhux

thuquhux: .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Triangle_Mesh.o
	$(CC) .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Triangle_Mesh.o $(LIBS) -o $(EXECUTABLE)

.main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o .main.o
	
.Simplexnoise.o: Simplexnoise.cpp Simplexnoise.h
	$(CC) $(CFLAGS) $< -o $@
	
.TerrainGenerator.o: TerrainGenerator.cpp TerrainGenerator.h
	$(CC) $(CFLAGS) $< -o $@
	
.Parametric_Surface.o: ./Geometry/Parametric_Surface.cpp ./Geometry/Parametric_Surface.h
	$(CC) $(CFLAGS) $< -o $@
	
.PhysObject.o: Physics/PhysObject.cpp Physics/PhysObject.h
	$(CC) $(CFLAGS) $< -o $@
	
.PointVector.o: Geometry/PointVector.cpp Geometry/PointVector.h
	$(CC) $(CFLAGS) $< -o $@
	
.Material.o: Physics/Material.cpp Physics/Material.h
	$(CC) $(CFLAGS) $< -o $@
	
.Geometry.o: ./Geometry/Geometry.cpp ./Geometry/Geometry.h
	$(CC) $(CFLAGS) $< -o $@

.Triangle_Mesh.o: ./Geometry/Triangle_Mesh.cpp ./Geometry/Triangle_Mesh.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f .*.o
