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

thuquhux: .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o
	$(CC) .main.o .Simplexnoise.o .TerrainGenerator.o .Parametric_Surface.o .PhysObject.o .PointVector.o $(LIBS) -o $(EXECUTABLE)

.main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o .main.o
	
.Simplexnoise.o: Simplexnoise.cpp Simplexnoise.h
	$(CC) $(CFLAGS) Simplexnoise.cpp -o .Simplexnoise.o
	
.TerrainGenerator.o: TerrainGenerator.cpp TerrainGenerator.h
	$(CC) $(CFLAGS) TerrainGenerator.cpp -o .TerrainGenerator.o
	
.Parametric_Surface.o: Parametric_Surface.cpp Parametric_Surface.h
	$(CC) $(CFLAGS) Parametric_Surface.cpp -o .Parametric_Surface.o
	
.PhysObject.o: PhysObject.cpp PhysObject.h
	$(CC) $(CFLAGS) PhysObject.cpp -o .PhysObject.o
	
.PointVector.o: PointVector.cpp PointVector.h
	$(CC) $(CFLAGS) PointVector.cpp -o .PointVector.o
	
clean:
	rm -f *.o