/*
 * File: main.cpp
 * Authors: Charles Gilljam, Elias Forsberg, Joline Granth
 *
 * Created on April 7, 2013
 * Completely rewritten on January 2, 2014
 *
 * This file is mostly a demonstration of some capabilities of the Thuquhux engine.
 */

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Physics/PhysObject.h"
#include "NPC/NPC.h"
#include "Shaders/Shaders.h"

void demo_loop(GLFWwindow* widow);
GLFWwindow* loadglfw();
void initgl();

void (*mouse_fn)(GLFWwindow*,int,int,int);
void (*loop_init)(GLFWwindow*);
void (*loop_op)(double time);

void mouse_fn_phys(GLFWwindow* w, int a, int b, int c);
void mouse_fn_npc(GLFWwindow* w, int a, int b, int c);
void mouse_fn_csg(GLFWwindow* w, int a, int b, int c);

void loop_init_phys(GLFWwindow*);
void loop_init_npc(GLFWwindow*);
void loop_init_csg(GLFWwindow*);

void loop_op_phys(double time);
void loop_op_npc(double time);
void loop_op_csg(double time);

int main (){
	decltype(mouse_fn) fn[3] = {mouse_fn_phys, mouse_fn_npc, mouse_fn_csg};
	decltype(loop_init) in[3] = {loop_init_phys, loop_init_npc, loop_init_csg};
	decltype(loop_op) op[3] = {loop_op_phys, loop_op_npc, loop_op_csg};
	
	int mode = 0;
	std::cout<<"Please enter a number: 0 1 or 2\n";
	std::cin >> mode;
	
	switch(mode){
	case 0 :
		std::cout<<"Physics simulation, written by Charles\n"<<
		"click anywhere to spawn an object and watch it collide with others.\n";
		break;
	case 1 :
		std::cout<<"NPC code display, written by Joline\n"<<
		"Object on screen should follow mouse clicks, although NPC behaviour is"<<
		" somewhat probabilistic.\n";
		break;
	case 2 :
		std::cout<<"CSG union operation display, written by Elias\n"<<
		"tap U to unite the right box with the left, the new object can be rotated "<<
		"with W,A,S,D and SPACEBAR.\n";
		break;
	
	default :
		std::cout<<"Faulty input. Program will now terminate.\n";
		break;
	}
	
	mouse_fn = fn[mode];
	loop_init = in[mode];
	loop_op = op[mode];
	
	auto window = loadglfw();
	glewInit();
	initgl();
	
	demo_loop(window);
	
	glfwDestroyWindow(window);
	glfwTerminate();
}

void fix_gl_stuff(GLFWwindow* window){
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-2, 0,0,1, 0,1,0);
}

double get_time(){
	static double prev_time = glfwGetTime();
	double delta_time = glfwGetTime() - prev_time;
	prev_time = glfwGetTime();
	return delta_time;
}

void demo_loop(GLFWwindow* window){
	loop_init(window);
	while(!glfwWindowShouldClose(window)){
		double delta_time = get_time();
		fix_gl_stuff(window);
		
		loop_op(delta_time);
	};
}

GLFWwindow* loadglfw(){
	if(!glfwInit()){
		std::cerr<<"OpenGL initialization failed\n";
		std::exit(1);
	}
	GLFWwindow* window = glfwCreateWindow(640, 480, "Thuquhux demo", 0, 0);
	if(! window){
		glfwTerminate();
		std::cerr<<"Window creation failed\n";
		std::exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouse_fn);
	return window;
}

void initgl(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	
	InitGLSLShader();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,1,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}

Geometry::Vector<2, double> easy_mouse(GLFWwindow* w){
	double x = 0, y = 0;
	int dx = 0, dy = 0;

	glfwGetCursorPos(w,&x,&y);
	glfwGetWindowSize(w, &dx, &dy);

	x = (x/double(dx) - x/(2.0*dx))*2;
	y = (y/double(dy) - y/(2.0*dy))*2;
	x = -(x - 0.5)*2;
	y = -(y - 0.5)*2;
	
	return Geometry::Vector<2, double>{x,y};
}

void mouse_fn_phys(GLFWwindow* w, int , int b, int ){
	if(b == GLFW_RELEASE)
		return;
	auto pos = easy_mouse(w);
	
	PhysObject::create();
	PhysObject::default_handler.physObjects.back().position() = {pos.getdx(), pos.getdy(), 0};
	PhysObject::default_handler.physObjects.back().velocity() = {0,0,1.3};
}

void loop_init_phys(GLFWwindow*){
	PhysObject::create();
	PhysObject::default_handler.physObjects[0].position() = {-0.2,0.5,3};
}

void loop_op_phys(double time){
	PhysObject::default_handler.handle(time);
	for(auto& s : PhysObject::default_handler.physObjects){
		s.surface().drawMesh();
	}
}

extern std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL;
auto& npc_lt = PLACEHOLDER_LINE_OF_TRAVEL;
NPC test_npc;
Geometry::Parametric_Surface npc_surface({0,0,0});

void mouse_fn_npc(GLFWwindow* w, int, int b, int){
	if(b == GLFW_RELEASE)
		return;
	auto pos = easy_mouse(w);
	PointVector<3> npc_pos{pos.getdx(), pos.getdy(), 5};
	npc_lt.push_back(npc_pos);
}

void loop_init_npc(GLFWwindow*){
	npc_lt.push_back({0,0,5});
}

void loop_op_npc(double time){
	test_npc.updatePosition(time);
	npc_surface.position = test_npc.position;
	npc_surface.drawMesh();
}

std::vector<Geometry::Parametric_Surface> surf_list;
bool rotate = true;

void mouse_fn_csg(GLFWwindow*, int, int, int){}

void csg_key_handler(GLFWwindow*, int a, int, int c, int){
	
	if(a == 87 || a == 83)
		surf_list[0].rotate({1,0,0}, (85-a)*0.07);
	if(a == 65 || a == 68)
		surf_list[0].rotate({0,0,1}, (66.5-a)*0.06);
	
	if(c != GLFW_PRESS)
		return;
	if(a == 85)
		surf_list[0].Unite(surf_list[1]);
	if(a == 32)
		rotate = !rotate;
}

void loop_init_csg(GLFWwindow* w){
	glfwSetKeyCallback(w, csg_key_handler);
	surf_list.emplace_back(Geometry::Vector<3, double>{0,0,4});
	surf_list.emplace_back(Geometry::Vector<3, double>{-1,0,4});
}

void loop_op_csg(double time){
	if(rotate)
		surf_list[0].rotate(PointVector<>{0,1,0}, 0.5*time);
	for(auto& s: surf_list){
		s.drawMesh();
	}
}
