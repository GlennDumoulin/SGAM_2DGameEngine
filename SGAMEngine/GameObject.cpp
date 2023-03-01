#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace sgam
{
	GameObject::~GameObject() = default;

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_Components.emplace_back(std::move(component));
	}
	void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
	{
		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
	}
	void GameObject::RemoveAllComponents()
	{
		m_Components.clear();
	}

	void GameObject::FixedUpdate()
	{
		for (auto& component : m_Components)
		{
			component->FixedUpdate();
		}
	}
	void GameObject::Update()
	{
		for (auto& component : m_Components)
		{
			component->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (auto& component : m_Components)
		{
			component->LateUpdate();
		}
	}

	void GameObject::Render() const
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

		for (auto& component : m_Components)
		{
			component->Render();
		}
	}

	void GameObject::Destroy()
	{
		m_IsDestroyed = true;
	}
	bool GameObject::IsDestroyed() const
	{
		return m_IsDestroyed;
	}
	void GameObject::Cleanup()
	{
		for (auto& component : m_Components)
		{
			if (component->IsDestroyed())
				RemoveComponent(component);
		}
	}

	void GameObject::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void GameObject::SetPosition(float x, float y)
	{
		m_transform.SetPosition(x, y, 0.0f);
	}
}
