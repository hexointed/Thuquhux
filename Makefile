###Thuquhux makefile###

#Project name
PROJ = thuquhux

#Compiler
CC = g++-4.8

#Flags
ERRFLAGS = -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -fstrict-overflow -Wstrict-overflow=3
CFLAGS = -c -std=c++11 $(ERRFLAGS)

#Linked libraries
LIBS = -lglut -lGLU -lGLEW

#Executable output file
EXECUTABLE = ./$(PROJ).elf

#Scource code
SRC = main

#Classes
CLS = \
TerrainGenerator \
Simplexnoise \
Physics/PhysObject \
Physics/Material \
Geometry/Graph \
Geometry/Geometry

#Classes with template methods
CLT = \
Geometry/Parametric_Surface

#Template Classes
TCL = \
Geometry/PointVector

all: $(EXECUTABLE)

$(EXECUTABLE): $(addsuffix .o,$(CLS) $(SRC) $(CLT))
	$(CC) $(addsuffix .o,$(CLS) $(SRC) $(CLT)) $(LIBS) -o $(EXECUTABLE)
	
define PROGRAM_SRC

$(1).o: $(1).cpp
	$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach standalone,$(SRC),$(eval $(call PROGRAM_SRC,$(standalone))))

define PROGRAM_CLS

$(1).o: $(1).cpp $(1).h
	$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach class,$(CLS),$(eval $(call PROGRAM_CLS,$(class))))

define PROGRAM_CLT

$(1).o: $(1).cpp $(1).hpp $(1).h
	$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach class,$(CLT),$(eval $(call PROGRAM_CLT,$(class))))

define PROGRAM_TCL

#$(1).o: $(1).hpp $(1).h
#	$(CC) $(CFLAGS) $(1).hpp -o $(1).o

endef

$(foreach class,$(TCL),$(eval $(call PROGRAM_TCL,$(class))))
	
clean:
	rm $(addsuffix .o,$(SRC) $(CLS) $(CLT))
