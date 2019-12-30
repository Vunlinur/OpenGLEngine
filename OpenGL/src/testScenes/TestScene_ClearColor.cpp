#include "TestScene_ClearColor.h"

namespace scene {

	TestScene_ClearColor::TestScene_ClearColor()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}


	TestScene_ClearColor::~TestScene_ClearColor()
	{
	}

	void TestScene_ClearColor::OnTick(float deltaTime)
	{
	}

	void TestScene_ClearColor::OnRender()
	{
		glCall( glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]) );
		glCall( glClear(GL_COLOR_BUFFER_BIT) );
	}

	void TestScene_ClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear color", m_ClearColor);
	}
}