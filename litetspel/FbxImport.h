#pragma once

#include "fbxsdk.h"
#include <vector>
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;


class FbxImport
{
public:
	/*Functions*/

	void initializeImporter();
	void processMesh(FbxMesh* inputMesh);
	
	void processVertices(FbxMesh* inputMesh);
	void processNormals(FbxMesh* inputMesh);
	void processTangents(FbxMesh* inputMesh);
	void processBiTangents(FbxMesh* inputMesh);
	void processUVs(FbxMesh* inputMesh);

	void processLight(FbxLight* inputLight);
	void processCamera(FbxCamera* inputCamera);

	std::vector<Mesh> mMeshList;
	//for(mMeshList.size()):
	//vertices localVertexList = mMeshList[i].getVertices();
	//material currMat = mMeshList[i].getMaterial();
	//matrix meshOis = 
	std::vector<Light*> mLightList;
	std::vector<Camera*> mCameraList;

	Mesh mesh;

	FbxImport();
	~FbxImport();

private:

	FbxNode* pmRootNode;
	FbxManager* pmManager;
	FbxIOSettings* pmSettings;
	FbxScene* pmScene;

	int meshCount;
};



