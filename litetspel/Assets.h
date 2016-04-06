#pragma once

#include <map>
#include <string>
using std::map;
using std::string;

class Asset
{
public:
	virtual bool Load( string file ) = 0;
	virtual void Unload() = 0;
};

class Assets
{
public:
	/*Load an asset from a file.*/
	template<typename T> T* Load( string file )
	{
		T* result = nullptr;

		map<string,Asset*>::const_iterator it = mAssets.find( file );
		if( it != mAssets.end() )
			result = it->second;
		else
		{
			result = new T();
			if( !result->Load( file ) )
			{
				delete result;
				result = nullptr;
			}
		}

		return result;
	}
	
	/*Unloads all assets.*/
	void Unload();

	Assets& operator=( const Assets& ref );
	Assets( const Assets& ref );
	Assets();
	~Assets();

private:
	map<string,Asset*> mAssets;
};