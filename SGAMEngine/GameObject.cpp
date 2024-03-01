#include <algorithm>

#include "GameObject.h"
#include "Transform.h"

using namespace sgam;

GameObject::GameObject()
{
	AddComponent<Transform>();
}

void GameObject::FixedUpdate()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		pComponent->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		pComponent->Update();
	}
}

void GameObject::LateUpdate()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		pComponent->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (const auto& pComponent : m_pRenderableComponents)
	{
		pComponent->Render();
	}
}

void GameObject::Cleanup()
{
	// Remove all FunctionalComponents that were marked to be destroyed
	std::for_each(m_pFunctionalComponents.begin(), m_pFunctionalComponents.end(), [&](const auto& pComponent)
	{
		if (pComponent->IsMarkedAsDestroyed())
		{
			m_pFunctionalComponents.erase(std::remove(m_pFunctionalComponents.begin(), m_pFunctionalComponents.end(), pComponent), m_pFunctionalComponents.end());
		}
	});

	// Remove all RenderComponents that were marked to be destroyed
	std::for_each(m_pRenderableComponents.begin(), m_pRenderableComponents.end(), [&](const auto& pComponent)
	{
		if (pComponent->IsMarkedAsDestroyed())
		{
			m_pRenderableComponents.erase(std::remove(m_pRenderableComponents.begin(), m_pRenderableComponents.end(), pComponent), m_pRenderableComponents.end());
		}
	});
}
