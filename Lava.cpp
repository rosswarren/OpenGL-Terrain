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

	lavaTexture = rawLoader.LoadTextureRAW("lavatexture.raw", 0, 1024, 1024);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);

	GLfloat lavacolour[4] = {1.0f, 1.0f, 1.0f, 0.7f};
	

	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lavacolour); // material colour
	glBindTexture(GL_TEXTURE_2D, lavaTexture); // bind the texture
	glTranslatef(512.0f, -250.0f, 512.0f);
	glScalef(512.0f, 400.0f, 512.0f);
	glNormal3f(0, 1.0f, 0);
	shapes.cube();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
}

void Lava::Display(void) {
	glCallList(displayList);
}