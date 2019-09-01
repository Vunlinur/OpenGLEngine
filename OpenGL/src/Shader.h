#pragma once
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
	void SetUnifrom1f(const std::string& name, float f0);
	void SetUnifrom3f(const std::string& name, float f0, float f1, float f2);
	void SetUnifrom4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
	ShaderProgramSource ParseShader(std::string filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};