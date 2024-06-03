#include "SceneManager.h"
#include "Scene.h"

using namespace sgam;

Scene* SceneManager::CreateScene(const std::function<void(Scene*)>& sceneLoader, const std::string& name)
{
	// Make new Scene
	// Set the Scene's loader (required) & name (optional)
	auto pScene{ std::unique_ptr<Scene, SceneDeleter>(new Scene(sceneLoader, name)) };

	// Get raw pointer to the Scene
	Scene* pScenePtr{ pScene.get() };

	// Add Scene to list of scenes
	m_pScenes.push_back(std::move(pScene));

	return pScenePtr;
}

bool SceneManager::SetNextScene(const std::string& sceneName)
{
	for (const auto& pScene : m_pScenes)
	{
		if (pScene->GetName() == sceneName)
		{
			m_pNextScene = pScene.get();
			return true;
		}
	}

	return false;
}

void SceneManager::LoadNextScene()
{
	// Check if we need to load a new scene
	// If next scene is same as active scene, reload it
	if (!m_pNextScene) return;

	// Unload the active scene, if there was one
	if (m_pActiveScene) m_pActiveScene->RemoveAll();

	// Set and Load next scene
	m_pActiveScene = m_pNextScene;
	m_pActiveScene->Load();

	// Clear next scene
	m_pNextScene = nullptr;
}

void SceneManager::FixedUpdate()
{
	m_pActiveScene->FixedUpdate();
}
void SceneManager::Update()
{
	m_pActiveScene->Update();
}
void SceneManager::LateUpdate()
{
	m_pActiveScene->LateUpdate();
}

void SceneManager::Render() const
{
	m_pActiveScene->Render();
}

void SceneManager::RenderGUI()
{
	m_pActiveScene->RenderGUI();
}

void SceneManager::Cleanup()
{
	m_pActiveScene->Cleanup();
}
