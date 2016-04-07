#include "Mesh.h"

bool Mesh::load( string& file )
{
    // TA can put their stuff in here
    return false;
}

void Mesh::unload()
{
    if( mVertexArray > 0 )
        glDeleteVertexArrays( 1, &mVertexArray );
    if( mVertexBuffer > 0 )
        glDeleteBuffers( 1, &mVertexBuffer );
    if( mIndexBuffer > 0 )
        glDeleteBuffers( 1, &mIndexBuffer );

    mVertexArray = mVertexBuffer = mIndexBuffer = 0;
}

Mesh& Mesh::operator=( const Mesh& ref )
{
    mVertexArray = ref.mVertexArray;
    mVertexBuffer = ref.mVertexBuffer;
    mIndexBuffer = ref.mIndexBuffer;
    return *this;
}

Mesh::Mesh( const Mesh& ref )
        : mVertexArray( ref.mVertexArray ), mVertexBuffer( ref.mVertexBuffer ), mIndexBuffer( ref.mIndexBuffer )
{    
}

Mesh::Mesh()
        : mVertexArray( 0 ), mVertexBuffer( 0 ), mIndexBuffer( 0 )
{
}

Mesh::~Mesh()
{
}
