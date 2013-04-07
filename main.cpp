#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <ctime>

#define PI 3.1415926535897932384626433832
#define TAN22p5 0.414213562373095 

void Initialize();
void KeyboardHandler(unsigned char key, int x, int y);
void Display();
void Animate();
void Reshape(int width, int height);
void DrawCube(float size);
void DrawGround(float height, float width, float length);
void GenGround();

const int ground_size = 200;
const int ground_detail = 1;
float ground[ground_size][ground_size];

float posy = 0.0f;
float posx = 0.0f;
float rot = -1.0f;
float lpos = 0.0f;
float trotx = 0.0;
float troty = 0.0;

unsigned char *img;

GLfloat pos[] = {0,0,0,1};
GLfloat dir[] = {0,-1,0};
GLfloat color[] = {0,1,0,1};

int main(int argc, char **argv)
{
    srand(time(0));
    GenGround();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("Wooo!");
    glutDisplayFunc(Display);
    glutKeyboardFunc(KeyboardHandler);
    //glutReshapeFunc(Reshape);
    glutIdleFunc(Animate);
    
    GLenum res = glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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
    
    //glEnable(GL_COLOR_MATERIAL);
    
    
    
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
      case 's':  // exit
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
      trotx = x;
      troty = y;
      default:
      {} break;
  }
  glutPostRedisplay();
}

void Reshape(int width, int height)
{
  if (height == 0)
    return;

  //glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(90.0, width/height, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
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
        //glColor3f(1,1,0);
        DrawCube(0.5);
    glPopMatrix();
    
    GLfloat color2[] = {1,0,0};
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
        DrawGround(0.05, 0.06*ground_size, 0.06*ground_size);
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

void DrawGround(float height, float width, float length){
    for(int z = 0; z < ground_size - 1; z++){
        glBegin(GL_TRIANGLE_STRIP);
            for(int x = 0; x < ground_size; x++){
                glVertex3f((((float)x)/ground_size)*width -width/2, ground[x][z + 1], ((z+1.0)/ground_size)*(-length) + length/2);
                glVertex3f((((float)x)/ground_size)*width -width/2, ground[x][z], (((float)z)/ground_size)*(-length) + length/2);
            }
        glEnd();
    }
}

void GenGround(){
    float temp[ground_size][ground_size];
    for(int k = 0; k < ground_detail; k++){
        for(int i = 0; i < ground_size; i++){
            for(int n = 0; n < ground_size; n++){
                float avg = 0;
                if(i>0 && n>0){
                    avg = (ground[i][n-1] + ground[i-1][n])/2.0;
                }
                ground[i][n] = (rand()%1000 - 500)*0.0001 + avg;
            }
        }
        
    }
    
}