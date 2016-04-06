#pragma once
#include <gl\glew.h>
#include <string>
#include <iostream>

using namespace std;

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void compileShaders(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);

	void use();
	void unUse();
	GLuint getProgramID() const;
private:
	GLuint programID;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader;

	int numAttributes;
	void compileShader(const std::string& filePath, GLuint shaderID);
};