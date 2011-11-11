#pragma once

#include "heightfield.h"

class Refinery
{
private:
	GLUquadricObj* quadric;
	GLint smallgear, biggear, innergearsupport, strut, topstrut, angledstrut, handle, whisk;
	double angle;
public:
	Refinery(void);
	~Refinery(void);

	void Init();
	void Display();
};

