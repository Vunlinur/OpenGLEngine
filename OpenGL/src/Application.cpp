#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
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

	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	int resolutionX = 1920, resolutionY = 1080;
	window = glfwCreateWindow(resolutionX, resolutionY, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // v-sync
	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	if (glewInit() == GLEW_OK)
		std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << " initialized." << std::endl;
	else
		std::cout << "[ERROR] GLEW init failed!" << std::endl;

	/* Data to render */
	float positions[] = {
		0.0, 0.0, 0.0, 0.0,//0
		500, 0.0, 1.0, 0.0,//1
		500, 500, 1.0, 1.0,//2
		0.0, 500, 0.0, 1.0//3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	/* Vertex buffer & Layout */
	VertexBuffer vertexBuffer(positions, sizeof(positions));
	VertexBufferLayout layout;
	layout.Push<float>(2); // 1st and 2nd columns of POSITIONS: vertex coords
	layout.Push<float>(2); // 3rd and 4th columns of POSITIONS: texture coords

	/* Vertex array */
	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);
	IndexBuffer indexBuffer(indices, 6);

	/* Model View Projection matrices */
	glm::vec3 viewTranslation = glm::vec3(500, 250, 0);
	glm::mat4 projectionMatrix = glm::ortho( 0.0f, (float)resolutionX, 0.0f, (float)resolutionY);
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation);
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	
	/* Shaders */
	Shader shader("resources/Shader.shader");
	shader.Bind();
	float time = 0.0; // Uniform

	Texture texture("resources/dragonAlpha.png");
	int textureSlot = 0;
	texture.Bind(textureSlot);
	shader.SetUniform1i("u_Texture", textureSlot);

	Renderer renderer;

	/* ImGui */
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation);
		mvp = projectionMatrix * viewMatrix * modelMatrix;

		/* Shader Uniforms */
		shader.SetUniformMat4f("u_ModelViewProjectionMatrix", mvp);
		shader.SetUniform1f("u_Time", time);
		time = time + (float)0.01;

		/* Render here */
		renderer.Clear();

		renderer.Draw(vertexArray, indexBuffer, shader);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		/* ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SliderFloat2("Translation", &viewTranslation.x, 0.0f, (float)resolutionX);            // Edit 2 floats starting from memory address of viewTranslation.x
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	shader.Unbind();
	glfwTerminate();
	return 0;
}