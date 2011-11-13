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
	glPushMatrix();
	
	glTranslatef(740.0f, 210.0f, 250.0f);
	shapes.cuboid(20.0f, 60.0f, 20.0f);
	glPopMatrix();
	glEndList();
}

void Building::Display(void) {
	//glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture); // bind the texture
	glCallList(displayList);
	//glPopMatrix();
}
