#pragma once
#include <memory>

#include "imgui.h"
#include "implot.h"

namespace sgam
{
	class GameObject;
	class Transform;

	class Component
	{
	public:
		virtual void RenderGUI() const {};

		void Destroy() { m_IsMarkedAsDestroyed = true; }
		const bool IsMarkedAsDestroyed() const { return m_IsMarkedAsDestroyed; }

		void SetEnabled(bool isEnabled) { m_IsEnabled = isEnabled; }
		bool IsEnabled() const { return m_IsEnabled; }

		GameObject* GetOwner() const { return m_pOwner; }
		GameObject* GetParent() const;
		Transform* GetTransform() const;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		friend class GameObject;
		explicit Component(GameObject* pOwner) : m_pOwner{ pOwner } {}

	private:
		GameObject* m_pOwner{};

		bool m_IsMarkedAsDestroyed{ false };
		bool m_IsEnabled{ true };
	};
}
