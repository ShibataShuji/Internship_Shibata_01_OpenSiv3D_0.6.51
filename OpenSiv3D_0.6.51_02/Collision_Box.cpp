#include "stdafx.h"

void Collision_Box::Update()
{
	// 親
	Collision::Update();


}

void Collision_Box::UpdateCollisionState()
{
	// 親
	Collision::UpdateCollisionState();

	m_OrientedBox.setPos(m_Position);
	m_OrientedBox.setOrientation(GetQuaternionForRotation());
	m_OrientedBox.setSize(m_Size);
}
