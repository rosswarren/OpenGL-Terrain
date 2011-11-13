#include "SkyBox.h"

/** Constructor for the skybox class */
SkyBox::SkyBox(void) {

}

/** Destructor */
SkyBox::~SkyBox(void) {

}


/** Initialise by loading textures etc. */
void SkyBox::Init(void) {
	RawLoader rawLoader;

	skyTexture = rawLoader.LoadTextureRAW("skyboxtexture.raw", 0, 4096, 3072);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);

	glPushMatrix();

	GLfloat emissiveMaterial[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat nonEmissiveMaterial[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	// make the sky glow and bright
	glMaterialfv(GL_FRONT, GL_EMISSION, emissiveMaterial);
	glScalef(512.0f, 512.0f, 512.0f);
	glTranslatef(1.0f, 0.6f, 1.0f);

	//walls
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.01f, 0.665f); glVertex3f(-1.0f, -0.5f, 1.0f);
	glTexCoord2f(0.01f, 0.334f); glVertex3f(-1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.25f, 0.334f); glVertex3f(1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.25f, 0.665f); glVertex3f(1.0f, -0.5f, 1.0f);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.25f, 0.665f); glVertex3f(-1.0f, -0.5f, 1.0f);
	glTexCoord2f(0.25f, 0.334f); glVertex3f(-1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.5f, 0.334f); glVertex3f(1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.5f, 0.665f); glVertex3f(1.0f, -0.5f, 1.0f);
	glEnd();
	glPopMatrix();

	glRotatef(90.0f, 0, 1.0f, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.5f, 0.665f); glVertex3f(-1.0f, -0.5f, 1.0f);
	glTexCoord2f(0.5f, 0.334f); glVertex3f(-1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.75f, 0.334f); glVertex3f(1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.75f, 0.665f); glVertex3f(1.0f, -0.5f, 1.0f);
	glEnd();
	glPopMatrix();

	glRotatef(90.0f, 0, 1.0f, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); 
	glTexCoord2f(0.75f, 0.665f); glVertex3f(-1.0f, -0.5f, 1.0f);
	glTexCoord2f(0.75f, 0.334f); glVertex3f(-1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.999f, 0.334f); glVertex3f(1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.999f, 0.665f); glVertex3f(1.0f, -0.5f, 1.0f);
	glEnd();
	glPopMatrix();

	// Top
	glRotatef(180.0f, 0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0f, 0);
	glTexCoord2f(0.251f, 0.001f); glVertex3f(-1.0f, 0.5f, -1.0f);
	glTexCoord2f(0.499f, 0.001f); glVertex3f(1.0f, 0.5f, -1.0f);
	glTexCoord2f(0.499f, 0.332f); glVertex3f(1.0f, 0.5f, 1.0f);
	glTexCoord2f(0.251f, 0.332f); glVertex3f(-1.0f, 0.5f, 1.0f);
	glEnd();

	// Turn off emissive lighting
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nonEmissiveMaterial);
	glPopMatrix();

	glEndList();
}

/** Display the skybox */
void SkyBox::Display(void) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glCallList(displayList);
	glPopMatrix();
}