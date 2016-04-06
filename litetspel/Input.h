#pragma once

#include <SDL\SDL.h>
#include <glm\glm.hpp>

enum
{
    MBUTTON_LEFT = 0,
    MBUTTON_RIGHT,
    MBUTTON_MIDDLE,
    MAX_BUTTONS,
};

#define MAX_KEYS 128

class Input
{
public:
    bool Update();

    bool KeyDown( int key );
    bool KeyUp( int key );
    bool KeyPressed( int key );
    bool KeyReleased( int key );

    bool ButtonDown( int button );
    bool ButtonUp( int button );
    bool ButtonPressed( int button );
    bool ButtonReleased( int button );

    glm::vec2 MousePosition();
    glm::vec2 MouseDelta();
    
    Input& operator=( const Input& ref );
    Input( const Input& ref );
    Input();
    ~Input();
    
private:
    bool mCurKeys[MAX_KEYS];
    bool mPrevKeys[MAX_KEYS];
    bool mCurButtons[MAX_BUTTONS];
    bool mPrevButtons[MAX_BUTTONS];
    glm::vec2 mCurMouse;
    glm::vec2 mPrevMouse;
};
