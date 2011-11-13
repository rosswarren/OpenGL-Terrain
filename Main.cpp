#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <assert.h>
#include "Terrain.h"
#include "SkyBox.h"
#include "Lava.h"
#include "Building.h"
#include "Refinery.h"
#include "Trees.h"

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#pragma comment(lib,"glew32.lib")

float xpos = 512.0f, ypos = 351.594f, zpos = 512.033f, xrot = 758.0f, yrot = 238.0f, angle = 0.0f;
float lastx, lasty;
float bounce;
float cScale = 1.0;
int time;
int frame = 0;
int timebase = 0;
int fps = 0;
bool wireframe = false;

SkyBox skyBox;
Lava lava;
Building building;
Refinery refinery;
Trees trees;
Terrain terrain;

void camera (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;

	if (xrot > 90) xrot = 90;

	if (xrot < -90) xrot = -90;

	ypos = lava.height + 65.0f;

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); 
	glTranslated(-xpos, -ypos, -zpos);
}

void fog(void) {
	GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 200.0f);
    glFogf(GL_FOG_END, 850.0f);
}

void calcFPS() {
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		fps = (int)(frame * 1000.0 / (time-timebase));
	 	timebase = time;
		frame = 0;
	}
}

void drawString(std::string s) {
	void * font = GLUT_BITMAP_9_BY_15;
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

void drawText(void) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 400, 0.0, 500);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	std::string strings [5];

	strings[0] = "Ross Warren's OpenGL Assignement";
	strings[1] = "Controls:";
	strings[2] = "Movement: WASD, Decrease tree complexity: Z, Increase tree complexity: X, Recalculate Trees: C, Raise lava: E, Lower lava: F";
	strings[3] = "Increase terrain complexity: M, Decrease terrain complexity: N, Toggle wireframe: V";
	
	std::string s = "Tree complexity: ";

	std::stringstream ss;
	
	ss << s << trees.GetComplexity();

	s = " Frames per second: ";
	
	ss << s << fps;

	s = " Terrain complexity: ";

	float complexity = (float)terrain.GetComplexity();

	complexity = complexity / 32 * 100;

	complexity = 1 / complexity * 625;
	
	ss << s << complexity << "%";

	strings[4] = ss.str();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	int height = 60;

	for (int i = 0; i < 5; i++) {
		glRasterPos2i(10, height -= 10);
		drawString(strings[i]);
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void display (void) {
	glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	GLfloat white[4] =  {1.0f, 1.0f, 1.0f, 1.0f};
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white); // material colour

	calcFPS(); // calculate the frames per second

	glPushMatrix();
	camera(); // change the view to that of the camera

	// display everything
	skyBox.Display();
	building.Display();
	refinery.Display();
	trees.Display();
	terrain.Display();
	lava.Display();
	terrain.DrawDots();

	glPopMatrix();

	drawText(); // draw the help and informational text

	glutSwapBuffers();
}

void initExtensions(void){
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
}

void Init(void) {
	glDepthFunc(GL_LEQUAL);

	initExtensions();
	GLfloat pos[4] = {5.0f, 100.0f, 10.0f, 0.0f};
	GLfloat whiskcolor[3] = {0.74f, 0.74f, 0.74f};
	GLfloat specular[3] = {0.0f, 0.0f, 0.0f};
	GLfloat ambient[3] = {0.1f, 0.1f, 0.1f};
	GLfloat diffuse[3] = {0.8f, 0.8f, 0.8f};

	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND); //Enable alpha blending

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

	glShadeModel(GL_SMOOTH);

	printf("Loading textures, building display lists and vertex buffer objects \n");
	terrain.Init();
	skyBox.Init();
	lava.Init();
	building.Init();
	refinery.Init();
	trees.Init();
	printf("Welcome to Ross's OpenGL Assigment \n");
}

void mouseMovement(int x, int y) {
	float diffx = x-lastx; 
	float diffy = y-lasty; 
	lastx = (float)x; 
	lasty = (float)y; 
	xrot += diffy; 
	yrot += diffx;
}

void switchWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
	wireframe = !wireframe;
}

void keyboard(unsigned char key, int x, int y) {
	float xrotrad, yrotrad;

	switch(key) {
	case 'w':
		yrotrad = (yrot / 180.0f * M_PI);
		xrotrad = (xrot / 180.0f * M_PI); 
		xpos += float(sin(yrotrad)) * cScale;
		zpos -= float(cos(yrotrad)) * cScale;
		ypos -= float(sin(xrotrad)) ;
		bounce += 0.04f;
		break;
	case 'a':
		yrotrad = (yrot / 180.0f * M_PI);
		xpos -= float(cos(yrotrad)) * cScale;
		zpos -= float(sin(yrotrad)) * cScale;
		break;
	case 's':
		yrotrad = (yrot / 180.0f * M_PI);
		xrotrad = (xrot / 180.0f * M_PI); 
		xpos -= float(sin(yrotrad)) * cScale;
		zpos += float(cos(yrotrad)) * cScale;
		ypos += float(sin(xrotrad));
		bounce += 0.04f;
		break;
	case 'd':
		yrotrad = (yrot / 180.0f * M_PI);
		xpos += float(cos(yrotrad)) * cScale;
		zpos += float(sin(yrotrad)) * cScale;
		break;
	case 'e':
		lava.height += 1.0f;
		break;
	case 'f':
		lava.height -= 1.0f;
		break;
	case 'z':
		printf("Decreasing tree complexity \n");
		trees.DecreaseComplexity();
		break;
	case 'x':
		printf("Increasing tree complexity \n");
		trees.IncreaseComplexity();
		break;
	case 'c':
		printf("Regenerating trees \n");
		trees.Regen();
		break;
	case 'n':
		terrain.DecreaseComplexity();
		break;
	case 'm':
		terrain.IncreaseComplexity();
		break;
	case 'v':
		switchWireframe();
		break;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 3000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Ross Warren's OpenGL Assignment");
	Init();
    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
    glutMainLoop();

    return 0;
}