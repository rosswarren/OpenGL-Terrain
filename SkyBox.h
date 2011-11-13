#pragma once

#include "Terrain.h"

class SkyBox {
private:
	GLuint skyTexture;
	GLuint displayList;
public:
	SkyBox(void); //constructor
	~SkyBox(void); //destructor

	void Init();
	void Display();
};