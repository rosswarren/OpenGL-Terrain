#include "StdAfx.h"
#include "Lava.h"


Lava::Lava(void) {
}


Lava::~Lava(void) {
}


/**
* Initialise by loading textures etc.
*/
void Lava::Init(void) {
	//load textures
	RawLoader rawLoader;
	Shapes shapes;

	lavaTexture = rawLoader.LoadTextureRAW("lavatexture.raw", 0, 1024);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glBindTexture(GL_TEXTURE_2D, lavaTexture); // bind the texture
	glPushMatrix();
	glTranslatef(512.0f, -250.0f, 512.0f);
	glScalef(512.0f, 400.0f, 512.0f);
	glNormal3f(0, 1.0f, 0);
	shapes.cube();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void Lava::Display(void) {
	glCallList(displayList);
}