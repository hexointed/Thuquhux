#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include "Simplexnoise.h"
#include "TerrainGenerator.h"
#include "Geometry/Parametric_Surface.h"
#include "Geometry/PointVector.h"
#include "Geometry/Triangle.h"
#include "NPC/NPC.h"
#include "Geometry/Triangle_Mesh.h"
#include "Physics/PhysObject.h"
#include "Physics/PhysHandler.h"

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
int showtri = 0;

#define g_width 8.0
#define g_depth 12.0
#define arot 0.0

TerrainGenerator *a = new TerrainGenerator();

using Geometry::Parametric_Surface;
using Geometry::Triangle;

Parametric_Surface *b = new Parametric_Surface(Geometry::def_param_axis_func, {0,0,0});
Parametric_Surface *c = new Parametric_Surface(Geometry::def_param_axis_func, {0,0,0});
Parametric_Surface elias{{0,0,0}};

PointVector<> qq[] = {PointVector<>({0.5,0.2,-3.50}), PointVector<>({0.1,-0.3,0}), PointVector<>({-0.2,0.1,0})};
PointVector<> pp[] = {PointVector<>({0.0,-0.3,-0.2}), PointVector<>({-0.4,0.2,-0.2}), PointVector<>({-0.3,-0.4,-0.2})};

PointVector<> tp{0,0,0};

Triangle d{qq};
Triangle e{pp};



NPC joline;
NPC nyNPC;

double (*vertecies)[3] = new double[a->getGroundVertexSize()][3];


int main(int argc, char **argv)
{

	
	srand(time(0));
	a->genGround(g_width, g_depth,arot,0, vertecies);

	InitGlut(argc, argv);
	InitLight();

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
		case 'b':
		{
			tpos += 0.0125;
		} break;
		case 'v':
		{
			tpos -= 0.0125;
		} break;
		case 'j':
		{
			tp.setdx(tp.getdx() - 0.125123);
		} break;
		case 'l':
		{
			tp.setdx(tp.getdx() + 0.125123);
		} break;
		case 'k':
		{
			tp.setdy(tp.getdy() - 0.125123);
		} break;
		case 'i':
		{
			tp.setdy(tp.getdy() + 0.125127);
		} break;
		case 'p':
		{
			elias = Parametric_Surface::unite(*b, *c);
		}
		default:
		{} break;
	}
	glutPostRedisplay();
}

void Display()
{	
	
	PhysObject::default_handler.handle(0.05);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	c->position.setdx(cpos);
	elias.position = {3,0,0};
	c->rotate({0,1,0}, 0.1);
	e.move({tpos,0,0});
	Triangle tritest{{-0.5,-0.5,0},{0.5,-0.5,0},{0.5,-0.5,0.5}};

	double color[3] {c->pointIsWithin(tp)?1.0:0.0, c->isIntersecting(*b)?1.0:0.0, d.intersectionWith(e).first?1.0:0.0};
	glClearColor(color[0], color[1], color[2], 0);

	GLfloat position[] = {(float)cos(lpos),(float)sin(lpos),0,1};
	GLfloat position2[] = {(float)-cos(lpos),(float)-sin(lpos),0,1};
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
		elias.drawMesh();
		glBegin(GL_POINTS);
			glVertex3dv((double*)&tp);
			glVertex3dv((double*)&joline.position);
			glVertex3dv((double*)&nyNPC.position);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		d.draw();
		e.draw();
		PhysObject::default_handler.NPCs[0].second.surface().drawMesh();

		tritest.draw();
		tritest.split({0,0,0},{1,0,0})[1].move({0,1,0}).draw();
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
