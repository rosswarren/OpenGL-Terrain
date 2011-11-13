#pragma once

#include "Terrain.h"

class Refinery
{
private:
	GLUquadricObj* quadric;
	GLuint smallgear, biggear, innergearsupport, strut, topstrut, angledstrut, handle, whisk;
	GLuint rustTexture;
	double angle;
public:
	Refinery(void);
	~Refinery(void);

	void Init();
	void Display();
};

