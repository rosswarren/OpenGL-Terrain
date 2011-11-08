#include <GL/glew.h>
#include <GL/freeglut.h>

class Vert{
	public:  
		float x;
		float y;
		float z;
};

class TexCoord {
	public:
		float u;
		float v;
};

class Normal {
	public:
		float x;
		float y;
		float z;
};

class HeightField {
private:
	int hmHeight;
	int hmWidth;
	int terrainList;
	unsigned int tID[2];

	int vhVertexCount;
	Vert *vhVertices;
	TexCoord *vhTexCoords;
	Normal *vhNormals;

	unsigned int vhVBOVertices;
	unsigned int vhVBOTexCoords;
	unsigned int vhVBONormals;
public:
	bool Create();
	void Render();
	void Init();
	void Cube();
	GLuint LoadTextureRAW( const char * filename, int wrap );
	int hLOD;
	GLubyte hHeightField[1024][1024];
	GLubyte texture[1024][1024];
	GLubyte lavaTexture[1024][1024];
	float waterheight;
};