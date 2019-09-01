#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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

	const int floatpos = 6;
	float positions[] = {
		-1.0, -1.0, //0
		 1.0, -1.0, //1
		 1.0,  1.0, //2
		-1.0,  1.0  //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	VertexBuffer vertexBuffer(positions, sizeof(positions) * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);
	IndexBuffer indexBuffer(indices, 6);
	
	Shader shader("src/Shader.shader");
	shader.Bind();
	
	float time = 0.0; // Uniform

	//va.Unbind();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		glCall(shader.SetUnifrom1f("u_Time", time));

		vertexArray.Bind();
		indexBuffer.Bind();
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