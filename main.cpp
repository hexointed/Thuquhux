#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include "Simplexnoise.h"
#include "TerrainGenerator.h"

void KeyboardHandler(unsigned char key, int x, int y);
void Display();
void Animate();
void DrawCube(float size);
void DrawGround(float height, float width, float length);

float posy = 0.0f;
float posx = 0.0f;
float rot = -1.0f;
float lpos = 0.0f;

#define g_width 5
#define g_depth 5

TerrainGenerator *a = new TerrainGenerator();
double vertecies[(int)((g_width/0.3)*(g_depth/0.3)*2 - (g_depth/0.3)*2)][3];



int main(int argc, char **argv)
{
    srand(time(0));
    //a->genGround();
    std::cout<<(int)((g_width/0.3)*(g_depth/0.3)*2 - (g_depth/0.3)*2)<<std::endl;
    a->genGround(g_width, g_depth, vertecies);
    
    
    
    std::cout<<vertecies[180][0]<<std::endl;
    std::cout<<vertecies[180][1]<<std::endl;
    std::cout<<vertecies[180][2]<<std::endl;
    std::cout<<vertecies[181][0]<<std::endl;
    std::cout<<vertecies[181][1]<<std::endl;
    std::cout<<vertecies[181][2]<<std::endl;
    std::cout<<vertecies[182][0]<<std::endl;
    std::cout<<vertecies[182][1]<<std::endl;
    std::cout<<vertecies[182][2]<<std::endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("Wooo!");
    glutDisplayFunc(Display);
    glutKeyboardFunc(KeyboardHandler);
    glutIdleFunc(Animate);
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    
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
          posy = posy + 0.31;
      } break;
      case 'w':
      {
          posy = posy - 0.31;
      } break;
      case 'a':
      {
          posx = posx + 0.31;
      } break;
      case 'd':
      {
          posx = posx - 0.31;
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
      default:
      {} break;
  }
  glutPostRedisplay();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    
    glRotatef(.05,0,1,0);
    glPushMatrix();
        glRotatef(rot, 0,0,1);
        glRotatef(posx, 1,0,0);
        glRotatef(posy, 0,1,0);
        DrawCube(0.5);
    glPopMatrix();
    
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
    glPushMatrix();
        glTranslatef(0.0, -0.9, 0);
        //DrawGround(0.05, 0.03*ground_size, 0.03*ground_size);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, -0.9, 0);
        glVertexPointer(3,GL_DOUBLE,0,vertecies);
        glDrawArrays(GL_TRIANGLE_STRIP,0,(int)((g_width/0.3)*(g_depth/0.3)*2 - (g_depth/0.3)*2));
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

void DrawGround(float depth, float width, float length){
    for(int z = 0; z < ground_size - 1; z++){
        glBegin(GL_TRIANGLE_STRIP);
            for(int x = 0; x < ground_size; x++){
                glVertex3f((((float)x)/ground_size)*width -width/2, a->getGround(x,z+1), ((z+1.0)/ground_size)*(-length) + length/2);
                glVertex3f((((float)x)/ground_size)*width -width/2, a->getGround(x,z), (((float)z)/ground_size)*(-length) + length/2);
            }
        glEnd();
    }
}