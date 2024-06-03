#include <algorithm>

#include "Scene.h"

using namespace sgam;

Scene::~Scene()
{
	RemoveAll();
}

GameObject* Scene::CreateGameObject(const std::string& name)
{
	// Make new GameObject
	// Set the GameObject's Scene & name (optional)
	auto pObject{ std::make_unique<GameObject>(this, name) };

	// Get raw pointer to the GameObject
	GameObject* pObjectPtr{ pObject.get() };

	// Add GameObject to Scene
	Add(std::move(pObject));

	// Return raw pointer
	return pObjectPtr;
}

void Scene::Add(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.push_back(std::move(pObject));
}

std::unique_ptr<GameObject> Scene::Remove(GameObject* pObject)
{
	const size_t objectsCount{ m_pObjects.size() };
	for (size_t idx{ 0 }; idx < objectsCount; ++idx)
	{
		// Check if this is the object we want to remove
		if (m_pObjects.at(idx).get() == pObject)
		{
			// Get the unique pointer 
			std::unique_ptr<GameObject> pUniqueObject{ std::move(m_pObjects.at(idx)) };

			// Remove the dangling pointer from the list
			m_pObjects.erase(m_pObjects.begin() + idx);

			return pUniqueObject;
		}
	}

	return nullptr;
}

bool Scene::Load()
{
	if (!m_pObjects.empty())
	{
		std::cout << "Scene was already loaded!\n";
		return false;
	}

	// Execute the load function
	m_SceneLoader(this);

	return true;
}

void Scene::FixedUpdate()
{
	for (auto& pObject : m_pObjects)
	{
		if (pObject->IsEnabled()) pObject->FixedUpdate();
	}
}

void Scene::Update()
{
	for(auto& pObject : m_pObjects)
	{
		if (pObject->IsEnabled()) pObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (auto& pObject : m_pObjects)
	{
		if (pObject->IsEnabled()) pObject->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		if (pObject->IsEnabled()) pObject->Render();
	}
}

void Scene::RenderGUI()
{
	for (const auto& pObject : m_pObjects)
	{
		if (pObject->IsEnabled()) pObject->RenderGUI();
	}
}

void Scene::Cleanup()
{
	// Remove all GameObjects that were marked to be destroyed
	m_pObjects.erase(
		std::remove_if(
			m_pObjects.begin(), m_pObjects.end(),
			[](const auto& pObject) { return pObject->IsMarkedAsDestroyed(); }
		)
		, m_pObjects.end()
	);

	// Clean up all GameObjects in the scene
	for (const auto& pObject : m_pObjects)
	{
		pObject->Cleanup();
	}
}
