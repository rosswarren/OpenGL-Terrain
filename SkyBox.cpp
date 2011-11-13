#include "SkyBox.h"

/**
* Constructor for the skybox class
**/
SkyBox::SkyBox(void) {

}

/**
* Destructor
*/
SkyBox::~SkyBox(void) {

}


/**
* Initialise by loading textures etc.
*/
void SkyBox::Init(void) {
	RawLoader rawLoader;

	skyTexture = rawLoader.LoadTextureRAW("skyboxtexture.raw", 0, 4096, 3072);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);

	glPushMatrix();

	GLfloat skycolour[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat emissiveMaterial[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat nonEmissiveMaterial[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, skycolour); // material colour

	// Turn on Emissive lighting. We don't want shadows or dark patches on the skybox
	glMaterialfv(GL_FRONT, GL_EMISSION, emissiveMaterial);
	glBindTexture( GL_TEXTURE_2D, skyTexture);

	glScalef(512.0f, 512.0f, 512.0f);
	glTranslatef(1.0f, 0.6f, 1.0f);

	GLfloat half = 0.5f;

	//walls
	glPushMatrix();
	glBegin (GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.001f, 0.665f); glVertex3f(-1.0, -half, 1.0);
	glTexCoord2f(0.001f, 0.334f); glVertex3f(-1.0, half, 1.0);
	glTexCoord2f(0.249f, 0.334f); glVertex3f(1.0, half, 1.0);
	glTexCoord2f(0.249f, 0.665f); glVertex3f(1.0, -half, 1.0);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glBegin (GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.251f, 0.665f); glVertex3f(-1.0, -half, 1.0);
	glTexCoord2f(0.251f, 0.334f); glVertex3f(-1.0, half, 1.0);
	glTexCoord2f(0.499f, 0.334f); glVertex3f(1.0, half, 1.0);
	glTexCoord2f(0.499f, 0.665f); glVertex3f(1.0, -half, 1.0);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glBegin (GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.501f, 0.665f); glVertex3f(-1.0, -half, 1.0);
	glTexCoord2f(0.501f, 0.334f); glVertex3f(-1.0, half, 1.0);
	glTexCoord2f(0.749f, 0.334f); glVertex3f(1.0, half, 1.0);
	glTexCoord2f(0.749f, 0.665f); glVertex3f(1.0, -half, 1.0);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glBegin (GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.751f, 0.665f); glVertex3f(-1.0, -half, 1.0);
	glTexCoord2f(0.751f, 0.334f); glVertex3f(-1.0, half, 1.0);
	glTexCoord2f(0.999f, 0.334f); glVertex3f(1.0, half, 1.0);
	glTexCoord2f(0.999f, 0.665f); glVertex3f(1.0, -half, 1.0);
	glEnd();
	glPopMatrix();

	// Top
	glRotatef(180.0f, 0, 1, 0);
	glBegin (GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.251f, 0.001f); glVertex3f(-1.0f, half, -1.0f);
	glTexCoord2f(0.499f, 0.001f); glVertex3f(1.0f, half, -1.0f);
	glTexCoord2f(0.499f, 0.332f); glVertex3f(1.0f, half, 1.0f);
	glTexCoord2f(0.251f, 0.332f); glVertex3f(-1.0f, half, 1.0f);
	glEnd();


	// Bottom
	//glBegin (GL_QUADS);
	//	glNormal3f(0, 1, 0);
	//	glTexCoord2f(0.25f, 0.6666f); glVertex3f(-1.0f, -0.5f, -1.0f);
	//	glTexCoord2f(0.5f, 0.6666f); glVertex3f(-1.0f, -0.5f,  1.0f);
	//	glTexCoord2f(0.5f, 1.0f); glVertex3f(1.0f, -0.5f,  1.0f);
	//	glTexCoord2f(0.25f, 1.0f); glVertex3f(1.0f, -0.5f, -1.0f);
	//glEnd();

	// Turn off emissive lighting
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nonEmissiveMaterial);

	glPopMatrix();

	glEndList();

}

/**
* Display the skybox
*/
void SkyBox::Display(void) {
	glCallList(displayList);
}