#pragma once

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
#include "Scene.h"

namespace scene {

	class TestScene_LiveShader : public Scene
	{
	private:
		/* Data to render */
		float positions[16] = {
			0.0,	0.0, //0
			1920.0, 0.0, //1
			1920.0, 1080.0, //2
			0.0,	1080.0 //3
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		float time = 0;
		float shaderPower = 2;
		float shaderDivider = 80;

		VertexBuffer vertexBuffer;
		VertexBufferLayout layout;
		VertexArray vertexArray;
		IndexBuffer indexBuffer;
		Shader shader;

		Renderer renderer;

		/* Model View Projection matrices */
		glm::vec3 viewTranslation = glm::vec3(0, 0, 0);
		glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)1920, 0.0f, (float)1080);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation);
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	public:
		TestScene_LiveShader();
		~TestScene_LiveShader();

		void OnTick(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	};
}