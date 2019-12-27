#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // v-sync

	if (glewInit() == GLEW_OK)
		std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << " initialized." << std::endl;
	else
		std::cout << "[ERROR] GLEW init failed!" << std::endl;

	float positions[] = {
		-1.0, -1.0, 0.0, 0.0,//0
		 1.0, -1.0, 1.0, 0.0,//1
		 1.0,  1.0, 1.0, 1.0,//2
		-1.0,  1.0, 0.0, 1.0//3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	VertexBuffer vertexBuffer(positions, sizeof(positions)*8); // *8 for debug
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);
	IndexBuffer indexBuffer(indices, 6);
	
	Shader shader("resources/Shader.shader");
	shader.Bind();
	float time = 0.0; // Uniform

	Texture texture("resources/dragonAlpha.png");
	int textureSlot = 0;
	texture.Bind(textureSlot);
	shader.SetUniform1i("u_Texture", textureSlot);

	Renderer renderer;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		glCall(shader.SetUnifrom1f("u_Time", time));

		renderer.Draw(vertexArray, indexBuffer, shader);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		time = time + (float)0.01;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	
	shader.Unbind();
	glfwTerminate();
	return 0;
}