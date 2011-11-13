#pragma once
#include "Terrain.h"

class Lava {
private:
	GLuint lavaTexture;
	GLuint displayList;
	GLfloat height;
public:
	Lava(void);
	~Lava(void);

	void Init();
	void Display();
	GLfloat getHeight(void);
	void increaseHeight();
	void decreaseHeight();
};

