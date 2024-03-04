#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "FunctionalComponent.h"
#include "RenderableComponent.h"
#include "Transform.h"

namespace sgam
{
	class Scene;

	class GameObject final
	{
	public:
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void Destroy() { m_IsMarkedAsDestroyed = true; }
		bool IsMarkedAsDestroyed() const { return m_IsMarkedAsDestroyed; }
		void Cleanup();

		void SetEnabled(bool isEnabled) { m_IsEnabled = isEnabled; }
		bool IsEnabled() const { return m_IsEnabled; }

		const std::string& GetName() const { return m_Name; }

		Scene* GetScene() const { return m_pScene; }

		void SetParent(GameObject* pParent, const bool keepWorldPosition = true);
		GameObject* GetParent() const { return m_pParent; }
		GameObject* GetChildAt(const unsigned int index) const;
		size_t GetChildCount() const { return m_pChildren.size(); }

		GameObject* CreateGameObject(const std::string& name = "");

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
		Transform* GetTransform() const { return m_pTransform.get(); }

		explicit GameObject(Scene* pScene, const std::string& name = "", GameObject* pParent = nullptr);
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool IsChild(GameObject* pObject) const;

		void AddChild(std::unique_ptr<GameObject> pChild);
		std::unique_ptr<GameObject> RemoveChildAt(const unsigned int index);

		Scene* m_pScene{};

		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};

		std::vector<std::unique_ptr<FunctionalComponent>> m_pFunctionalComponents{};
		std::vector<std::unique_ptr<RenderableComponent>> m_pRenderableComponents{};
		std::unique_ptr<Transform> m_pTransform{};

		bool m_IsMarkedAsDestroyed{ false };
		bool m_IsEnabled{ true };

		std::string m_Name{};
	};

	template <class T>
	inline T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		// Check if we are getting the transform
		if constexpr (std::is_same<Transform, T>()) return GetTransform();

		if constexpr (std::is_base_of<FunctionalComponent, T>())
		{
			for (const auto& pComponent : m_pFunctionalComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) return pDerivedComponent;
			}
		}
		else if constexpr (std::is_base_of<RenderableComponent, T>())
		{
			for (const auto& pComponent : m_pRenderableComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) return pDerivedComponent;
			}
		}

		return nullptr;
	}

	template <class T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");

		std::vector<T*> pComponents{};

		// Check if we are getting the transform(s?)
		if constexpr (std::is_same<Transform, T>()) return pComponents.push_back(GetTransform());

		if constexpr (std::is_base_of<FunctionalComponent, T>())
		{
			for (const auto& pComponent : m_pFunctionalComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) pComponents.push_back(pDerivedComponent);
			}
		}
		else if constexpr (std::is_base_of<RenderableComponent, T>())
		{
			for (const auto& pComponent : m_pRenderableComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) pComponents.push_back(pDerivedComponent);
			}
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
				std::cout << "You tried to add a second Transform Component, which doesn't do anything.\n";

				return GetTransform();
			}
		}

		// Make the Component we want to add
		// Set the current GameObject as the owner
		auto pComponent{ std::make_unique<T>(this) };

		// Get the raw pointer to the Component
		T* pComponentPtr{ pComponent.get() };

		// Add the Component to GameObject's Components
		if constexpr (std::is_base_of<FunctionalComponent, T>())
		{
			m_pFunctionalComponents.push_back(std::move(pComponent));
		}
		else if constexpr (std::is_base_of<RenderableComponent, T>())
		{
			m_pRenderableComponents.push_back(std::move(pComponent));
		}
		else if constexpr (std::is_same<Transform, T>())
		{
			m_pTransform = std::move(pComponent);
		}

		return pComponentPtr;
	}

	template <class T>
	inline bool GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T does not derive from Component class");
		static_assert(!std::is_same<Transform, T>(), "You can't remove Transform component");

		T* pComponent{ GetComponent<T>() };

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

		if constexpr (std::is_same<Transform, T>()) return m_pTransform;

		if constexpr (std::is_base_of<FunctionalComponent, T>())
		{
			for (const auto& pComponent : m_pFunctionalComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) return true;
			}
		}
		else if constexpr (std::is_base_of<RenderableComponent, T>())
		{
			for (const auto& pComponent : m_pRenderableComponents)
			{
				T* pDerivedComponent{ dynamic_cast<T*>(pComponent.get()) };

				if (pDerivedComponent) return true;
			}
		}

		return false;
	}
}
