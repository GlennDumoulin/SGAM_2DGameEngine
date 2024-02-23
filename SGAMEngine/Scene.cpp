#include <algorithm>

#include "Scene.h"
#include "GameObject.h"

using namespace sgam;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

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
		pObject->FixedUpdate();
	}
}
void Scene::Update()
{
	for(auto& pObject : m_pObjects)
	{
		pObject->Update();
	}
}
void Scene::LateUpdate()
{
	for (auto& pObject : m_pObjects)
	{
		pObject->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Render();
	}
}

