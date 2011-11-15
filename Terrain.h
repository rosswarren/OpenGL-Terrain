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
	unsigned int vhVBOVertices;
	unsigned int vhVBOTexCoords;
	unsigned int vhVBONormals;

	int vertexCount;
	bool loaded;

	GLuint complexity;
	GLubyte hHeightField[1024][1024];
	GLubyte texture[1024][1024];

	Vert *vertices;
	TexCoord *texCoords;
	Normal *normals;
public:
	Terrain(void);

	void Display();
	void Init();
	
	void DrawDots(void);
	void IncreaseComplexity(void);
	void DecreaseComplexity(void);
	float GetHeightAt(unsigned int x, unsigned int z);
	GLuint GetComplexity(void);
};