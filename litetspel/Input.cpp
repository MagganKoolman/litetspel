#include "Input.h"

bool Input::Update()
{
    bool result = true;

    // copy last frames current input to current frames previous input
    for( int i=0; i<MAX_KEYS; i++ )
        mPrevKeys[i] = mCurKeys[i];

    for( int i=0; i<MAX_BUTTONS; i++ )
        mPrevButtons[i] = mCurButtons[i];

    // poll SDL for input
    SDL_Event e;
    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
            result = false;
        if( e.type == SDL_KEYDOWN )
        {
            int key = e.key.keysym.sym;
            if( key >= 0 && key < MAX_KEYS )
                mCurKeys[key] = true;
        }
        else if( e.type == SDL_KEYUP )
        {
            int key = e.key.keysym.sym;
            if( key >= 0 && key < MAX_KEYS )
                mCurKeys[key] = false;
        }
        else if( e.type == SDL_MOUSEBUTTONDOWN )
        {
            int button = e.button.button-1; // SDL_BUTTON_LEFT is 1, we want it to be 0
            if( button >= 0 && button < MAX_BUTTONS )
                mCurButtons[button] = true;
        }
        else if( e.type == SDL_MOUSEBUTTONUP )
        {
            int button = e.button.button-1;
            if( button >= 0 && button < MAX_BUTTONS )
                mCurButtons[button] = false;
        }
    }

    return result;
}

bool Input::KeyDown( int key )
{
    if( key < 0 || key >= MAX_KEYS )
        return false;
    return mCurKeys[key];
}

bool Input::KeyUp( int key )
{
    if( key < 0 || key >= MAX_KEYS )
        return false;
    return !mCurKeys[key];
}

bool Input::KeyPressed( int key )
{
    if( key < 0 || key >= MAX_KEYS )
        return false;
    if( mPrevKeys[key] )
        return false;
    return mCurKeys[key];
}

bool Input::KeyReleased( int key )
{
    if( key < 0 || key >= MAX_KEYS )
        return false;
    if( mCurKeys[key] )
        return false;
    return mPrevKeys[key];
}

bool Input::ButtonDown( int button )
{
    if( button < 0 || button >= MAX_BUTTONS )
        return false;
    return mCurButtons[button];
}

bool Input::ButtonUp( int button )
{
    if( button < 0 || button >= MAX_BUTTONS )
        return false;
    return !mCurButtons[button];
}

bool Input::ButtonPressed( int button )
{
    if( button < 0 || button >= MAX_BUTTONS )
        return false;
    if( mPrevButtons[button] )
        return false;
    return mCurButtons[button];
}

bool Input::ButtonReleased( int button )
{
    if( button < 0 || button >= MAX_BUTTONS )
        return false;
    if( mCurButtons[button] )
        return false;
    return mPrevButtons[button];
}

glm::vec2 Input::MousePosition()
{
    return mCurMouse;
}

glm::vec2 Input::MouseDelta()
{
    return ( mPrevMouse - mCurMouse );
}

Input& Input::operator=( const Input& ref )
{
    // copy values from reference
    for( int i=0; i<MAX_KEYS; i++ )
    {
        mCurKeys[i] = ref.mCurKeys[i];
        mPrevKeys[i] = ref.mPrevKeys[i];
    }

    for( int i=0; i<MAX_BUTTONS; i++ )
    {
        mCurButtons[i] = ref.mCurButtons[i];
        mPrevButtons[i] = ref.mPrevButtons[i];
    }

    mCurMouse = ref.mCurMouse;
    mPrevMouse = ref.mPrevMouse;

    return *this;
}

Input::Input( const Input& ref )
        : mCurMouse( ref.mCurMouse ), mPrevMouse( ref.mPrevMouse )
{
    // copy values from reference
    for( int i=0; i<MAX_KEYS; i++ )
    {
        mCurKeys[i] = ref.mCurKeys[i];
        mPrevKeys[i] = ref.mPrevKeys[i];
    }

    for( int i=0; i<MAX_BUTTONS; i++ )
    {
        mCurButtons[i] = ref.mCurButtons[i];
        mPrevButtons[i] = ref.mPrevButtons[i];
    }
}

Input::Input()
{
    // initialize all values to false
    for( int i=0; i<MAX_KEYS; i++ )
        mCurKeys[i] = mPrevKeys[i] = false;

    for( int i=0; i<MAX_BUTTONS; i++ )
        mCurButtons[i] = mPrevButtons[i] = false;

    // TODO: Initialize mouse position?
}

Input::~Input()
{
}
