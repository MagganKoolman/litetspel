#include "DeferredProgram.h"

DeferredProgram::DeferredProgram() {

}

DeferredProgram::DeferredProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath): ShaderProgram() {
	compileShaders(vertexPath, fragmentPath, geometryPath);

	//Initializing framebuffer
	glGenFramebuffers(1, &mFBOid);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBOid);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &mAmbientTex);
	glBindTexture(GL_TEXTURE_2D, mAmbientTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1080, 720, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &mNormalTex);
	glBindTexture(GL_TEXTURE_2D, mNormalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1080, 720, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &mSpecularTex);
	glBindTexture(GL_TEXTURE_2D, mSpecularTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &mDiffuseTex);
	glBindTexture(GL_TEXTURE_2D, mDiffuseTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &mDepthTex);
	glBindTexture(GL_TEXTURE_2D, mDepthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1080, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mAmbientTex, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, mNormalTex, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, mSpecularTex, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, mDiffuseTex, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthTex, 0);

	GLenum DrawBuffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "No framebuffer!!!!";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

DeferredProgram::~DeferredProgram() {
	glDeleteTextures(1, &mAmbientTex);
	glDeleteTextures(1, &mNormalTex);
	glDeleteTextures(1, &mSpecularTex);
	glDeleteTextures(1, &mDiffuseTex);
	glDeleteTextures(1, &mDepthTex);
	glDeleteFramebuffers(1, &mFBOid);
}

void DeferredProgram::use() {
	glUseProgram(mProgramID);
	for (int i = 0; i < mTotalAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, mFBOid);
	glViewport(0, 0, 1080, 720);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeferredProgram::unUse() {
	glUseProgram(0);
	for (int i = 0; i < mTotalAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
