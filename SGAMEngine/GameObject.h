#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Transform.h"

namespace sgam
{
	class BaseComponent;
	class Texture2D;

	class GameObject final
	{
	public:
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);
		void RemoveAllComponents();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void Destroy();
		bool IsDestroyed() const;
		void Cleanup();

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};

		bool m_IsDestroyed{ false };

		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}
