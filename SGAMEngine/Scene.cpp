#include "Scene.h"
#include "GameObject.h"

namespace sgam
{
	unsigned int Scene::m_idCounter = 0;

	Scene::Scene(const std::string& name) : m_name(name) {}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameObject> object)
	{
		m_objects.emplace_back(std::move(object));
	}
	void Scene::Remove(std::shared_ptr<GameObject> object)
	{
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
	}
	void Scene::RemoveAll()
	{
		m_objects.clear();
	}

	void Scene::FixedUpdate()
	{
		for (auto& object : m_objects)
		{
			object->FixedUpdate();
		}
	}
	void Scene::Update()
	{
		for (auto& object : m_objects)
		{
			object->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (auto& object : m_objects)
		{
			object->LateUpdate();
		}
	}

	void Scene::Render() const
	{
		for (const auto& object : m_objects)
		{
			object->Render();
		}
	}

	void Scene::Cleanup()
	{
		for (const auto& object : m_objects)
		{
			if (object->IsDestroyed())
			{
				//Remove destroyed object
				object->RemoveAllComponents();
				Remove(object);
			}
			else
			{
				//Cleanup object
				object->Cleanup();
			}
		}
	}
}
