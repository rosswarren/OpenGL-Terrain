#include "StdAfx.h"
#include "Building.h"


Building::Building(void) {
}


Building::~Building(void) {
}

/**
* Initialise by loading textures etc.
*/
void Building::Init(void) {
	//load textures
	RawLoader rawLoader;
	Shapes shapes;

	texture = rawLoader.LoadTextureRAW("buildingtexture.raw", 1, 350, 500);



	// load the building to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glBindTexture(GL_TEXTURE_2D, texture); // bind the texture
	glPushMatrix();
	glTranslatef(740.0f, 210.0f, 250.0f);
	glScalef(20.0f, 60.0f, 20.0f);
	shapes.cube();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void Building::Display(void) {
	GLfloat refinerycolour[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, refinerycolour); // material colour
	glCallList(displayList);
}
