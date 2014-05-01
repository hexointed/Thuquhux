/*
 * File: DrawHandler.cpp
 * Author: Elias Forsberg
 *
 * Created on: February 28, 2014, 12:53
 */

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include "DrawHandler.h"
#include "Shaders.h"

using Graphics::DrawHandler;

DrawHandler::DrawHandler(){
	if(!glfwInit()){
		std::cerr<<"OpenGL initialization failed\n";
		std::exit(1);
	}
	window = glfwCreateWindow(640, 480, "Thuquhux demo", 0, 0);
	if(! window){
		glfwTerminate();
		std::cerr<<"Window creation failed\n";
		std::exit(1);
	}
	glfwMakeContextCurrent(window);
	
	glewInit();
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	
	InitGLSLShader();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,1,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	
	glDisable(GL_CULL_FACE);
}

DrawHandler::~DrawHandler(){
	glfwDestroyWindow(window);
}

void DrawHandler::draw(Geometry::Parametric_Surface& /*p*/){

}

void DrawHandler::draw(Terrain::ScatterTree& t){
	glScalef(0.3, 0.05, 0.3);
	glTranslatef(0, 0, -3.0);

	auto draw_n = [](Geometry::Vector<>& pos, double&){
		glVertex3d(pos[0], pos[1], pos[2]);
	};

	glBegin(GL_POINTS);
		t.foreach(draw_n);
	glEnd();
}

void DrawHandler::redisplay_window(){
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-2, 0,0,1, 0,1,0);
}
