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

void DrawHandler::draw(Geometry::Surface& p){
	glPushMatrix();
	glTranslated(p.position[0], p.position[1], p.position[2]);
	glBegin(GL_TRIANGLES);
	for(Geometry::Triangle t : p.mesh){
		glVertex3d(t[0][0], t[0][1], t[0][2]);
		glVertex3d(t[1][0], t[1][1], t[1][2]);
		glVertex3d(t[2][0], t[2][1], t[2][2]);
	}
	glEnd();
	glPopMatrix();
}

namespace {
	void draw_node(Terrain::ScatterTree::Node& n){
		try{
			auto& pos = n.left().position;
			glVertex3d(n.position[0], n.position[1], n.position[2]);
			glVertex3d(pos[0], pos[1], pos[2]);
			draw_node(n.left());
		}catch(...){}
		try{
			auto& pos = n.right().position;
			glVertex3d(n.position[0], n.position[1], n.position[2]);
			glVertex3d(pos[0], pos[1], pos[2]);
			draw_node(n.right());
		}catch(...){}
	}
}

void DrawHandler::draw(Terrain::ScatterTree& t){
	glScalef(0.4, 0.1, 0.4);
	glTranslatef(0, -1.0, -3.0);
	
	glPushMatrix();
	glRotatef(glfwGetTime()*10.0, 0, 1, 0);
	
	glBegin(GL_LINES);
		draw_node(t.top());
	glEnd();
	glPopMatrix();
}

void DrawHandler::redisplay_window(){
	glfwSwapBuffers(window);
	glfwPollEvents();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-2, 0,0,1, 0,1,0);
}
