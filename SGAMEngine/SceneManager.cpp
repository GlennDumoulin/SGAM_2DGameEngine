#include "SceneManager.h"
#include "Scene.h"

using namespace sgam;

void SceneManager::FixedUpdate()
{
	for (auto& pScene : m_pScenes)
	{
		pScene->FixedUpdate();
	}
}
void SceneManager::Update()
{
	for(auto& pScene : m_pScenes)
	{
		pScene->Update();
	}
}
void SceneManager::LateUpdate()
{
	for (auto& pScene : m_pScenes)
	{
		pScene->LateUpdate();
	}
}

void SceneManager::Render() const
{
	for (const auto& pScene : m_pScenes)
	{
		pScene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& pScene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(pScene);
	return *pScene;
}
