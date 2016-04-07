#pragma once

#include <GL\glew.h>
#include <SDL\SDL_image.h>
#include "Assets.h"

class Texture : public Asset
{
public:
    /*Loads a texture from the file supplied to the method. Returns true if load was successful.*/
    bool load( string file );
    /*Destroys the texture and frees the memory in the GPU.*/
    void unload();

    Texture& operator=( const Texture& ref );
    Texture( const Texture& ref );
    Texture();
    ~Texture();

private:
    GLuint mID;
    int mWidth, mHeight;
};
