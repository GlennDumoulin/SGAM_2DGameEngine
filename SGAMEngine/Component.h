#pragma once
#include <memory>

namespace sgam
{
	class GameObject;
	class Transform;

	class Component
	{
	public:
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual void Render() const {};

		void Destroy() { m_IsMarkedAsDestroyed = true; }
		const bool IsMarkedAsDestroyed() const { return m_IsMarkedAsDestroyed; }

		GameObject* GetOwner() const { return m_pOwner; }
		Transform* GetTransform() const;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		friend class GameObject;
		Component() = default;

	private:
		void SetOwner(GameObject* pNewOwner) { m_pOwner = pNewOwner; }

		GameObject* m_pOwner{};

		bool m_IsMarkedAsDestroyed{ false };
	};
}
