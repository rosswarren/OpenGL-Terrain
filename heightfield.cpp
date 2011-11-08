#include "stdafx.h"
#include <stdio.h>
#include "heightfield.h"

static float terrainLightPos[4] = {0.0f, 0.1f, 0.1f, 0.0f};
static float terrainDiffuseCol[3] = {1.0f, 1.0f, 1.0f};
static float terrainAmbientCol[3] = {0.04f, 0.04f, 0.04f};
static int terrainSimLight = 1;

static GLuint textureNumber;
static GLuint lavaNumber;

bool HeightField::Create(char *hFileName, char *tFileName, const int hWidth, const int hHeight) {	
	waterheight = 480.0f;
	hmHeight = hHeight;
	hmWidth = hWidth;
	
	FILE *fp;

	fp = fopen(hFileName, "rb");

	fread(hHeightField, 1, hWidth * hHeight, fp);

	fclose(fp);

	FILE *terrain;

	terrain = fopen(hFileName, "rb");
	fread(texture, 1, hWidth * hHeight, terrain);
	fclose(terrain);

	vhVertexCount = (int)(hmHeight * hHeight * 6) / (hLOD * hLOD);
	vhVertices = new Vert[vhVertexCount];
	vhTexCoords = new TexCoord[vhVertexCount];
	vhNormals = new Normal[vhVertexCount];

	int nIndex = 0;
	float flX;
	float flZ;

	for (int hMapX = 0; hMapX < hmWidth; hMapX+=hLOD){
		for (int hMapZ = 0; hMapZ < hmHeight; hMapZ+=hLOD){
			for (int nTri = 0; nTri < 6; nTri++){
				flX = (float)hMapX + ((nTri == 1 || nTri == 2 || nTri == 5) ? hLOD : 0);
				flZ = (float)hMapZ + ((nTri == 1 || nTri == 4 || nTri == 5) ? hLOD : 0);

				vhVertices[nIndex].x = flX;
				vhVertices[nIndex].y = hHeightField[(int)flX][(int)flZ];
				//printf("%f", vhVertices[nIndex].y);
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

	Init();

	textureNumber = LoadTextureRAW("heightField2.raw", 0);

	lavaNumber = LoadTextureRAW("lava.raw", 0);

	return true;
}/*
	hmHeight = hHeight;
	hmWidth = hWidth;
	
	FILE *fp;

	fp = fopen(hFileName, "rb");

	fread(hHeightField, 1, hWidth * hHeight, fp);

	fclose(fp);

	//FILE *terrain;

	//terrain = fopen(tFileName, "rb");

	//fread(texture, 1, hWidth * hHeight, fp);

	return true; 
}*/

// load a 256x256 RGB .RAW file as a texture
GLuint HeightField::LoadTextureRAW( const char * filename, int wrap ) {
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 1024;
    height = 1024;

	data = (BYTE *)malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free(data);

    return texture;
}

void HeightField::Init() {
	glGenBuffersARB(1, &vhVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhVertices, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBOTexCoords);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 2 * sizeof(float), vhTexCoords, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &vhVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhNormals, GL_STATIC_DRAW_ARB);

	delete [] vhVertices;
	vhVertices = NULL;

	delete [] vhTexCoords;
	vhTexCoords = NULL;

	delete [] vhNormals;
	vhNormals = NULL;

	return;

	/*
	glNewList(list, GL_COMPILE);
	//glPushMatrix();

	 DOTS 
	glBegin(GL_POINTS);
		for (int hMapX = 0; hMapX < hmWidth; hMapX++) {
			for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++) {
				glVertex3f((GLfloat)hMapX, hHeightField[hMapX][hMapZ], (GLfloat)hMapZ);	
			}
		}
	glEnd();   

	 Triangle Strips 
	for (int hMapX = 0; hMapX < hmWidth; hMapX++) {
		for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++) {
			GLfloat x = (GLfloat)hMapX;
			GLfloat z = (GLfloat)hMapZ;
			
			glBegin(GL_TRIANGLE_STRIP);
				glVertex3f(x, hHeightField[hMapX][hMapZ], z);
				glVertex3f(x, hHeightField[hMapX][hMapZ + 1], z + 1);
				glVertex3f(x + 1, hHeightField[hMapX + 1][hMapZ], z);
				glVertex3f(x + 1, hHeightField[hMapX + 1][hMapZ + 1], z + 1);
			glEnd();
		}
	}

	//glPopMatrix();
	glEndList();  */
}

void HeightField::Cube() {
	glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
glEnd();
}

void HeightField::Render() {
	GLfloat whiskcolor[4] = {0.74f, 0.74f, 0.74f, 1.0f};
	GLfloat watercolour[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat specular[3] = {1.0f, 1.0f, 1.0f};
	
	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glBindTexture(GL_TEXTURE_2D, lavaNumber); // bind the texture
	glPushMatrix();
	glTranslatef(512.0f, waterheight, 512.0f);
	glScalef(512.0f, 400.0f, 512.0f);
	glNormal3f(0, 1, 0);
	Cube();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);

    glPushMatrix();
	glTranslatef(512.0f, waterheight, 512.0f);
	glScalef(20.0f, 60.0f, 20.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glBindTexture(GL_TEXTURE_2D, textureNumber); // bind the texture

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBONormals);
	//glNormalPointer(GL_FLOAT, 0, (char *) NULL);

	glNormal3f(0, 1, 0);

	glDrawArrays(GL_TRIANGLES, 0, vhVertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}