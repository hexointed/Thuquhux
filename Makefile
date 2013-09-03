###Thuquhux makefile###

#Project name
PROJ = thuquhux

#Compiler
CC = g++-4.8

#Flags
ERRFLAGS = -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -fstrict-overflow -Wstrict-overflow=3
CFLAGS = -c -std=c++0x $(ERRFLAGS)

#Linked libraries
LIBS = -lglut -lGLU -lGLEW

#Executable output file
EXECUTABLE = ./$(PROJ).elf

#Scource code
SRC = main.cpp

#Classes
CLS = \
TerrainGenerator \
Simplexnoise \
#PhysObject \
#Material \
#Graph \
#Geometry

#Classes with template methods
CLT = \
Parametric_Surface
#Template Classes.Simplexnoise.o .TerrainGenerator.o
TCL = \
PointVector

all: $(PROJ)

$(PROJ): .main.o .classes .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Graph.o
	$(CC) .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o .Material.o .Geometry.o .Graph.o $(LIBS) -o $(EXECUTABLE)

.main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o .main.o
	
.classes:
	$(foreach class, $(CLS), $(CC) $(CFLAGS) $(class).cpp -o .$(class).o;)
	
.Parametric_Surface.o: ./Geometry/Parametric_Surface.cpp ./Geometry/Parametric_Surface.h
	$(CC) $(CFLAGS) $< -o $@
	
.PhysObject.o: Physics/PhysObject.cpp Physics/PhysObject.h
	$(CC) $(CFLAGS) $< -o $@
	
.PointVector.o: Geometry/PointVector.cpp Geometry/PointVector.h
	$(CC) $(CFLAGS) $< -o $@
	
.Material.o: Physics/Material.cpp Physics/Material.h
	$(CC) $(CFLAGS) $< -o $@
	
.Graph.o: Geometry/Graph.cpp Geometry/Graph.h
	$(CC) $(CFLAGS) $< -o $@
	
.Geometry.o: ./Geometry/Geometry.cpp ./Geometry/Geometry.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f .*.o
