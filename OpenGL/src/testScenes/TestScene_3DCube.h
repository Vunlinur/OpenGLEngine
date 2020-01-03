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
#include "Scene.h"

namespace scene {

	class TestScene_3DCube : public Scene
	{
	private:
		/* Data to render */

		float positions[24] = {
			// front
			-250.0, -250.0,  250.0,
			 250.0, -250.0,  250.0,
			 250.0,  250.0,  250.0,
			-250.0,  250.0,  250.0,
			// back
			-250.0, -250.0, -250.0,
			 250.0, -250.0, -250.0,
			 250.0,  250.0, -250.0,
			-250.0,  250.0, -250.0
		};

		unsigned int indices[36] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

		int textureSlot = 0;

		VertexBuffer vertexBuffer;
		VertexBufferLayout layout;
		VertexArray vertexArray;
		IndexBuffer indexBuffer;
		Shader shader;

		Renderer renderer;

		/* Model View Projection matrices */
		int mouseScroll;

		//glm::mat4 projectionMatrix = glm::ortho(-1920.f / 2, 1920.f/2, -1080.f/2, 1080.f/2, 0.1f, 10000.f);
		glm::mat4 projectionMatrix = glm::perspective(70.0, 1920.0/1080.0, 0.1, 10000.0); // why the hell 75 degree fov fucks up?
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1920/2, -1080/2, -1800));
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	public:
		TestScene_3DCube();
		~TestScene_3DCube();

		void OnTick(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}