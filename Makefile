###Thuquhux makefile###

#Project name
PROJ = thuquhux

#Compiler
CC = clang++

#Flags
ERRFLAGS = -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -fstrict-overflow -Wstrict-overflow=3
CFLAGS = -c -std=c++0x -g $(ERRFLAGS)

#Linked libraries
LIBS = -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm

#Executable output file
EXECUTABLE = ./$(PROJ).elf

#Scource code
SRC = main \
Graphics/Shaders

#Classes
CLS = \
Geometry/Triangle \
Geometry/Triangle_Mesh \
Graphics/DrawHandler \
NPC/NPC \
Physics/PhysObject \
Physics/Material \
Physics/PhysHandler \
Terrain/TerrainGenerator \
Terrain/Simplexnoise \
Terrain/ScatterTree \

#Classes with template methods
CLT = \
Geometry/Parametric_Surface

#Template Classes
TCL = \
Geometry/PointVector

all: $(EXECUTABLE)

$(EXECUTABLE): $(addsuffix .h.gch,$(TCL)) $(addsuffix .o,$(CLS) $(SRC) $(CLT))
	@echo linking with $(LIBS)
	@$(CC) $(addsuffix .o,$(CLS) $(SRC) $(CLT)) $(LIBS) -o $(EXECUTABLE)
	
define PROGRAM_SRC

$(1).o: $(1).cpp
	@echo compiling $(1)
	@$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach standalone,$(SRC),$(eval $(call PROGRAM_SRC,$(standalone))))

define PROGRAM_CLS

$(1).o: $(1).cpp $(1).h
	@echo compiling class $(1)
	@$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach class,$(CLS),$(eval $(call PROGRAM_CLS,$(class))))

define PROGRAM_CLT

$(1).o: $(1).cpp $(1).hpp $(1).h
	@echo compiling class $(1)
	@$(CC) $(CFLAGS) $(1).cpp -o $(1).o

endef

$(foreach class,$(CLT),$(eval $(call PROGRAM_CLT,$(class))))

define PROGRAM_TCL

$(1).h.gch: $(1).hpp $(1).h
	@echo precompling header $(1)
	@$(CC) $(CFLAGS) $(1).h

endef

$(foreach class,$(TCL),$(eval $(call PROGRAM_TCL,$(class))))
	
clean:
	@echo cleaning up
	@- rm $(addsuffix .o,$(SRC) $(CLS) $(CLT)) $(addsuffix .h.gch,$(TCL)) 2> /dev/null
