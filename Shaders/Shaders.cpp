/* 
 * File:   Shaders.cpp
 * Author: Elias Forsberg
 *
 * Created on May 15, 2013, 7:28 PM
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>


void InitARBShader(){
	{
		std::ifstream in("Shaders/vertex.arbvs");
		std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		char * prgrm = new char[str.size()];
		strcpy(prgrm, str.c_str());
	
		glEnable(GL_VERTEX_PROGRAM_ARB);
		unsigned int handle[1];
		glGenProgramsARB(1,handle);
		glBindProgramARB(GL_VERTEX_PROGRAM_ARB, *handle);
		glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, str.size(), &prgrm[0]);
	
		int err;
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &err);
		if(err !=-1){
			std::string error = (const char*) glGetString(GL_PROGRAM_ERROR_STRING_ARB);
			std::cout<<"Vertex program failed:\n"<<err<<std::endl<<error<<std::endl;
		}
		delete[] prgrm;
	}
	{
		std::ifstream in("Shaders/fragment.arbfs");
		std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		char * prgrm = new char[str.size()];
		strcpy(prgrm, str.c_str());
	
		glEnable(GL_FRAGMENT_PROGRAM_ARB);
		unsigned int handle[1];
		glGenProgramsARB(1,handle);
		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, *handle);
		glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, str.size(), &prgrm[0]);
	
		int err;
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &err);
		if(err !=-1){
			std::string error = (const char*) glGetString(GL_PROGRAM_ERROR_STRING_ARB);
			std::cout<<"Vertex program failed:\n"<<err<<std::endl<<error<<std::endl;
		}
		delete[] prgrm;
	}
}