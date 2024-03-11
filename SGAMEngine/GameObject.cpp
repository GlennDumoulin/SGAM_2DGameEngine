#include <algorithm>

#include "GameObject.h"
#include "Scene.h"

using namespace sgam;

GameObject::GameObject(Scene* pScene, const std::string& name, GameObject* pParent)
	: m_pScene{ pScene }
	, m_Name{ name }
	, m_pParent{ pParent }
{
	AddComponent<Transform>();
}

void GameObject::FixedUpdate()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		if (pComponent->IsEnabled()) pComponent->FixedUpdate();
	}

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		if (pComponent->IsEnabled()) pComponent->Update();
	}

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->Update();
	}
}

void GameObject::LateUpdate()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		if (pComponent->IsEnabled()) pComponent->LateUpdate();
	}

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (const auto& pComponent : m_pRenderableComponents)
	{
		if (pComponent->IsEnabled()) pComponent->Render();
	}

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->Render();
	}
}

void GameObject::RenderGUI()
{
	for (const auto& pComponent : m_pFunctionalComponents)
	{
		if (pComponent->IsEnabled()) pComponent->RenderGUI();
	}
	for (const auto& pComponent : m_pRenderableComponents)
	{
		if (pComponent->IsEnabled()) pComponent->RenderGUI();
	}

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->RenderGUI();
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

	for (const auto& pChild : m_pChildren)
	{
		if (pChild->IsEnabled()) pChild->Cleanup();
	}
}

void GameObject::SetParent(GameObject* pParent, const bool keepWorldPosition)
{
	// Check if the new parent is different from the current parent & itself
	if (m_pParent == pParent || pParent == this) return;

	// Check if the new parent isn't one of this GameObject's children
	if (IsChild(pParent)) return;

	// Update Transform
	const auto& pTransform{ GetTransform() };

	if (keepWorldPosition)
	{
		glm::vec2 newLocalPos{ pTransform->GetWorldPosition() };
		if (pParent) newLocalPos -= pParent->GetTransform()->GetWorldPosition();

		pTransform->SetLocalPosition(newLocalPos);
	}
	pTransform->SetPositionDirty();

	// Cache the unique pointer of the current GameObject
	std::unique_ptr<GameObject> pObject{};

	if (m_pParent) // Remove itself from previous parent
	{
		const unsigned int childCount{ static_cast<unsigned int>(m_pParent->GetChildCount()) };
		for (unsigned int idx{ 0 }; idx < childCount; ++idx)
		{
			GameObject* pChild{ m_pParent->GetChildAt(idx) };

			if (pChild == this)
			{
				pObject = m_pParent->RemoveChildAt(idx);
				break;
			}
		}
	}
	else // Remove itself from the scene
	{
		pObject = m_pScene->Remove(this);
	}

	// Set the new parent
	m_pParent = pParent;

	if (m_pParent) // Add itself as child to new parent
	{
		m_pParent->AddChild(std::move(pObject));
	}
	else // Add itself to the scene
	{
		m_pScene->Add(std::move(pObject));
	}
}

bool GameObject::IsChild(GameObject* pObject) const
{
	// Check if the GameObject isn't one of this GameObject's children or their children
	for (const auto& pChild : m_pChildren)
	{
		if (pChild.get() == pObject) return true;

		if (pChild->IsChild(pObject)) return true;
	}

	return false;
}

GameObject* GameObject::GetChildAt(const unsigned int index) const
{
	if (index >= GetChildCount())
	{
		std::cout << "The child index you are trying to get is out of bounds\n";
		return nullptr;
	}

	return m_pChildren.at(index).get();
}

void GameObject::AddChild(std::unique_ptr<GameObject> pChild)
{
	m_pChildren.push_back(std::move(pChild));
}

std::unique_ptr<GameObject> GameObject::RemoveChildAt(const unsigned int index)
{
	if (index >= GetChildCount())
	{
		std::cout << "The child index you are trying to remove is out of bounds\n";
		return nullptr;
	}

	// Get the unique pointer from the GameObject we want to remove
	std::unique_ptr<GameObject> pObject{ std::move(m_pChildren.at(index)) };

	// Remove the dangling pointer from it's previous list
	m_pChildren.erase(m_pChildren.begin() + index);

	return pObject;
}

GameObject* GameObject::CreateGameObject(const std::string& name)
{
	// Make new GameObject
	// Set the new GameObject's Scene & name
	// Set current GameObject as parent
	auto pObject{ std::make_unique<GameObject>(GetScene(), name, this)};

	// Get raw pointer to the GameObject
	GameObject* pObjectPtr{ pObject.get() };

	// Add new GameObject to list of children
	m_pChildren.push_back(std::move(pObject));

	// Return raw pointer
	return pObjectPtr;
}
