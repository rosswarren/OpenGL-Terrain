#include "stdafx.h"
#include <stdio.h>
#include "Terrain.h"
#include "RawLoader.h"

static GLuint textureNumber;

Terrain::Terrain() {
	hLOD = 32;
	loaded = false;
}

void Terrain::Init() {
	int height = 1024;
	int width = 1024;

	if (!loaded) {
		FILE *fp;
		fp = fopen("heightmap.raw", "rb");

		if (fp == NULL) {
			throw "heightmap.raw not found";
		}

		fread(hHeightField, 1, height * width, fp);
		fclose(fp);
		loaded = true;

		RawLoader rawLoader;
		textureNumber = rawLoader.LoadTextureRAW("terraintexture.raw", 0, 1024, 1024);
	}

	vhVertexCount = (int)(height * width * 6) / (hLOD * hLOD);
	vhVertices = new Vert[vhVertexCount];
	vhTexCoords = new TexCoord[vhVertexCount];
	vhNormals = new Normal[vhVertexCount];

	int nIndex = 0;
	float flX;
	float flZ;

	for (int hMapX = 0; hMapX < width; hMapX+=hLOD) {
		for (int hMapZ = 0; hMapZ < height; hMapZ+=hLOD) {
			for (int nTri = 0; nTri < 6; nTri++) {
				flX = (float)hMapX + ((nTri == 1 || nTri == 2 || nTri == 5) ? hLOD : 0);
				flZ = (float)hMapZ + ((nTri == 1 || nTri == 4 || nTri == 5) ? hLOD : 0);

				vhVertices[nIndex].x = flX;
				vhVertices[nIndex].y = hHeightField[(int)flX][(int)flZ];
				vhVertices[nIndex].z = flZ;
				vhTexCoords[nIndex].u = flX / 1024;
				vhTexCoords[nIndex].v = flZ / 1024;
				vhNormals[nIndex].x = 0;
				vhNormals[nIndex].y = 0;
				vhNormals[nIndex].z = 0;
				nIndex++;
			}
		}
	}

	glGenBuffersARB(1, &vhVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhVertices, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBOTexCoords);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 2 * sizeof(float), vhTexCoords, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhNormals, GL_STATIC_DRAW_ARB);

	// wipe the arrays since they are graphics memory
	delete [] vhVertices;
	vhVertices = NULL;

	delete [] vhTexCoords;
	vhTexCoords = NULL;

	delete [] vhNormals;
	vhNormals = NULL;
}

GLuint Terrain::GetComplexity() {
	return hLOD;
}

void Terrain::IncreaseComplexity() {
	hLOD /= 2;

	if (hLOD < 2) {
		hLOD = 2;
		return;
	}

	Init();
}

void Terrain::DecreaseComplexity() {
	hLOD *= 2;

	if (hLOD > 32) {
		hLOD = 32;
		return;
	}

	Init();
}

void Terrain::Display() {
	GLfloat terraincolour[4] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat specular[3] = {1.0f, 1.0f, 1.0f};

	glPushMatrix();
	glScalef(1.0f, 1.2f, 1.0f);
	glTranslatef(0.0f, -20.0f, 0.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, terraincolour); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, textureNumber); // bind the texture

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	//glNormalPointer(GL_FLOAT, 0, (char *) NULL);

	glNormal3f(0, 1.0f, 0);

	glDrawArrays(GL_TRIANGLES, 0, vhVertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}

void Terrain::DrawDots() {
	glPushMatrix();
	//glScalef(1.0f, 1.2f, 1.0f);
	//glTranslatef(0.0f, -10.0f, 0.0f);
	/*  DOTS */ 
	glBegin(GL_POINTS);
	glPointSize(4.0);

	glNormal3f(0.0f, 1.0f, 0.0f);

	for (unsigned int hMapX = 0; hMapX < hmWidth; hMapX++) {
		for (unsigned int hMapZ = 0; hMapZ < hmHeight; hMapZ++) {
			glVertex3f((GLfloat)hMapX, hHeightField[hMapX][hMapZ], (GLfloat)hMapZ);	
		}
	}

	glEnd(); 
	glPopMatrix();
}