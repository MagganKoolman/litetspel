#include "FbxImport.h"

FbxImport::~FbxImport()
{
}

FbxImport::FbxImport()
{
	meshCount = 1;
}


void FbxImport::initializeImporter()
{
	/*Initialize memory allocator.*/
	pmManager = FbxManager::Create();

	/*Initialize settings for the import.*/
	pmSettings = FbxIOSettings::Create(pmManager, IOSROOT);

	/*Settings the options manually, by default it is true.*/
	pmSettings->SetBoolProp(IMP_FBX_MATERIAL, true);
	pmSettings->SetBoolProp(IMP_FBX_TEXTURE, true);
	pmSettings->SetBoolProp(IMP_FBX_LINK, true);
	pmSettings->SetBoolProp(IMP_FBX_SHAPE, true);
	pmSettings->SetBoolProp(IMP_FBX_GOBO, true);
	pmSettings->SetBoolProp(IMP_FBX_ANIMATION, true);
	pmSettings->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

	/*Setting the importing settings.*/
	pmManager->SetIOSettings(pmSettings);

	FbxImporter* pImporter = FbxImporter::Create(pmManager, "");

	bool importStatus = pImporter->Initialize("C:/Users/pixet/Documents/fbx_box.fbx", -1, pmManager->GetIOSettings());
	/*Abort if the importer can't be intitialized.*/
	if (importStatus == false) {
		FBXSDK_printf("Error: Can't initialize the importer. Aborting...\n");
		exit(1);
	}
	FbxScene* pScene = FbxScene::Create(pmManager, "MyScene");

	importStatus = pImporter->Import(pScene);
	/*Abort if the scene can't be imported.*/
	if (importStatus == false) {
		FBXSDK_printf("Error: Can't initialize the importer. Aborting...\n");
		exit(1);
	}
	pImporter->Destroy();

	/*Get the handle to all of the objects in the scene.*/
	pmRootNode = pScene->GetRootNode();

	for (int childIndex = 0; childIndex < pmRootNode->GetChildCount(); childIndex++)
	{
		/*Getting the child nodes in the scene and their node attribute types.*/
		FbxNode* childNode = pmRootNode->GetChild(childIndex);
		FbxNodeAttribute::EType attributeType = childNode->GetNodeAttribute()->GetAttributeType();

		/*No attributes, then skip!*/
		if (childNode->GetNodeAttribute() == NULL)
			continue;

		/*To make sure we only want to import meshes, lights and cameras.*/
		if (attributeType != FbxNodeAttribute::eMesh && attributeType != FbxNodeAttribute::eLight &&
			attributeType != FbxNodeAttribute::eCamera)
			continue;
		
		if (attributeType == FbxNodeAttribute::eMesh)
		{
			cout << "\n" << "Object nr: " << meshCount << "\n";

			processMesh((FbxMesh*)childNode->GetNodeAttribute());
			meshCount += 1;
		}
		
		if (attributeType == FbxNodeAttribute::eLight)
		{
			processLight((FbxLight*)childNode->GetNodeAttribute());
		}
		
		if (attributeType == FbxNodeAttribute::eCamera)
		{
			processCamera((FbxCamera*)childNode->GetNodeAttribute());
		}
	}

}

void FbxImport::processMesh(FbxMesh * inputMesh)
{
	processVertices(inputMesh);

	processNormals(inputMesh);

	processTangents(inputMesh);

	processUVs(inputMesh);

	/*mMeshList.push_back(mesh.mp_VertexList);*/ //Want to push back a mesh with a vertex list... or? 
}

void FbxImport::processVertices(FbxMesh * inputMesh)
{
	/*Array of the control points of mesh.*/
	FbxVector4* vertices = inputMesh->GetControlPoints();  

	for (int i = 0; i < inputMesh->GetPolygonCount(); i++)
	{
		/*Getting vertices of a polygon in the mesh.*/
		int numPolygonVertices = inputMesh->GetPolygonSize(i); 

		/*If the mesh is not triangulated, meaning that there are quads in the mesh,
		then the program should abort, terminating the process.*/
		assert(numPolygonVertices == 3);

		for (int j = 0; j < numPolygonVertices; j++)
		{
			/*Getting the index to a control point "vertex".*/
			int polygonVertex = inputMesh->GetPolygonVertex(i, j); 

			mesh.vertexData.vertexPos[0] = (float)vertices[polygonVertex].mData[0];
			mesh.vertexData.vertexPos[1] = (float)vertices[polygonVertex].mData[1];
			mesh.vertexData.vertexPos[2] = (float)vertices[polygonVertex].mData[2];

			cout << "\n" << "Position: " << (float)vertices[polygonVertex].mData[0] << " " << 
					(float)vertices[polygonVertex].mData[1] << " " <<
					(float)vertices[polygonVertex].mData[1] << "\n";
	
			mesh.mpVertexList.push_back(mesh.vertexData);
		}
	}
}

