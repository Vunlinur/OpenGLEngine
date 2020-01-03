#include "TestScene_3DCube.h"

namespace scene {

	TestScene_3DCube::TestScene_3DCube()
		: vertexBuffer(positions, sizeof(positions)), // *8 debug
		indexBuffer(indices, 36),
		shader("resources/3DCube.shader")
	{
		glEnable(GL_CULL_FACE);
		//glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		/* Vertex buffer, layout & array */
		layout.Push<float>(3); // 1st to 3rd columns of POSITIONS: vertex coords
		vertexArray.AddBuffer(vertexBuffer, layout);

		/* Shaders */
		shader.Bind();
	}


	TestScene_3DCube::~TestScene_3DCube()
	{
		shader.Unbind();
	}

	void TestScene_3DCube::OnTick(float deltaTime)
	{
		mouseScroll = ImGui::GetIO().MouseWheel;
		if (mouseScroll != 0)
		{
			glm::vec3 localTranslation = glm::vec3(0.0, 0.0, -mouseScroll * 100);
			glm::mat4 localTranslationMatrix = glm::mat4(1.f);

			localTranslationMatrix = glm::translate(localTranslationMatrix, localTranslation);
			modelMatrix = localTranslationMatrix * modelMatrix;
		}
		
		if (ImGui::GetIO().MouseDown[0])
		{
			// translate in world space
			glm::vec3 localTranslation = glm::vec3(ImGui::GetIO().MouseDelta.x * 1.5, -ImGui::GetIO().MouseDelta.y * 1.5, 0.0);
			glm::mat4 localTranslationMatrix = glm::mat4(1.f);
			
			localTranslationMatrix = glm::translate(localTranslationMatrix, localTranslation);
			modelMatrix = localTranslationMatrix * modelMatrix;
		}
		if (ImGui::GetIO().MouseDown[1])
		{
			modelMatrix = glm::rotate(modelMatrix, glm::radians(ImGui::GetIO().MouseDelta.x), glm::vec3(0.0, 1.0, 0.0));
			auto rot = glm::rotate(glm::mat4(1.f), glm::radians(ImGui::GetIO().MouseDelta.y), glm::vec3(1.0, 0.0, 0.0));
			modelMatrix = modelMatrix * rot;
		}
	}

	void TestScene_3DCube::OnRender()
	{
		/* Shader Uniforms */
		mvp = projectionMatrix * viewMatrix * modelMatrix;
		shader.SetUniformMat4f("u_ModelViewProjectionMatrix", mvp);

		renderer.Draw(vertexArray, indexBuffer, shader);
	}

	void TestScene_3DCube::OnImGuiRender()
	{
	}
}