#include "Transform.h"

using namespace sgam;

void Transform::SetPosition(const float x, const float y, const float z)
{
	// Don't update if nothing changed
	if (x == m_position.x && y == m_position.y && z == m_position.z) return;

	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
