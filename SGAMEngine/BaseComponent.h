#pragma once
#include <memory>

namespace sgam
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render() const;

		void Destroy();
		bool IsDestroyed() const;

	private:
		//std::weak_ptr<GameObject> m_Parent;

		bool m_IsDestroyed{ false };
	};
}
