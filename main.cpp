/*
 * File: main.cpp
 * Authors: Charles Gilljam, Elias Forsberg, Joline Granth
 *
 * Created on April 7, 2013
 * Completely rewritten on January 2, 2014
 *
 * This file is mostly a demonstration of some capabilities of the Thuquhux engine.
 */

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Physics/PhysObject.h"
#include "Graphics/Graphics.h"

void demo_loop(GLFWwindow* widow);
GLFWwindow* loadglfw();
void initgl();

int main (){
	auto window = loadglfw();
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
	PhysObject::create();
	PhysObject::create();
	PhysObject::default_handler.physObjects[0].velocity() = {0,0,0.3};
	while(!glfwWindowShouldClose(window)){
		double delta_time = get_time();
		fix_gl_stuff(window);
		
		PhysObject::default_handler.handle(delta_time);
		for(auto& s : PhysObject::default_handler.physObjects){
			s.surface().drawMesh();
		}
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
	return window;
}

void initgl(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	
	Graphics::Program shprog{Graphics::Shader(GL_VERTEX_SHADER, "")
	                         Graphics::Shader(GL_FRAGMENT_SHADER, "")};
	shprog.use();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,1,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}
