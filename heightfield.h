#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
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

class HeightField {
private:
	int hmHeight;
	int hmWidth;
	int terrainList;
	unsigned int tID[2];

	int vhVertexCount;
	Vert *vhVertices;
	TexCoord *vhTexCoords;
	Normal *vhNormals;

	unsigned int vhVBOVertices;
	unsigned int vhVBOTexCoords;
	unsigned int vhVBONormals;
public:
	bool Create();
	void Render();
	void Init();
	int hLOD;
	GLubyte hHeightField[1024][1024];
	GLubyte texture[1024][1024];
	float waterheight;
};