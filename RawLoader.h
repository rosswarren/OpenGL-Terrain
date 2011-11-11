#pragma once

#include "heightfield.h"

class RawLoader
{
public:
	RawLoader(void);
	~RawLoader(void);

	GLuint LoadTextureRAW(const char * filename, int wrap, int size);
};

