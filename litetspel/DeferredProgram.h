#pragma once
#include "ShaderProgram.h"

class DeferredProgram : public ShaderProgram {
public:
	DeferredProgram();
	DeferredProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
	~DeferredProgram();

	void use();
	void unUse();
private:
	GLuint mFBOid;
	GLuint mNormalTex;
	GLuint mDiffuseTex;
	GLuint mAmbientTex;
	GLuint mSpecularTex;
	GLuint mDepthTex;
};
