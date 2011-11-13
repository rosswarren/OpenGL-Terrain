#pragma once
#include "Terrain.h"

class Lava {
private:
	GLuint lavaTexture;
	GLuint displayList;
public:
	Lava(void);
	~Lava(void);

	void Init();
	void Display();

	GLfloat height;
};

