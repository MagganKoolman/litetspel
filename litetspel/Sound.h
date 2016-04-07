#pragma once

#include "Assets.h"
#include <SDL\SDL.h>

class Sound : public Asset
{
public:
    bool load( string& file );
    void unload();
    
    Sound& operator=( const Sound& ref );
    Sound( const Sound& ref );
    Sound();
    ~Sound();

private:
    // TODO: Get SDL_Mixer
};
