#pragma once

#include "Terrain.h"
#include <math.h>

const int numTrees = 10;

class Trees
{
private:
	GLUquadricObj* quadric;
	GLuint woodTexture;
	GLuint treeLists[numTrees];
	Vert randomHeights[numTrees];
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
	void SetUpHeights(Terrain &terrain, float lavaHeight);
	void SetUpHeight(int i, Terrain &terrain, float lavaHeight);
};

