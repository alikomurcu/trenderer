#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	unsigned int ID;
	unsigned int createVertexShader(std::string vertexPath);
	unsigned int createFragmentShader(std::string fragmentPath);
	void createShaderProgram(unsigned int vertex, unsigned int fragment);
	void checkCompileErrors(unsigned int shader, std::string type);
};
