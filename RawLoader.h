#pragma once

#include "Terrain.h"

class RawLoader {
public:
	RawLoader(void);
	~RawLoader(void);

	GLuint LoadTextureRAW(char * filename, int wrap, int width, int height);
};

