#pragma once
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;	//debug
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int i0);

	void SetUniform1f(const std::string& name, float f0);
	void SetUniform2f(const std::string & name, float f0, float f1);
	void SetUniform3f(const std::string& name, float f0, float f1, float f2);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	ShaderProgramSource ParseShader(std::string filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};