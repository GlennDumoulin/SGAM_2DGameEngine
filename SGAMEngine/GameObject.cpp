#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace sgam;

GameObject::~GameObject() = default;

void GameObject::FixedUpdate(){}
void GameObject::Update(){}
void GameObject::LateUpdate(){}

void GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void GameObject::Destroy()
{
	// Mark the GameObject to be destroyed
	m_IsMarkedAsDestroyed = true;
}

void GameObject::Cleanup()
{
	// Remove all Components that were marked to be destroyed
	//...
}

void GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
