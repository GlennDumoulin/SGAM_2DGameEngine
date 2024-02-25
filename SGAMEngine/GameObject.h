#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Component.h"

namespace sgam
{
	class Transform;

	class GameObject final
	{
	public:
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void Destroy() { m_IsMarkedAsDestroyed = true; }
		const bool IsMarkedAsDestroyed() const { return m_IsMarkedAsDestroyed; }
		void Cleanup();

		template <class T>
		T* GetComponent() const;
		template <class T>
		std::vector<T*> GetComponents() const;
		template <class T>
		T* AddComponent();
		template <class T>
		bool RemoveComponent();
		template <class T>
		bool RemoveComponent(T* pComponent);
		template <class T>
		bool RemoveComponents();
		template <class T>
		bool HasComponent() const;
		Transform* GetTransform() const { return m_pTransform; }

		GameObject();
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<Component>> m_pComponents{};
		Transform* m_pTransform{};

		bool m_IsMarkedAsDestroyed{ false };
	};

	template <class T>
	inline T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		for (const auto& pComponent : m_pComponents)
		{
			T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

			if (pDerivedComponent) return pDerivedComponent;
		}

		return nullptr;
	}

	template <class T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		std::vector<T*> pComponents{};

		for (const auto& pComponent : m_pComponents)
		{
			T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

			if (pDerivedComponent) pComponents.push_back(pComponent);
		}

		return pComponents;
	}

	template <class T>
	inline T* GameObject::AddComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		if constexpr (std::is_same<Transform, T>())
		{
			// Check if we already have a Transform Component, if so return that one
			if (m_pTransform)
			{
				std::cout << "You tried to add a second Transform Component, which doesn't do anything.";

				return m_pTransform;
			}
		}

		// Make the Component we want to add
		auto pComponent{ std::make_unique<T>() };

		// Set the current GameObject as the owner
		pComponent->SetOwner(this);

		// Get the raw pointer to the Component
		T* pComponentPtr{ pComponent.get() };

		// Add the Component to GameObject's Components
		m_pComponents.push_back(std::move(pComponent));

		return pComponentPtr;
	}

	template <class T>
	inline bool GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");
		static_assert(!std::is_same<Transform, T>(), "You can't remove Transform component");

		const T* pComponent{ GetComponent<T>() };

		if (pComponent)
		{
			pComponent->Destroy();

			return true;
		}

		return false;
	}

	template <class T>
	inline bool GameObject::RemoveComponent(T* pComponent)
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");
		static_assert(!std::is_same<Transform, T>(), "You can't remove Transform component");

		if (pComponent && pComponent->GetOwner() == this)
		{
			pComponent->Destroy();

			return true;
		}

		return false;
	}

	template <class T>
	inline bool GameObject::RemoveComponents()
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");
		static_assert(!std::is_same<Transform, T>(), "You can't remove Transform component");

		const std::vector<T*> pComponents{ GetComponents<T>() };

		if (!pComponents.empty())
		{
			for (const auto& pComponent : pComponents)
			{
				pComponent->Destroy();
			}

			return true;
		}

		return false;
	}

	template <class T>
	inline bool GameObject::HasComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		for (const auto& pComponent : m_pComponents)
		{
			T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

			if (pDerivedComponent) return true;
		}

		return false;
	}
}
