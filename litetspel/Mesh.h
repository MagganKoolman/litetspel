#pragma once

#include "Assets.h"
#include <GL\glew.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <GLM\glm.hpp>

class Mesh : public Asset
{
public:
    /*Load a mesh from a file. Returns true if the load was successful.*/
    bool load( string file );
    /*Unloads the mesh and frees the memory on the GPU.*/
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
