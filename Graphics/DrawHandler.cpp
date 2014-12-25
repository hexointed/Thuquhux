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
#include "../Geometry/Surface.h"

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

void DrawHandler::draw_vertex(Geometry::Vector<> v){
	glVertex3d(v[0],v[1],v[2]);
}

void DrawHandler::draw(Geometry::Surface& p){
	glPushMatrix();
	glTranslated(p.position[0], p.position[1], p.position[2]);
	glBegin(GL_TRIANGLES);
	for(Geometry::Triangle_Mesh::Element t : p.mesh){
		draw_vertex(t[0].position);
		draw_vertex(t[1].position);
		draw_vertex(t[2].position);
	}
	glEnd();
	glPopMatrix();
}

void DrawHandler::draw(Terrain::ScatterTree& t){
	glScalef(0.3, 0.05, 0.3);
	glTranslatef(0, 0, -3.0);

	glBegin(GL_POINTS);
		t.foreach([&](Geometry::Vector<>& pos, double&){draw_vertex(pos);});
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
