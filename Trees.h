#pragma once

#include "Terrain.h"
#include <math.h>

class Trees
{
private:
	GLUquadricObj* quadric;
	GLuint woodTexture;
	GLuint treeLists[5];
	int treeLvl;
	bool leaves;
	bool loaded;
	void tree(int level);
	int random(int min, int max);
public:
	Trees(void);
	~Trees(void);

	void Init();
	void Display();
	void IncreaseComplexity(void);
	void DecreaseComplexity(void);
	void Regen(void);
	int GetComplexity(void);
};

