#pragma once
#include "heightfield.h"

class Lava {
private:
	GLuint lavaTexture;
	GLuint displayList;
public:
	Lava(void);
	~Lava(void);

	void Init();
	void Display();
};

