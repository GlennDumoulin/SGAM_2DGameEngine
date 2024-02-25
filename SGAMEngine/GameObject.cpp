#include <string>
#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

using namespace sgam;

GameObject::GameObject()
{
	m_pTransform = AddComponent<Transform>();
}

void GameObject::FixedUpdate()
{
	for (const auto& pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (const auto& pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void GameObject::LateUpdate()
{
	for (const auto& pComponent : m_pComponents)
	{
		pComponent->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (const auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void GameObject::Cleanup()
{
	// Remove all Components that were marked to be destroyed
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](const auto& pComponent)
	{
		if (pComponent->IsMarkedAsDestroyed())
		{
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent), m_pComponents.end());
		}
	});
}
