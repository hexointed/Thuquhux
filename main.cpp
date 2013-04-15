#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include "Simplexnoise.h"
#include "TerrainGenerator.h"

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

#define g_width 7.0
#define g_depth 14.0
#define arot 0.0

TerrainGenerator *a = new TerrainGenerator();
double (*vertecies)[3] = new double[a->getGroundVertexSize()][3];

int main(int argc, char **argv)
{
    srand(time(0));
    a->genGround(g_width, g_depth,arot,0, vertecies);
    
    InitGlut(argc, argv);
    InitLight();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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

void KeyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
      case 's':
      {
          posy = posy + 0.001;
      } break;
      case 'w':
      {
          posy = posy - 0.001;
      } break;
      case 'a':
      {
          posx = posx + 0.001;
      } break;
      case 'd':
      {
          posx = posx - 0.001;
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
      }
      default:
      {} break;
  }
  glutPostRedisplay();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    GLfloat position[] = {cos(lpos),sin(lpos),0,1};
    GLfloat position2[] = {-cos(lpos),-sin(lpos),0,1};
    glPushMatrix();
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glTranslatef(cos(lpos),sin(lpos),0);
        DrawCube(0.05);
    glPopMatrix();
    glPushMatrix();
        glLightfv(GL_LIGHT1, GL_POSITION, position2);
        glTranslatef(-cos(lpos),-sin(lpos),0);
        DrawCube(0.05);
    glPopMatrix();
    
    a->genGround(g_width, g_depth,posy,posx, vertecies);
    
    glPushMatrix();
        glTranslated(0.0, -1 + height, 0);
        glRotatef(rot, 0,1,0);
        //glTranslatef(posx,0,0);
        //glTranslatef(0,0,posy);
        glVertexPointer(3,GL_DOUBLE,0,vertecies);
        glDrawArrays(GL_TRIANGLE_STRIP,0,a->getGroundVertexSize());
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
    GLfloat color2[] = {1,0,0};
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
