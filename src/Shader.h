#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm.hpp>
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
	void setVec2(const std::string &name, glm::vec2& value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3& value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4& value) const;
	void setMat4(const std::string &name, const glm::mat4& value) const;
private:
	unsigned int ID;
	unsigned int createVertexShader(std::string vertexPath);
	unsigned int createFragmentShader(std::string fragmentPath);
	void createShaderProgram(unsigned int vertex, unsigned int fragment);
	void checkCompileErrors(unsigned int shader, std::string type);
};
