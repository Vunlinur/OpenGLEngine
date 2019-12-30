#pragma once

#include <functional>
#include <vector>

namespace scene {

	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {};

		virtual void OnTick(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class SceneMenu : public Scene
	{
	private:
		Scene*& m_CurrentScene; // Reference to Scene pointer
		std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes; // Lambda returning pointer to not-yet-constructed Scene
		
	public:
		SceneMenu(Scene*& CurrentScenePointer);

		void OnImGuiRender() override;

		template<typename T>
			void RegisterScene(const std::string& name)
		{
			std::cout << "Registering scene: " << name << std::endl;
			m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}