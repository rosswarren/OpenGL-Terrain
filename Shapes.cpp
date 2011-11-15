#include "Shapes.h"

#ifndef M_PI
#define M_PI 3.14159265f
#endif


Shapes::Shapes(void) {
}


Shapes::~Shapes(void) {
}

// draw a cube with normals and texture coordinates
void Shapes::cube(void) {
	glBegin(GL_QUADS);
    // Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
	glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
	glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad

	glNormal3f(0.0f, 1.0f, 0.0f);
	glEnd();
}

// draws a cuboid, which is just a cube scaled
void Shapes::cuboid(GLfloat width, GLfloat height, GLfloat depth) {
	glPushMatrix();
	glScalef(width / 2 , height / 2, depth / 2);
	cube();
	glPopMatrix();
}

/** draw a gear 
* Adapted from here http://www.opengl.org/resources/code/samples/glut_examples/mesademos/mesademos.html
*/
void Shapes::gear(GLfloat innerRadius, GLfloat outerRadius, GLfloat width, GLint teeth, GLfloat tooth_depth) {
	GLint i; //general purpose incrementer for loops
	GLfloat r0, r1, r2, u, v, len, da;
	GLdouble angle;

	width /= 2; // half width since it's half is always needed in this method

	r0 = innerRadius;
	r1 = outerRadius - tooth_depth / 2.0f;
	r2 = outerRadius + tooth_depth / 2.0f;
	da = 2.0f * (GLfloat)M_PI / teeth / 4.0f;
	glShadeModel(GL_SMOOTH); // set type of shading to smooth

	glNormal3f(0.0f, 0.0f, 1.0f); // normal for the front of the gear

	/* draw front face */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0f * M_PI / teeth;
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
	}

	glEnd();

	/* draw front sides of teeth */
	glBegin(GL_QUADS);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
	}

	glEnd();

	glNormal3f(0.0f, 0.0f, -1.0f); // normal for the back of the gear

	/* draw back face */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
	}

	glEnd();

	/* draw back sides of teeth */
	glBegin(GL_QUADS);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), -width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
	}

	glEnd();

	/* draw outward faces of teeth */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
		u = (GLfloat) (r2 * cos(angle + da) - r1 * cos(angle));
		v = (GLfloat) (r2 * sin(angle + da) - r1 * sin(angle));
		len = (GLfloat) (sqrt(u * u + v * v));
		u /= len;
		v /= len;
		glNormal3d(v, -u, 0.0);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), -width);
		glNormal3d(cos(angle), sin(angle), 0.0);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width);
		u = (GLfloat) (r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da));
		v = (GLfloat) (r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da));
		glNormal3f(v, -u, 0.0f);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glNormal3d(cos(angle), sin(angle), 0.0);
	}

	glVertex3d(r1 * cos(0.0), r1 * sin(0.0), width);
	glVertex3d(r1 * cos(0.0), r1 * sin(0.0), -width);

	glEnd();

	/* draw inside radius cylinder */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glNormal3d(-cos(angle), -sin(angle), 0.0);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
	}

	glEnd();
}

/** draws the supports for the big metal gear */
void Shapes::innergearsupports(void) {
    int max = 360;
    int index;

	for (index = 120; index <= max; index += 120) {
		glPushMatrix();
		glRotatef((GLfloat)index, 0.0f, 0.0f, 1.0f);
		glTranslatef(6.5f, 0.0, 0.0);
		cuboid(13.0f, 4.0f, 1.0f);
		glPopMatrix();
	}
}

/** draws a cylinder with capped ends */
void Shapes::cylinder(double height, double radiusBase, double radiusTop, int slices, int stacks, GLUquadricObj* quadric) {
	//gluQuadricDrawstyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, 1);
	gluCylinder(quadric, radiusBase, radiusTop, height, slices, stacks); //first draw the cylinder

	// Draw the top disk cap
	glPushMatrix();
	glTranslated(0.0, 0.0, height); //move to top to cylinder
	gluDisk(quadric, 0.0, radiusTop, slices, stacks);
	glPopMatrix();

	// Draw the bottom disk cap
	glPushMatrix();
	glRotated(180.0, 1.0, 0.0, 0.0); //flip to face down
	gluDisk(quadric, 0.0, radiusBase, slices, stacks);
	glPopMatrix();
}

/** draw whisk with spindle, part of the refinery */
void Shapes::drawWhisk(int direction, double angle, int smallgear, int whisk, GLUquadricObj* quadric) {
	GLdouble whiskangle = direction == 0 ? angle : -angle; // reverse the angle if direction is 0

	glPushMatrix();
	glRotated(whiskangle, 0.0, 1.0, 0.0); // spin the whisk and gear
	glRotatef(90.0, 1.0, 0.0, 0.0); //rotate 90 degrees so it is facing downwards
	gear(1.0f, 4.0f, 5.0f, 12, 0.7f);
	//glCallList(smallgear); // draw the plastic gear
	glTranslatef(0.0f, 0.0f, -6.0f); // move down 6
	glCallList(whisk);  // draw the whisk part	
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); //rotate 90 degrees so it is facing downwards
	glTranslatef(0.0f, 0.0f, -6.0f); // move down 6
	cylinder(67.5, 0.5, 0.5, 10, 1, quadric); // thin inner spindle
	glPopMatrix();
}