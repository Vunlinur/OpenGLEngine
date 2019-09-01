#include "renderer.h"
#include <iostream>

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) //wrap a function in it to assert and print errors
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error " << error << "]: " << function << " " << file << ":" << line;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}