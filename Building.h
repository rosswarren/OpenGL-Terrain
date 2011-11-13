#pragma once
#include "Terrain.h"

class Building
{
private:
	GLuint displayList;
	GLuint texture;
public:
	Building(void);
	~Building(void);

	void Init();
	void Display();
};

