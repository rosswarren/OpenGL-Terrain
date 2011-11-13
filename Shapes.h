#pragma once

#include "Terrain.h"

class Shapes
{
public:
	Shapes(void);
	~Shapes(void);

	void cube(void);
	void cuboid(GLfloat width, GLfloat height, GLfloat depth);
	void gear(GLfloat innerRadius, GLfloat outerRadius, GLfloat width, GLint teeth, GLfloat tooth_depth);
	void innergearsupports(void);
	void cylinder(double height, double radiusBase, double radiusTop, int slices, int stacks, GLUquadricObj* quadric);
	void drawWhisk(int direction, double angle, int smallgear, int whisk, GLUquadricObj* quadric);
};

