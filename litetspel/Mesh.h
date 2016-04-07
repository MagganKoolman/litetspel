#pragma once

#include "Assets.h"
#include <GL\glew.h>

class Mesh : public Asset
{
public:
	bool load( string& file );
	void unload();

	Mesh& operator=( const Mesh& ref );
	Mesh( const Mesh& ref );
	Mesh();
	~Mesh();
	
private:
	GLuint mVertexArray;
	GLuint mVertexBuffer;
	GLuint mIndexBuffer;
};