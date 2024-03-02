#include "Transform.h"

using namespace sgam;

void Transform::SetPosition(const float x, const float y, const float z)
{
	// Don't update if nothing changed
	if (x == m_Position.x && y == m_Position.y && z == m_Position.z) return;

	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
