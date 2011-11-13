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

	/* white plastic gear */
	smallgear = glGenLists(1);
	glNewList(smallgear, GL_COMPILE);
	glColor3fv(whiteplastic);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiteplastic);
	shapes.gear(1.0f, 4.0f, 5.0f, 12, 0.7f); // make gear inner radius, outer radius, width, number of teeth, teeth size
	glEndList();

	/* big metal gear */
	biggear = glGenLists(1);
	glNewList(biggear, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 10);

	shapes.gear(11.0f, 15.0f, 3.0f, 50, 2.0f);
	glEndList();

	/* inner gear support and handle */
	innergearsupport = glGenLists(1);
	glNewList(innergearsupport, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is

	/* big gear axle */
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -8.0f);
	shapes.cylinder(16.0, 1.5, 1.5, 16, 1, quadric);
	glPopMatrix();

	/* inner gear supports */
	shapes.innergearsupports();

	/* handle support
	glPushMatrix();
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	glTranslatef(11.7f, 0.0f, 7.2f);
	shapes.cuboid(20.0f, 2.0f, 1.0f);
	glPopMatrix();  */

	/* handle 
	glPushMatrix();
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(20.0, 0.0, 12.0);
	glColor3fv(handlecolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, handlecolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, handlespecular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is
	shapes.cylinder(8.0, 2.1, 2.8, 30, 100, quadric);
	glPopMatrix(); */


	glEndList();

	/* strut */
	strut = glGenLists(1);
	glNewList(strut, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is
	glPushMatrix();
	shapes.cuboid(5.0f, 30.0f, 1.0f);
	glPopMatrix();
	glEndList();

	/* top strut */
	topstrut = glGenLists(1);
	glNewList(topstrut, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is
	glPushMatrix();
	shapes.cuboid(5.0f, 1.0f, 12.0f);
	glPopMatrix();
	glEndList();

	/* angled strut */
	angledstrut = glGenLists(1);
	glNewList(angledstrut, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is
	glPushMatrix();
	shapes.cuboid(5.0f, 25.0f, 1.0f);
	glPopMatrix();
	glEndList();

	/* handle */
	handle = glGenLists(1);
	glNewList(handle, GL_COMPILE);
	glColor3fv(handlecolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, handlecolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, handlespecular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is
	shapes.cuboid(10.0f, 10.0f, 38.0f);
	glPopMatrix();
	glEndList();

	/* whisk */
	whisk = glGenLists(1);
	glNewList(whisk, GL_COMPILE);
	glColor3fv(whiskcolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiskcolor); // material colour
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is

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

	glEnable(GL_TEXTURE_2D); // enable drawing the texture
	glBindTexture(GL_TEXTURE_2D, rustTexture); // bind the texture

	glTranslatef(440.0f, 200.0f, 550.0f);

	GLfloat refinerycolour[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, refinerycolour); // material colour

	glPushMatrix();
	glTranslatef(0.0f, 17.0f, 5.0f);
	glRotatef((GLfloat)angle, 0.0f, 0.0f, 1.0f);
	shapes.cylinder(190.0f, 1.6, 1.6, 16, 1, quadric);
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
		glPushMatrix();
		

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
		shapes.cylinder(10.0, 0.5, 0.5, 10, 1, quadric);
		glPopMatrix();

		// big metal gear plus handle
		glPushMatrix();
		glTranslatef(0.0f, 17.0f, 0.0f);
		glRotated(angle / 3.75, 0.0, 0.0, 1.0);
		glCallList(biggear);
		glCallList(innergearsupport);
		glPopMatrix();

		// side struts
		glPushMatrix();
		glTranslatef(0.0f, 20.0f, 5.0f);
		glCallList(strut);
		glTranslatef(0.0f, 0.0f, -10.0f);
		glCallList(strut);
		glPopMatrix();

		// top joining struts
		glPushMatrix();
		glTranslatef(0.0f, 35.0f, 0.0f);
		
		
		glCallList(topstrut);
		
		glPopMatrix();

		// angled top struts
		/* glPushMatrix();
		glTranslatef(0.0f, 45.0f, 11.0f);
		glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
		glCallList(angledstrut);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 45.0f, -11.0f);
		glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
		glCallList(angledstrut);
		glPopMatrix(); */

		// top handle
		/* glPushMatrix();
		glTranslatef(0.0f, 60.0f, 0.0f);
		glCallList(handle);
		glPopMatrix(); */

		glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


