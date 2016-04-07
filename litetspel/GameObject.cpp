#include "GameObject.h"

GameObject::GameObject( const GameObject& ref )
        : mPosition( ref.mPosition ), mRotation( ref.mRotation ), mpMesh( ref.mpMesh ), mpTexture( ref.mpTexture )
{
}

GameObject::GameObject()
        : mPosition( 0.0f ), mRotation( 0.0f, 0.0f, 0.0f, 0.0f ), mpMesh( nullptr ), mpTexture( nullptr )
{
}

GameObject::~GameObject()
{
}
