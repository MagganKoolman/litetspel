#pragma once

#include "Assets.h"
#include <SDL\SDL.h>

class Sound : public Asset
{
public:
    /* Load a sounds from a file. Returns true if the load was successful.*/
    bool load( string& file );
    /* Unloads the sound. */
    void unload();
    
    Sound& operator=( const Sound& ref );
    Sound( const Sound& ref );
    Sound();
    ~Sound();

private:
    // TODO: Get SDL_Mixer
};
