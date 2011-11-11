#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <assert.h>


#ifndef M_PI
#define M_PI 3.14159265f
#endif

#include "heightfield.h"
#include "SkyBox.h"
#include "Lava.h"

#pragma comment(lib,"glew32.lib")

float xpos = 512.0f, ypos = 351.594f, zpos = 512.033f, xrot = 758.0f, yrot = 238.0f, angle = 0.0f;
float lastx, lasty;
float bounce;
float cScale = 1.0;

SkyBox skyBox;
Lava lava;

HeightField hField;

void camera (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); 
	glTranslated(-xpos, -ypos, -zpos);
}

void fog(void) {
	GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 200.0f);
    glFogf(GL_FOG_END, 650.0f);
}

void display (void) {
	glClearColor(0.5, 0.5, 0.5, 1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	camera();

	skyBox.Display();
	lava.Display();

    fog();

	glPushMatrix();
	hField.Render();
	glPopMatrix();

	glutSwapBuffers();
}

void initExtensions(void){
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
}

void Init (void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glDepthFunc(GL_LEQUAL);

	initExtensions();
	hField.hLOD = 8;

	hField.Create();

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

	skyBox.Init();
	lava.Init();
}

void mouseMovement(int x, int y) {
	int diffx=x-lastx; 
	int diffy=y-lasty; 
	lastx=x; 
	lasty=y; 
	xrot += (float) diffy; 
	yrot += (float) diffx;
}

void keyboard (unsigned char key, int x, int y) {
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
		hField.waterheight += 10.0f;
		break;
	case 'f':
		hField.waterheight -= 10.0f;
		break;
	}
}

void reshape (int w, int h) {
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
    glutCreateWindow("A basic OpenGL Window");
	Init();
    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
    glutMainLoop ();
    return 0;
}