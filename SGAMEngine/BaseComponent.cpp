#include "BaseComponent.h"
#include "GameObject.h"

namespace sgam
{
	BaseComponent::~BaseComponent() = default;

	void BaseComponent::FixedUpdate()
	{
		//...
	}
	void BaseComponent::Update()
	{
		//...
	}
	void BaseComponent::LateUpdate()
	{
		//...
	}

	void BaseComponent::Render() const
	{
		//...
	}

	void BaseComponent::Destroy()
	{
		m_IsDestroyed = true;
	}
	bool BaseComponent::IsDestroyed() const
	{
		return m_IsDestroyed;
	}
}
