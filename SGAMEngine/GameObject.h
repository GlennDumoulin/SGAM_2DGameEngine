#pragma once
#include <memory>

#include "Transform.h"

namespace sgam
{
	class Texture2D;

	// todo: this should become final.
	class GameObject 
	{
	public:
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render() const;

		virtual void Destroy();
		virtual const bool IsMarkedAsDestroyed() const { return m_IsMarkedAsDestroyed; }
		virtual void Cleanup();

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};

		bool m_IsMarkedAsDestroyed{ false };

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
