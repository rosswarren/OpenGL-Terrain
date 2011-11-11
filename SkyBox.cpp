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
	//load textures
	RawLoader rawLoader;

	skyTexture = rawLoader.LoadTextureRAW("skytexture.raw", 0, 512);
	skyTextureTop = rawLoader.LoadTextureRAW("skytexturetop.raw", 0, 512);
	skyTextureBottom = rawLoader.LoadTextureRAW("skytexturebottom.raw", 0, 512);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);

	glPushMatrix();

	GLfloat emissiveMaterial[] = {1.0f, 1.0f, 1.0f};
	GLfloat nonEmissiveMaterial[] = {0.0f, 0.0f, 0.0f};

	// Turn on Emissive lighting. We don't want shadows or dark patches on the skybox
	glMaterialfv(GL_FRONT, GL_EMISSION, emissiveMaterial);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, skyTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glScalef(512.0f, 512.0f, 512.0f);
	glTranslatef(1.0f, 0.6f, 1.0f);
	

	// Walls
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
			glRotatef((90 * i), 0, 1, 0);

			glBegin (GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f); 
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -0.5f, 1.0);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.5f, 1.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 0.5f, 1.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -0.5f, 1.0);
			glEnd();

		glPopMatrix();
	}


	// Ceiling
	glBindTexture( GL_TEXTURE_2D, skyTextureTop);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin (GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 0.5f, -1.0f);
		glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 0.5f, -1.0f);
		glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 0.5f, 1.0f);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 0.5f, 1.0f);
	glEnd();


	// Floor
	glBindTexture( GL_TEXTURE_2D, skyTextureBottom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin (GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -0.5f, -1.0f);
		glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, -0.5f,  1.0f);
		glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, -0.5f,  1.0f);
		glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, -0.5f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

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