/*
 * File: DrawHandler.h
 * Author: Elias Forsberg
 *
 * Created on: February 28, 2014, 12:53
 */
 
#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H

#include <GLFW/glfw3.h>
#include <map>

#include "../Geometry/Geometry.h"
#include "../Geometry/Surface.h"
#include "../Terrain/ScatterTree.h"

namespace Graphics{

	class DrawHandler{
	public:
		DrawHandler();
		~DrawHandler();
	
	public:
		GLFWwindow* window;
		//std::map<Geometry::Surface*, std::pair<GLuint, GLuint>> buffers;
	
	public:
		void draw(Geometry::Surface& p);
		void draw(Terrain::ScatterTree& t);
		
		void redisplay_window();
	
	private:
		void draw_vertex(Geometry::Vertex v);
	};

}
#endif /* DRAWHANDLER_CPP */
