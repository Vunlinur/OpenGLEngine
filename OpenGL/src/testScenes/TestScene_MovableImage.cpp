#include "TestScene_MovableImage.h"

namespace scene {

	TestScene_MovableImage::TestScene_MovableImage()
		: vertexBuffer(positions, sizeof(positions)),
		indexBuffer(indices, 6),
		shader("resources/Texture.shader"),
		texture("resources/dragonAlpha.png")
	{
		/* Vertex buffer, layout & array */
		layout.Push<float>(2); // 1st and 2nd columns of POSITIONS: vertex coords
		layout.Push<float>(2); // 3rd and 4th columns of POSITIONS: texture coords

		vertexArray.AddBuffer(vertexBuffer, layout);

		/* Shaders */
		shader.Bind();
		texture.Bind(textureSlot);
		shader.SetUniform1i("u_Texture", textureSlot);
	}


	TestScene_MovableImage::~TestScene_MovableImage()
	{
		shader.Unbind();
	}

	void TestScene_MovableImage::OnTick(float deltaTime)
	{
	}

	void TestScene_MovableImage::OnRender()
	{
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), viewTranslation);
		mvp = projectionMatrix * viewMatrix * modelMatrix;

		/* Shader Uniforms */
		shader.SetUniformMat4f("u_ModelViewProjectionMatrix", mvp);

		renderer.Draw(vertexArray, indexBuffer, shader);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void TestScene_MovableImage::OnImGuiRender()
	{
		ImGui::SliderFloat2("Translation", &viewTranslation.x, 0.0f, 1080.0f);            // Edit 2 floats starting from memory address of viewTranslation.x
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}