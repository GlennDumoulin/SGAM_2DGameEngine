#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace sgam
{
	GameObject::~GameObject() = default;

	void GameObject::FixedUpdate()
	{
		//...
	}
	void GameObject::Update()
	{
		//...
	}
	void GameObject::LateUpdate()
	{
		//...
	}

	void GameObject::Render() const
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	void GameObject::Destroy()
	{
		m_IsDestroyed = true;
	}
	bool GameObject::IsDestroyed() const
	{
		return m_IsDestroyed;
	}
	void GameObject::Cleanup()
	{
		//todo: cleanup destroyed components
	}

	void GameObject::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void GameObject::SetPosition(float x, float y)
	{
		m_transform.SetPosition(x, y, 0.0f);
	}
}
