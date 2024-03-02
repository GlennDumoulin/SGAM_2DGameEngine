#include <algorithm>

#include "Scene.h"
#include "GameObject.h"

using namespace sgam;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> pObject)
{
	m_pObjects.emplace_back(std::move(pObject));
}

void Scene::Remove(std::shared_ptr<GameObject> pObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), pObject), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
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

void Scene::Cleanup()
{
	// Remove all GameObjects that were marked to be destroyed
	std::for_each(m_pObjects.begin(), m_pObjects.end(), [&](const auto& pObject)
	{
		if (pObject->IsMarkedAsDestroyed())
		{
			Remove(pObject);
		}
	});

	// Clean up all GameObjects in the scene
	for (const auto& pObject : m_pObjects)
	{
		pObject->Cleanup();
	}
}
