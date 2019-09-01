#include "Shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& filePath)
	: m_FilePath(filePath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	glCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(std::string filePath)
{
	std::ifstream stream(filePath);

	enum ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = VERTEX;
			else
				if (line.find("fragment") != std::string::npos)
					type = FRAGMENT;
		}
		else
			ss[type] << line << "\n";
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* sourceCode = source.c_str(); // = $source[0];
	glShaderSource(id, 1, &sourceCode, nullptr);
	glCompileShader(id);

	// Error handling
	int compilationResult;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);
	if (compilationResult == GL_FALSE)
	{
		int logLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		char* message = (char*)alloca(logLength * sizeof(char));
		glGetShaderInfoLog(id, logLength, &logLength, message);
		std::cout << std::endl << message;
		free(message);
		glDeleteShader(id);
		return 0;
	}
	std::cout << "Successfully compiled " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vsh = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fsh = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	return program;
}

void Shader::Bind() const
{
	glCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	glCall(glUseProgram(0));
}

void Shader::SetUnifrom1f(const std::string& name, float f0)
{
	glCall(glUniform1f(GetUniformLocation(name), f0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	glCall(int location = glGetUniformLocation(m_RendererID, name.c_str()))
		if (location == -1)
			std::cout << "[WARNING] Uniform " << name << " does not exist!" << std::endl;
	return location;
}