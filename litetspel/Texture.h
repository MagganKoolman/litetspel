#pragma once

#include <GL\glew.h>
#include <SDL\SDL_image.h>
#include "Assets.h"

class Texture : public Asset
{
public:
	bool Load( string file );
	void Unload();

	Texture& operator=( const Texture& ref );
	Texture( const Texture& ref );
	Texture();
	~Texture();

private:
	GLuint mID;
	int mWidth, mHeight;
};