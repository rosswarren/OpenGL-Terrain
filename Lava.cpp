#include "Lava.h"

/**
* Lava texture from deviantart
*/

Lava::Lava(void) {
	height = 100.0f;
}


Lava::~Lava(void) {
}

// Initialise by loading textures etc.
void Lava::Init(void) {
	//load textures
	RawLoader rawLoader;
	Shapes shapes;

	lavaTexture = rawLoader.LoadTextureRAW("lavatexture.raw", 0, 1024, 1024);

	// load the skybox to a display list
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);

	GLfloat lavacolour[4] = {1.0f, 1.0f, 1.0f, 0.8f};
	GLfloat emissiveMaterial[] = {1.0f, 1.0f, 1.0f};
	GLfloat nonEmissiveMaterial[] = {0.0f, 0.0f, 0.0f};

	// Turn on Emissive lighting. We don't want shadows or dark patches on the skybox
	glMaterialfv(GL_FRONT, GL_EMISSION, emissiveMaterial);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lavacolour); // material colour
	glBindTexture(GL_TEXTURE_2D, lavaTexture); // bind the texture
	glNormal3f(0, 1.0f, 0);
	shapes.cuboid(1024.0f, 100.0f, 1024.0f);
	glPopMatrix();

	// Turn off emissive lighting
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nonEmissiveMaterial);
	glEndList();
}

// display the lava
void Lava::Display(void) {
	glDepthMask(GL_FALSE);
	glPushMatrix();
	glTranslatef(512.0f, height, 512.0f);
	glCallList(displayList);
	glPopMatrix();
	glDepthMask(GL_TRUE);
}

/** return the lava height */
GLfloat Lava::getHeight(void) {
	return height;
}

/** increase the lava height */
void Lava::increaseHeight(void) {
	height += 1.0f;

	if (height > 215.0f) height = 215.0f;
}

/** decrease the lava height */
void Lava::decreaseHeight(void) {
	height -= 1.0f;

	if (height < 0.0f) height = 0.0f;
}