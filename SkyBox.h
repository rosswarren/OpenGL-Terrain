#pragma once

#include "heightfield.h"

class SkyBox {
private:
	GLuint skyTexture;
	GLuint skyTextureTop;
	GLuint skyTextureBottom;
	GLuint displayList;
public:
	SkyBox(void); //constructor
	~SkyBox(void); //destructor

	void Init();
	void Display();
};