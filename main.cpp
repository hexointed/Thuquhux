#include <GL/glew.h>
#include <GL/freeglut.h>

#include <ctime>
#include <math.h>
#include <iostream>

#include "Simplexnoise.h"
#include "TerrainGenerator.h"
#include "Shaders/Shaders.h"
#include "Geometry/Parametric_Surface.h"
#include "PointVector.h"
#include "Geometry/Geometry.h"

void InitLight();
void InitGlut(int argc, char **argv);
void KeyboardHandler(unsigned char key, int x, int y);
void Display();
void Animate();
void DrawCube(float size);

float posy = 0.0f;
float posx = 0.0f;
float rot = 0.0f;
float lpos = 0.0f;
float height = 0.0f;
float cpos = 0.0f;
float tpos = 0.0f;

#define g_width 10.0
#define g_depth 20.0
#define arot 0.0

TerrainGenerator *a = new TerrainGenerator();

using Geometry::Parametric_Surface;
using Geometry::Triangle;

Parametric_Surface *b = new Parametric_Surface(Geometry::def_param_axis_func);
Parametric_Surface *c = new Parametric_Surface(Geometry::def_param_axis_func);

PointVector<> qq[] = {PointVector<>(0.5,0.2,-3.50), PointVector<>(0.1,-0.3,0), PointVector<>(-0.2,0.1,0)};
PointVector<> pp[] = {PointVector<>(0.0,-0.3,-0.2), PointVector<>(-0.4,0.2,-0.2), PointVector<>(-0.3,-0.4,-0.2)};

Triangle d(qq);
Triangle e(pp);

double (*vertecies)[3] = new double[a->getGroundVertexSize()][3];

int main(int argc, char **argv)
{	
    srand(time(0));
    a->genGround(g_width, g_depth,arot,0, vertecies);
	
	std::cout<< PointVector<>::mul_cross({0.5,0.2,-3.5}, {0,-0.3,-0.2}).get(0)<<std::endl;
	std::cout<< PointVector<>::mul_cross({0.5,0.2,-3.5}, {0,-0.3,-0.2}).get(1)<<std::endl;
	std::cout<< PointVector<>::mul_cross({0.5,0.2,-3.5}, {0,-0.3,-0.2}).get(2)<<std::endl;
    
    InitGlut(argc, argv);
	GLenum res = glewInit();
	
    InitLight();
	InitGLSLShader();
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    gluLookAt(0,0,3, 0,0,1, 0,1,0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50,1,1,-1000);
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(0,0,0,0);
    glPointSize(10);

    glutMainLoop();   
   
  return 0;
}

void Animate(){
    glutPostRedisplay();
}

void KeyboardHandler(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
      case 's':
      {
          posy = posy - 0.001;
      } break;
      case 'w':
      {
          posy = posy + 0.001;
      } break;
      case 'a':
      {
          posx = posx - 0.001;
      } break;
      case 'd':
      {
          posx = posx + 0.001;
      } break;
      case 'q':
      {
          rot = rot - 0.31;
      } break;
      case 'e':
      {
          rot = rot + 0.31;
      } break;
      case 'r':
      {
          lpos += 0.03;
      } break;
      case 't':
      {
          lpos -= 0.03;
      } break;
      case 'z':
      {
          height -= 0.1;
      } break;
      case 'x':
      {
          height += 0.1;
      } break;
	  case 'f':
	  {
		  cpos -= 0.125;
	  } break;
	  case 'g':
	  {
		  cpos += 0.125;
	  } break;
	  case 'c':
	  {
		  c->Unite(*b);
	  } break;
	  case 'k':
	  {
		  tpos += 0.0125;
	  } break;
	  case 'j':
	  {
		  tpos -= 0.0125;
	  } break;
      default:
      {} break;
  }
  glutPostRedisplay();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	
	if(d.collisionWith(e) && ! c->isIntersecting(*b)){
		glClearColor(1,0,0,0);
	}else if(!d.collisionWith(e) && ! c->isIntersecting(*b)){
		glClearColor(0,0,1,0);
	}else if(!d.collisionWith(e)){
		glClearColor(0,1,1,0);
	}else{
		glClearColor(1,0,1,0);
	}
	c->position->setdx(cpos);
	
    GLfloat position[] = {(float)(2.5*cos(lpos)),(float)(2.5*sin(lpos)),3,1};
    GLfloat position2[] = {(float)(-2.5*cos(lpos)),(float)(-2.5*sin(lpos)),0,1};
	
	glProgramEnvParameter4fvARB(GL_VERTEX_PROGRAM_ARB, 0, position);
	glProgramEnvParameter4fvARB(GL_VERTEX_PROGRAM_ARB, 1, position2);
	

    e.vertecies[1].set(0,tpos);
    glPushMatrix();
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glTranslatef(2.5*cos(lpos), 2.5*sin(lpos),-3);
        DrawCube(0.05);
    glPopMatrix();
    glPushMatrix();
        glLightfv(GL_LIGHT1, GL_POSITION, position2);
        glTranslatef(-cos(lpos),-sin(lpos),-3);
        DrawCube(0.05);
    glPopMatrix();
    
    a->genGround(g_width, g_depth,posy,posx, vertecies);
    
    glPushMatrix();
        glTranslated(0.0,height -1, 0);
        glRotatef(rot, 0,1,0);
        glVertexPointer(3,GL_DOUBLE,0,vertecies);
        glDrawArrays(GL_TRIANGLE_STRIP,0,a->getGroundVertexSize());
    glPopMatrix();
	
	glPushMatrix();
		glTranslated(-1.0, 1, 0);
        glRotatef(rot, 0,1,0);
		glScalef(0.125, 0.125, 0.125);
		b->drawMesh();
		c->drawMesh();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		d.draw();
		e.draw();
	glPopMatrix();
    glutSwapBuffers();
    
}

void DrawCube(float size){
    size = size/2;
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(size,size,size);
        
        glVertex3f(size,size,-size);
        glVertex3f(-size,size,-size);
        glVertex3f(-size,size,size);
        glVertex3f(-size,-size,size);
        glVertex3f(size,-size,size);
        glVertex3f(size,-size,-size);
        glVertex3f(size,size,-size);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-size,-size,-size);
        
        glVertex3f(size,size,-size);
        glVertex3f(size,-size,-size);
        glVertex3f(size,-size,size);
        glVertex3f(-size,-size,size);
        glVertex3f(-size,size,size);
        glVertex3f(-size,size,-size);
        glVertex3f(size,size,-size);
    glEnd();
}

void InitLight(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat color[] = {0,1,0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.25f);
    
    glEnable(GL_LIGHT1);
    GLfloat color2[] = {0,0,1};
    glLightfv(GL_LIGHT1, GL_AMBIENT, color2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, color2);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.25f);
}

void InitGlut(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("Wooo!");
    glutDisplayFunc(Display);
    glutKeyboardFunc(KeyboardHandler);
    glutIdleFunc(Animate);
}
