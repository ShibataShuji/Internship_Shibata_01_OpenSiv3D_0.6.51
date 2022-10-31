#include "stdafx.h"

void Collision_Box::Update()
{

	// 親
	Collision::Update();


}

void Collision_Box::UpdateCollisionState()
{
	m_OldOrientedBox = m_OrientedBox;

	// 親 Oldの保存、m_Position等の更新がされる。
	Collision::UpdateCollisionState();

	m_OrientedBox.setPos(m_Position);
	m_OrientedBox.setOrientation(GetQuaternionForRotation());
	m_OrientedBox.setSize(m_Size);
}

void Collision_Box::Draw()
{
	if (!GetVisibility())
		return;

	// 親
	Collision::Draw();

	ColorF color =  GetColor();

	Vec3 Direction = TPSRay::GetRay()->getDirection();
	Vec3 Origin = TPSRay::GetRay()->getOrigin()- Direction * TPSRay::GetRadius();
	
	Ray ray{ Origin , Direction };

	Vec3 limitvec = Origin - TPSRay::GetRay()->getOrigin();

	Optional<double> intersects;
	intersects = ray.intersects(m_OrientedBox);
	if (intersects)
	{
		// 衝突していて、プレイヤーより手前なら
		if (pow(intersects.value(), 2) <= limitvec.lengthSq())
		{
			color.setA(0.3);
		}
	}

	Sphere sphere{ Origin , 1 };
	if(sphere.intersects(m_OrientedBox))
		color.setA(0.3);

	m_OrientedBox.draw(color);

	DrawHemming(&m_OrientedBox);
}

void Collision_Box::DrawHemming(const OrientedBox* orientedbox)
{
	// ふちどりの半径
	float r = 0.1f;

	// ふちどりの色
	ColorF color = ColorF{ 0.4, 0.8, 0.6, 0.7 }.removeSRGBCurve();


	// ８つの角をセット
	std::array<Vec3, 8> Corners;
	Corners = orientedbox->getCorners();

	// 8つの角の球を描写する
	for (const auto& Corner : Corners)
	{
		Sphere{ Corner,r }.draw(color);
	}

	//Corners.data()[0];

	// 線分12本の描写
	Cylinder{ Corners.data()[0], Corners.data()[1], r }.draw(color);
	Cylinder{ Corners.data()[0], Corners.data()[2], r }.draw(color);
	Cylinder{ Corners.data()[1], Corners.data()[3], r }.draw(color);
	Cylinder{ Corners.data()[2], Corners.data()[3], r }.draw(color);

	Cylinder{ Corners.data()[4], Corners.data()[5], r }.draw(color);
	Cylinder{ Corners.data()[4], Corners.data()[6], r }.draw(color);
	Cylinder{ Corners.data()[5], Corners.data()[7], r }.draw(color);
	Cylinder{ Corners.data()[6], Corners.data()[7], r }.draw(color);

	Cylinder{ Corners.data()[0], Corners.data()[4], r }.draw(color);
	Cylinder{ Corners.data()[1], Corners.data()[5], r }.draw(color);
	Cylinder{ Corners.data()[2], Corners.data()[6], r }.draw(color);
	Cylinder{ Corners.data()[3], Corners.data()[7], r }.draw(color);

}
