#include "stdafx.h"

void MidObject::Init()
{
	// このオブジェクトの名前
	m_Name = U"MidObject";

	auto col = AddComponent<Collision_Sphere>(U"MidObject");
	col->SetResponseObject(ResponseObject::ItemsPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(MidRadius);
	col->SetCollisionColor(Linear::Palette::Blue);

	// ゴールは最初から回転を持っている。
	SetRotationSpeed(Vec3(0.05, 0.0, 0.0));

}


void MidObject::Uninit()
{
	GameObject::Uninit();
}


void MidObject::Update()
{
	// 最初に持ってくる
	GameObject::Update();



	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void MidObject::Draw()
{
	double height = 8.0;
	double headlength = 7.0;
	double cylindersize = 0.3;
	double headradius = 1.2;


	Vec3 from = m_Position;
	Vec3 to = from;
	to.y += height;

	const double theta = (m_Time * 10_deg);
	const Vec2 offset = OffsetCircular{ Vec2(0,0), headlength, theta };

	Vec3 headPos = to;
	headPos.x += offset.x;
	headPos.z += offset.y;

	Cylinder{ from, to, cylindersize }.draw(Linear::Palette::Black);
	Cone{ to, headPos, headradius }.draw(Linear::Palette::Blue);

	m_Time += Scene::DeltaTime();

	GameObject::Draw();	// 最初に持ってくる



}
