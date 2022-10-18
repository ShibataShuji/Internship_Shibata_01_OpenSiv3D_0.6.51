#include "stdafx.h"

void Collision_Sphere::Update()
{
	// 親
	Collision::Update();


}

void Collision_Sphere::UpdateCollisionState()
{
	// 親
	Collision::UpdateCollisionState();

	m_Sphere.setPos(m_Position);
	m_Sphere.setR(m_Size.x);
}
