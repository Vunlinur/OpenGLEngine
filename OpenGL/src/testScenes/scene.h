#pragma once

namespace scene {

	class scene
	{
	public:
		scene() {}
		virtual ~scene() {};

		virtual void OnTick(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};
}