#include "imgui/imgui.h"

#include "Scene.h"

namespace scene {

	SceneMenu::SceneMenu(Scene*& CurrentScenePointer)
		: m_CurrentScene(CurrentScenePointer)
	{

	}

	void SceneMenu::OnImGuiRender()
	{
		for (auto& scene : m_Scenes)
		{
			if (ImGui::Button(scene.first.c_str()))
				m_CurrentScene = scene.second();
		}
	}
}