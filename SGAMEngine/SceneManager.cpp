#include "SceneManager.h"
#include "Scene.h"

namespace sgam
{
	void SceneManager::FixedUpdate()
	{
		for (auto& scene : m_scenes)
		{
			scene->Update();//todo: Handle fixed updates
		}
	}
	void SceneManager::Update()
	{
		for (auto& scene : m_scenes)
		{
			scene->Update();
		}
	}
	void SceneManager::LateUpdate()
	{
		for (auto& scene : m_scenes)
		{
			scene->Update();//todo: Handle late updates
		}
	}

	void SceneManager::Render()
	{
		for (const auto& scene : m_scenes)
		{
			scene->Render();
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_scenes.push_back(scene);
		return *scene;
	}
}
