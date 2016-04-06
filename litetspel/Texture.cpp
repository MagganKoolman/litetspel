#include "Texture.h"

bool Texture::Load( string file )
{
    bool result = false;

    SDL_Surface* img = IMG_Load( file.c_str() );
    if( img )
    {
        glGenTextures( 1, &mID );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels );

        mWidth = img->w;
        mHeight = img->h;

        SDL_FreeSurface( img );
    }

    return result;
}

void Texture::Unload()
{
    if( mID > 0 )
        glDeleteTextures( 1, &mID );
    mWidth = mHeight = 0;
}

Texture& Texture::operator=( const Texture& ref )
{
    mID = ref.mID;
    mWidth = ref.mWidth;
    mHeight = ref.mHeight;
    return *this;
}

Texture::Texture( const Texture& ref )
    : mID( ref.mID ), mWidth( ref.mWidth ), mHeight( ref.mHeight )
{
}

Texture::Texture()
    : mID( 0 ), mWidth( 0 ), mHeight( 0 )
{
}

Texture::~Texture()
{
}
