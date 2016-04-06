#pragma once

#include <map>
#include <string>
using std::map;
using std::string;

class Asset
{
public:
    virtual bool load( string file ) = 0;
    virtual void unload() = 0;
};

class Assets
{
public:
    /*Load an asset from a file. Returns a pointer to the asset if successful or nullptr if not.*/
    template<typename T> T* load( string file )
    {
        T* result = nullptr;

        map<string,Asset*>::const_iterator it = mAssets.find( file );
        if( it != mAssets.end() )
            result = it->second;
        else
        {
            result = new T();
            if( !result->load( file ) )
            {
                delete result;
                result = nullptr;
            }
        }

        return result;
    }
    
    /*Unloads all assets and deletes them.*/
    void unload();

    Assets& operator=( const Assets& ref );
    Assets( const Assets& ref );
    Assets();
    ~Assets();

private:
    map<string,Asset*> mAssets;
};
