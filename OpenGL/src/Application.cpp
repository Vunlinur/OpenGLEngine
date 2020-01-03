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

#include "testScenes/TestScene_ClearColor.h"
#include "testScenes/TestScene_MovableImage.h"
#include "testScenes/TestScene_LiveShader.h"
#include "testScenes/TestScene_3DCube.h"

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

	Renderer renderer;

	/* ImGui */
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	scene::Scene* CurrentScene = nullptr;
	scene::SceneMenu* sceneMenu = new scene::SceneMenu(CurrentScene);
	CurrentScene = sceneMenu;

	sceneMenu->RegisterScene<scene::TestScene_ClearColor>("ClearColor");
	sceneMenu->RegisterScene<scene::TestScene_MovableImage>("MovableImage");
	sceneMenu->RegisterScene<scene::TestScene_LiveShader>("LiveShader");
	sceneMenu->RegisterScene<scene::TestScene_3DCube>("3DCube");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		/* ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (CurrentScene)
		{
			CurrentScene->OnTick(0.0f);
			CurrentScene->OnRender();
			ImGui::Begin("Scene menu");
			if (CurrentScene != sceneMenu && ImGui::Button("Back"))
			{
				delete CurrentScene;
				CurrentScene = sceneMenu;
			}
			CurrentScene->OnImGuiRender();
		}

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	delete CurrentScene;
	if (CurrentScene != sceneMenu)
		delete sceneMenu;
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}