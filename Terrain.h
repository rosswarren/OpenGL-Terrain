#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include "SkyBox.h"
#include "RawLoader.h"
#include "Shapes.h"



class Vert{
	public:  
		float x;
		float y;
		float z;
};

class TexCoord {
	public:
		float u;
		float v;
};

class Normal {
	public:
		float x;
		float y;
		float z;
};

class Terrain {
private:
	unsigned int hmHeight;
	unsigned int hmWidth;
	unsigned int terrainList;
	unsigned int tID[2];

	int vhVertexCount;
	Vert *vhVertices;
	TexCoord *vhTexCoords;
	Normal *vhNormals;

	unsigned int vhVBOVertices;
	unsigned int vhVBOTexCoords;
	unsigned int vhVBONormals;
	bool loaded;
	GLuint hLOD;
public:
	void Display();
	void Init();
	GLubyte hHeightField[1024][1024];
	GLubyte texture[1024][1024];
	Terrain(void);
	void DrawDots(void);
	void IncreaseComplexity(void);
	void DecreaseComplexity(void);
	GLuint GetComplexity(void);
};