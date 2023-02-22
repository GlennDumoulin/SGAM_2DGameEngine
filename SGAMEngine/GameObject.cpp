#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

sgam::GameObject::~GameObject() = default;

void sgam::GameObject::Update(){}

void sgam::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void sgam::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void sgam::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
