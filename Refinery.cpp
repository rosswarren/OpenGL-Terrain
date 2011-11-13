#include "StdAfx.h"
#include "Refinery.h"


Refinery::Refinery(void) {
}


Refinery::~Refinery(void) {
}

/**
* Initialise by loading textures etc.
*/
void Refinery::Init(void) {
	//load textures
	RawLoader rawLoader;
	Shapes shapes;

	rustTexture = rawLoader.LoadTextureRAW("rusttexture.raw", 1, 600, 600);

	angle = 0;

	GLfloat pos[4] = {5.0f, 5.0f, 10.0f, 0.0f};
	GLfloat whiteplastic[4] = {0.92f, 0.92f, 0.92f, 1.0f};
	GLfloat whiskcolor[4] = {0.74f, 0.74f, 0.74f, 1.0f};
	GLfloat handlecolor[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat specReflection[4] = { 0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat handlespecular[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat diffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};

	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_TRUE);

	/* white plastic gear
	smallgear = glGenLists(1);
	glNewList(smallgear, GL_COMPILE);
	shapes.gear(1.0f, 4.0f, 5.0f, 12, 0.7f); // make gear inner radius, outer radius, width, number of teeth, teeth size
	glEndList(); */

	/* big metal gear 
	biggear = glGenLists(1);
	glNewList(biggear, GL_COMPILE);
	shapes.gear(11.0f, 15.0f, 3.0f, 50.0f, 2.0f);
	glEndList();*/

	/* inner gear support */
	//innergearsupport = glGenLists(1);
	//glNewList(innergearsupport, GL_COMPILE);
	/* inner gear supports */
	//shapes.innergearsupports();
	//glEndList();

	/* strut
	strut = glGenLists(1);
	glNewList(strut, GL_COMPILE);
	glColor3fv(whiskcolor);
	shapes.cuboid(5.0f, 30.0f, 1.0f);
	glEndList(); */

	/* top strut
	topstrut = glGenLists(1);
	glNewList(topstrut, GL_COMPILE);
	glTranslatef(0.0f, 35.0f, 0.0f);
	shapes.cuboid(5.0f, 1.0f, 12.0f);
	glEndList(); */

	/* angled strut */
//	angledstrut = glGenLists(1);
//	glNewList(angledstrut, GL_COMPILE);
//	shapes.cuboid(5.0f, 25.0f, 1.0f);
//	glEndList();

	/* handle */
	///handle = glGenLists(1);
	//glNewList(handle, GL_COMPILE);
	//shapes.cuboid(10.0f, 10.0f, 38.0f);
	//glEndList();

	/* whisk */
	whisk = glGenLists(1);
	glNewList(whisk, GL_COMPILE);

	glPushMatrix();
	glTranslatef(0, 0, 4.0f); // move down to the gear
	shapes.cylinder(30.0, 1.0, 1.0, 10, 10, quadric); // thick cyclinder spacer
	glTranslatef(0, 0, 30.0f);
	shapes.cylinder(5.0, 3.0, 4.0, 20, 1, quadric);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	for (int counter = 0; counter < 4; counter++) {
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(4.3f, 16.5f, 0.0f);
		glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
		shapes.cuboid(1.0f, 24.0f, 2.0f);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(3.1f, 30.0f, 0.0f);
		glRotatef(50.0f, 0.0f, 0.0f, 1.0f);
		shapes.cuboid(1.0f, 6.6f, 2.0f);
		glPopMatrix();
	}

	glPopMatrix();
	glEndList();
}

void Refinery::Display(void) {
	Shapes shapes;

	angle += 0.40;

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, rustTexture); // bind the texture

	glTranslatef(440.0f, 200.0f, 550.0f);

	glPushMatrix();
	glTranslatef(0.0f, 17.0f, 5.0f);
	glRotatef((GLfloat)angle, 0.0f, 0.0f, 1.0f);
	shapes.cylinder(190.0f, 1.6, 1.6, 8, 1, quadric);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -50.0f, 6.0f);
	shapes.cuboid(8.0f, 180.0f, 8.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 17.0f, 192.0f);
	shapes.cuboid(12.0f, 14.0f, 18.0f);
	glPopMatrix();

	for (int i = 0; i < 5; i++) {
		glTranslatef(0, 0, 25.0f);
		// white plastic gears and whisks
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);
		shapes.drawWhisk(0, angle, smallgear, whisk, quadric);
		glTranslatef(0.0f, 0.0f, 10.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		shapes.drawWhisk(1, angle, smallgear, whisk, quadric);
		glPopMatrix();

		// bottom strut
		glPushMatrix();
		glTranslatef(0.0f, -61.5f, -5.0f);
		shapes.cylinder(10.0, 0.5, 0.5, 5, 1, quadric);
		glPopMatrix();

		// big metal gear plus handle
		glPushMatrix();
		glTranslatef(0.0f, 17.0f, 0.0f);
		glRotated(angle / 3.75, 0.0, 0.0, 1.0);
		shapes.gear(11.0f, 15.0f, 3.0f, 50.0f, 2.0f);
		//glCallList(innergearsupport);
		shapes.innergearsupports();
		glPopMatrix();

		// side struts
		glPushMatrix();
		glTranslatef(0.0f, 20.0f, 5.0f);
		shapes.cuboid(5.0f, 30.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, -10.0f);
		shapes.cuboid(5.0f, 30.0f, 1.0f);
		glPopMatrix();

		// top joining struts
		glTranslatef(0.0f, 35.0f, 0.0f);
		shapes.cuboid(5.0f, 1.0f, 12.0f);
	}

	glPopMatrix();
}


