#include "TestScene_LiveShader.h"

namespace scene {

	TestScene_LiveShader::TestScene_LiveShader()
		: vertexBuffer(positions, sizeof(positions)),
		indexBuffer(indices, 6),
		shader("resources/Live.shader")
	{
		/* Vertex buffer, layout & array */
		layout.Push<float>(2); // 1st and 2nd columns of POSITIONS: vertex coords

		vertexArray.AddBuffer(vertexBuffer, layout);

		/* Shaders */
		shader.Bind();
	}


	TestScene_LiveShader::~TestScene_LiveShader()
	{
		shader.Unbind();
	}

	void TestScene_LiveShader::OnTick(float deltaTime)
	{
	}

	void TestScene_LiveShader::OnRender()
	{
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation);
		mvp = projectionMatrix * viewMatrix * modelMatrix;
		time = time + (float)0.01;

		/* Shader Uniforms */
		shader.SetUniformMat4f("u_ModelViewProjectionMatrix", mvp);
		shader.SetUniform1f("u_Time", time);
		shader.SetUniform1f("u_Power", shaderPower);
		shader.SetUniform1f("u_Divider", shaderDivider);

		renderer.Draw(vertexArray, indexBuffer, shader);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void TestScene_LiveShader::OnImGuiRender()
	{
		ImGui::SliderFloat("Power", &shaderPower, 0.5f, 4.0f);
		ImGui::SliderFloat("Divider", &shaderDivider, 20.0f, 220.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}