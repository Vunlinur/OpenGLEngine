#pragma once
#include "scene.h"

namespace scene {

	class TestScene_ClearColor : public scene
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