#include <stdio.h>
#include "Terrain.h"
#include "RawLoader.h"

static GLuint textureNumber;

/**
* Terrain code is adapted from http://www.swiftless.com/terraintuts.html
* The heightmap and texture are also modified from there
*
*/
Terrain::Terrain() {
	complexity = 32;
	loaded = false;
}

// initialise terrain from heightmap and load texture
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

	vertexCount = (int)(height * width * 6) / (complexity * complexity);
	vertices = new Vert[vertexCount];
	texCoords = new TexCoord[vertexCount];
	normals = new Normal[vertexCount];

	int nIndex = 0;
	float flX;
	float flZ;

	for (int hMapX = 0; hMapX < width; hMapX += complexity) {
		for (int hMapZ = 0; hMapZ < height; hMapZ += complexity) {
			for (int nTri = 0; nTri < 6; nTri++) {
				flX = (float)hMapX + ((nTri == 1 || nTri == 2 || nTri == 5) ? complexity : 0);
				flZ = (float)hMapZ + ((nTri == 1 || nTri == 4 || nTri == 5) ? complexity : 0);

				vertices[nIndex].x = flX;
				vertices[nIndex].y = hHeightField[(int)flX][(int)flZ];
				vertices[nIndex].z = flZ;
				texCoords[nIndex].u = flX / 1024;
				texCoords[nIndex].v = flZ / 1024;
				normals[nIndex].x = 0;
				normals[nIndex].y = 1;
				normals[nIndex].z = 0;
				nIndex++;
			}
		}
	}

	glGenBuffersARB(1, &vhVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBOTexCoords);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertexCount * 2 * sizeof(float), texCoords, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertexCount * 3 * sizeof(float), normals, GL_STATIC_DRAW_ARB);

	// wipe the arrays since they are graphics memory
	delete [] vertices;
	vertices = NULL;

	delete [] texCoords;
	texCoords = NULL;

	delete [] normals;
	normals = NULL;
}

/** gets a Y coordinate value from the heightmap based on its X and Y */
float Terrain::GetHeightAt(unsigned int x, unsigned int z) {
	float y = hHeightField[x][z];
	y *= 1.2f;
	y -= 30.0f;

	return y;
}

/** returns the terrain complexity */
GLuint Terrain::GetComplexity() {
	return complexity;
}

/** increases the terrain complexity */
void Terrain::IncreaseComplexity() {
	complexity /= 2;

	if (complexity < 2) {
		complexity = 2;
		return;
	}

	Init();
}

/** decreases the terrain complexity */
void Terrain::DecreaseComplexity() {
	complexity *= 2;

	if (complexity > 32) {
		complexity = 32;
		return;
	}

	Init();
}

/** displays the terrain */
void Terrain::Display() {
	GLfloat terraincolour[4] = {0.7f, 0.7f, 0.7f, 1.0f};

	glPushMatrix();
	glScalef(1.0f, 1.2f, 1.0f);
	glTranslatef(0.0f, -20.0f, 0.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, terraincolour); // material colour

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, textureNumber); // bind the texture

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glNormalPointer(GL_FLOAT, 0, (char *) NULL);

	glNormal3f(0, 1.0f, 0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}

void Terrain::DrawDots() {
	glPushMatrix();
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