void FbxImport::processNormals(FbxMesh * inputMesh)
{
	/*Get the normal element of the mesh.*/
	FbxGeometryElementNormal* normalElement = inputMesh->GetElementNormal(); 

	if (normalElement) /*If there is normal element then proceed.*/
	{
		/*Obtain normal of each vertex.*/
		if (normalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint) 
		{
			/*Obtain the normals of each vertex, because the mapping mode of the normal element is by control point.*/
			for (int vertexIndex = 0; vertexIndex < inputMesh->GetControlPointsCount(); vertexIndex++)
			{
				int normalIndex = 0;

				/*If reference mode is direct, it means that the normal index is the same as a vertex index.*/
				if (normalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
				{
					normalIndex = vertexIndex;
				}

				/*If the reference mode is Index-to-Direct, it means that the normals are obtained by the Index-to-Direct.*/
				if (normalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
				{
					normalIndex = normalElement->GetIndexArray().GetAt(normalIndex);
				}

				/*Normals of each vertex is obtained.*/
				FbxVector4 normals = normalElement->GetDirectArray().GetAt(normalIndex); 

				cout << "\n" << "Normal: "<< normals.mData[0] << " " << normals.mData[1] << " " << normals.mData[2] << "\n";

				mesh.mpVertexList.at(vertexIndex).vertexNormal[0] = normals.mData[0];
				mesh.mpVertexList.at(vertexIndex).vertexNormal[1] = normals.mData[1];
				mesh.mpVertexList.at(vertexIndex).vertexNormal[2] = normals.mData[2];
			}
		}

		/*Get the normals by obtaining polygon-vertex.*/
		else if (normalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) 
		{
			int indexPolygonVertex = 0;

			/*Obtain normals of each polygon, because the mapping mode of normal element is by Polygon-Vertex.*/
			for (int polygonIndex = 0; polygonIndex < inputMesh->GetPolygonCount(); polygonIndex++)
			{
				/*Get the polygon size, to know how many vertices in current polygon.*/
				int polygonSize = inputMesh->GetPolygonSize(polygonIndex); 

				for (int i = 0; i < polygonSize; i++) //Obtain each vertex of the current polygon.
				{
					int normalIndex = 0;

					/*Reference mode is direct because the normal index is same as indexPolygonVertex.*/
					if (normalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					{
						normalIndex = indexPolygonVertex;
					}
					/*Reference mose is index-to-direct, which means getting normals by index-to-direct.*/
					if (normalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					{
						normalIndex = normalElement->GetIndexArray().GetAt(indexPolygonVertex);
					}

					FbxVector4 normals = normalElement->GetDirectArray().GetAt(normalIndex); //Obtain normals of each polygon-vertex

					cout << "\n" << "Normal: " << normals.mData[0] << " " << normals.mData[1] << " " << normals.mData[2] << "\n";

					mesh.mpVertexList.at(indexPolygonVertex).vertexNormal[0] = normals.mData[0];
					mesh.mpVertexList.at(indexPolygonVertex).vertexNormal[1] = normals.mData[1];
					mesh.mpVertexList.at(indexPolygonVertex).vertexNormal[2] = normals.mData[2];

					indexPolygonVertex++;
				}
			}
		}
	}
}

void FbxImport::processTangents(FbxMesh * inputMesh)
{
	int tangentCount = inputMesh->GetElementTangentCount();
	
	for (int i = 0; i < tangentCount; i++)
	{
		FbxGeometryElementTangent* tangentElement = inputMesh->GetElementTangent(i);
		
		if (tangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int indexPolygonVertex = 0;

			for (int polygonIndex = 0; inputMesh->GetPolygonCount(); polygonIndex++)
			{
				int polygonSize = inputMesh->GetPolygonSize(polygonIndex);

				for (int i = 0; i < polygonSize; i++)
				{
					int tangentIndex = 0;

					if (tangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					{
						tangentIndex = indexPolygonVertex;
					}

					if (tangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					{
						tangentIndex = tangentElement->GetIndexArray().GetAt(indexPolygonVertex);
					}

					FbxVector4 tangent = tangentElement->GetDirectArray().GetAt(tangentIndex);

					cout << "\n" << "Tangent Normals: " << tangent.mData[0] << " " << tangent.mData[1] << " " << tangent.mData[2] << "\n";
				}
			}

		}
	}
}

void FbxImport::processBiTangents(FbxMesh * inputMesh)
{
}

void FbxImport::processUVs(FbxMesh * inputMesh)
{
	/*A mesh can have different UV sets in Maya.*/
	FbxStringList UVSetNameList;
	inputMesh->GetUVSetNames(UVSetNameList);

	/*Looping through all the UV sets of the mesh in the scene.*/
	for (int setIndex = 0; setIndex < UVSetNameList.GetCount(); setIndex++)
	{
		/*Getting the name of each UV set so the name can be used to get
		the Element UV, which are needed to obtain the UV coordinates.*/
		const char* UVSetName = UVSetNameList.GetStringAt(setIndex);
		const FbxGeometryElementUV* UVElement = inputMesh->GetElementUV(UVSetName);

		if (!UVElement) //If the are no UV element then exit the loop. 
			continue;

		/*If the mapping modes for the UV element are not of these two modes,
		then return from the function.*/
		if (UVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
			UVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			return;

		/*The index array, which holds the index referenced to UV data.*/
		const bool useIndex = UVElement->GetReferenceMode() != FbxGeometryElement::eDirect &&
			UVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect;
		const int indexCount = (useIndex) ? UVElement->GetIndexArray().GetCount() : 0;

		const int polyCount = inputMesh->GetPolygonCount(); //Get the polygon count of mesh.

														/*If the mapping mode is "eByControlPoint".*/
		if (UVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			for (int polyIndex = 0; polyIndex < polyCount; ++polyIndex)
			{
				const int polySize = inputMesh->GetPolygonSize(polyIndex);

				for (int vertexIndex = 0; vertexIndex < polySize; ++vertexIndex)
				{
					FbxVector2 UVs;

					/*Obtain the index of a current vertex in the control points array.*/
					int polyVertexIndex = inputMesh->GetPolygonVertex(polyIndex, vertexIndex);

					/*What UV Index to be used depends on the reference mode.*/
					int UVIndex = useIndex ? UVElement->GetIndexArray().GetAt(polyVertexIndex) : polyVertexIndex;

					UVs = UVElement->GetDirectArray().GetAt(UVIndex); //Getting the UV coordinates.

					cout << "\n" << "UV: " << UVs.mData[0] << " " << UVs.mData[1] << "\n";

					mesh.mpVertexList.at(vertexIndex).vertexUV[0] = UVs.mData[0];
					mesh.mpVertexList.at(vertexIndex).vertexUV[1] = UVs.mData[1];
				}
			}
		}

		/*Otherwise the mapping mode should be "eByPolygonVertex.*/
		else if (UVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int polyIndexCount = 0;
			for (int polyIndex = 0; polyIndex < polyCount; ++polyIndex)
			{
				const int polySize = inputMesh->GetPolygonSize(polyIndex);
				for (int vertexIndex = 0; vertexIndex < polySize; ++vertexIndex)
				{
					FbxVector2 UVs;

					int UVIndex = useIndex ? UVElement->GetIndexArray().GetAt(polyIndexCount) : polyIndexCount;

					UVs = UVElement->GetDirectArray().GetAt(UVIndex);

					cout << "\n" << "UV: " << UVs.mData[0] << " " << UVs.mData[1] << "\n";

					mesh.mpVertexList.at(polyIndexCount).vertexUV[0] = UVs.mData[0];
					mesh.mpVertexList.at(polyIndexCount).vertexUV[1] = UVs.mData[1];

					polyIndexCount++;
				}
			}
		}
	}
}

void FbxImport::processLight(FbxLight * inputLight)
{
}

void FbxImport::processCamera(FbxCamera * inputCamera)
{
}

