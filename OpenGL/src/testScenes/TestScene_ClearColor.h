#pragma once

#include "imgui/imgui.h"
#include "renderer.h"

#include "Scene.h"

namespace scene {

	class TestScene_ClearColor : public Scene
	{
	public:
		TestScene_ClearColor();
		~TestScene_ClearColor();

		void OnTick(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];
	};
}