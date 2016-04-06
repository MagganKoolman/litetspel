#include "ShaderProgram.h"
#include <fstream>

ShaderProgram::ShaderProgram(): programID(0), vertexShader(0), fragmentShader(0), numAttributes(0), geometryShader(0) {

}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::compileShaders(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
	programID = glCreateProgram();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) 
		std::cout << "Vertex shader problem";
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) 
		std::cout << "Fragment shader problem!";
	
	compileShader(vertexPath, vertexShader);
	if (geometryPath != " ")
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		if (geometryShader == 0) {
			std::cout << "Geometry shader problem!";
		}
		compileShader(geometryPath, geometryShader);
	}
	compileShader(fragmentPath, fragmentShader);
}

void ShaderProgram::compileShader(const std::string& filePath, GLuint shaderID) {
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail()) {
		std::cout << "Fil fel: " + filePath;
	}
	std::string fileContent = "";
	std::string line;

	while (std::getline(shaderFile, line)) {
		fileContent += line + "\n";
	}
	shaderFile.close();

	const char* contentsPtr = fileContent.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		cout << "Kompileringsfel: " << filePath << endl;
	}
}

void ShaderProgram::linkShaders() {
	glAttachShader(programID, vertexShader);
	if (geometryShader != 0)
		glAttachShader(programID, geometryShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	GLint success = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&success);
	if (success == GL_FALSE) {
		cout << "Linknings fel i shaders " << endl;
	}
	glDetachShader(programID, vertexShader);
	if (geometryShader != 0) {
		glDetachShader(programID, geometryShader);
		glDeleteShader(geometryShader);
	}
	glDetachShader(programID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderProgram::getProgramID() const {
	return programID;
}