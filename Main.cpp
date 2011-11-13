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

#pragma comment(lib, "glew32.lib")

float xpos = 512.0f, ypos = 512.0f, zpos = 512.0f, xrot = 758.0f, yrot = 238.0f, angle = 0.0f;
float lastx, lasty;

// for fps
int time;
int frame = 0;
int timebase = 0;
int fps = 0; 

bool wireframe = false; // show wireframe?
bool refinerydisplay = false; // display the refinery?

SkyBox skyBox;
Lava lava;
Building building;
Refinery refinery;
Trees trees;
Terrain terrain;

/** Setup the camera viewpoint */
void camera (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;

	if (xrot > 90) xrot = 90;

	if (xrot < -90) xrot = -90;

	ypos = lava.getHeight() + 65.0f; // fix to the height of boating on lava viewpoint

	// rotate to the rotation variables
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	// translate to the position variables
	glTranslated(-xpos, -ypos, -zpos);
}

/** setup the fog */
void fog(void) {
	GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 200.0f);
    glFogf(GL_FOG_END, 850.0f);
}

/** calculate the fps */
void calcFPS() {
	frame++; // increment the frame count since the last check
	time = glutGet(GLUT_ELAPSED_TIME); 

	if (time - timebase > 200) { // check every 1/5th of a second
		fps = (int)(frame * 1000 / (time-timebase)); // set the calculated FPS
	 	timebase = time;
		frame = 0;
	}
}

/** draw a string to the screen */
void drawString(std::string s) {
	void * font = GLUT_BITMAP_9_BY_15;
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

/** draw the controls and informational text */
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
	strings[2] = "Movement: WASD, Decrease tree complexity: Z, Increase tree complexity: X, Recalculate trees: C, Relocate trees: T, Raise lava: E, Lower lava: F";
	strings[3] = "Decrease terrain complexity: N, Increase terrain complexity: M, Toggle wireframe: V";
	
	float complexity = (float)terrain.GetComplexity();
	complexity = complexity / 32.0f * 100.0f;
	complexity = 1 / complexity * 625.0f;

	std::stringstream ss;
	ss << "Tree complexity: " << trees.GetComplexity() << ", Frames per second: " << fps << ", Terrain complexity: " <<  complexity << "%";
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

/** opengl display method, draws everything */
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

	if (refinerydisplay) refinery.Display();

	terrain.Display();
	trees.Display();
	lava.Display();
	//terrain.DrawDots();

	glPopMatrix();

	glDisable(GL_LIGHTING);
	drawText(); // draw the help and informational text
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

/** Initialise OpenGL extensions for vertex buffer objects */
void initExtensions(void){
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
}

/** Initialisation method. Sets up OpenGL and calls initialisations of all the components */
void Init(void) {
	initExtensions();
	GLfloat pos[3] = {1024.0f, 800.0f, 0.0f};
	GLfloat whiskcolor[3] = {0.74f, 0.74f, 0.74f};
	//GLfloat specular[3] = {0.0f, 0.0f, 0.0f};
	GLfloat ambient[3] = {0.1f, 0.1f, 0.1f};
	GLfloat diffuse[3] = {0.8f, 0.8f, 0.8f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);//less or equal
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND); //Enable alpha blending
	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

	glShadeModel(GL_SMOOTH);

	printf("Loading textures, building display lists and vertex buffer objects \n");
	terrain.Init();
	skyBox.Init();
	lava.Init();
	building.Init();
	refinery.Init();
	trees.SetUpHeights(terrain, lava.getHeight());
	trees.Init();
	printf("Welcome to Ross's OpenGL Assigment \n");
}

/** mouse movement to look around */
void mouseMovement(int x, int y) {
	float diffx = x-lastx; 
	float diffy = y-lasty; 
	lastx = (float)x; 
	lasty = (float)y; 
	xrot += diffy; 
	yrot += diffx;
}

/** toggle wireframe mode */
void switchWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
	wireframe = !wireframe;
}

/** keyboard controlled */
void keyboard(unsigned char key, int x, int y) {
	float xrotrad, yrotrad;

	switch(key) {
	// move forwards
	case 'w':
		yrotrad = (yrot / 180.0f * M_PI);
		xrotrad = (xrot / 180.0f * M_PI); 
		xpos += sin(yrotrad);
		zpos -= cos(yrotrad);
		ypos -= sin(xrotrad);
		break;
	// strafe left
	case 'a':
		yrotrad = (yrot / 180.0f * M_PI);
		xpos -= cos(yrotrad);
		zpos -= sin(yrotrad);
		break;
	// move backwards
	case 's':
		yrotrad = (yrot / 180.0f * M_PI);
		xrotrad = (xrot / 180.0f * M_PI); 
		xpos -= sin(yrotrad);
		zpos += cos(yrotrad);
		ypos += sin(xrotrad);
		break;
	// move right
	case 'd':
		yrotrad = (yrot / 180.0f * M_PI);
		xpos += cos(yrotrad);
		zpos += sin(yrotrad);
		break;
	// increase lava height
	case 'e':
		lava.increaseHeight();
		break;
	// decrease lava height
	case 'f':
		lava.decreaseHeight();
		break;
	// decrease tree complexity
	case 'z':
		printf("Decreasing tree complexity \n");
		trees.DecreaseComplexity();
		break;
	// increase tree complexity
	case 'x':
		printf("Increasing tree complexity \n");
		trees.IncreaseComplexity();
		break;
	// regenerate trees
	case 'c':
		printf("Regenerating trees \n");
		trees.Regen();
		break;
	// decrease terrain complexity
	case 'n':
		printf("Decreasing terrain complexity \n");
		terrain.DecreaseComplexity();
		break;
	// increase terrain complexity
	case 'm':
		printf("Increasing terrain complexity \n");
		terrain.IncreaseComplexity();
		break;
	// toggle wireframe mode
	case 'v':
		switchWireframe();
		break;
	// toggle displaying of refinery
	case 'r':
		refinerydisplay = !refinerydisplay;
		break;
	// set up tree heights
	case 't':
		trees.SetUpHeights(terrain, lava.getHeight());
		break;
	}
}

/** reshape called when the window is resized */
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
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(400, 100);
	puts("Show the refinery? This will not run on slower computers. (Y or N).");
	char answer;
	std::cin >> answer;
	refinerydisplay = (answer == 'y') ? true : false;
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