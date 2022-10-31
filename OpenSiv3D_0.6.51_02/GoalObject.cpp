#include "stdafx.h"

void GoalObject::Init()
{
	// このオブジェクトの名前
	m_Name = U"GoalObject";

	auto col = AddComponent<Collision_Sphere>(U"GoalObject");
	col->SetResponseObject(ResponseObject::ItemsPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(GoalRadius);
	col->SetCollisionColor(MidColor);

	// ゴールは最初から回転を持っている。
	SetRotationSpeed(Vec3(0.05, 0.0, 0.0));

}


void GoalObject::Uninit()
{
	GameObject::Uninit();
}


void GoalObject::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void GoalObject::Draw()
{
	double height = 8.0;
	double headlength = 7.0;
	double cylindersize = 0.3;
	double headradius = 1.2;


	Vec3 from = m_Position;
	Vec3 to = from;
	to.y += height;

	const double theta = (m_Time * 10_deg);
	const Vec2 offset = OffsetCircular{ Vec2(0,0), headlength, theta};

	Vec3 headPos = to;
	headPos.x += offset.x;
	headPos.z += offset.y;

	Cylinder{ from, to, cylindersize }.draw(Linear::Palette::Black);

	ColorF conecolor = MidColor;
	if (m_itGoal)
		conecolor = GoalColor;
	else
		conecolor = MidColor;

	Cone{ to, headPos, headradius }.draw(conecolor);

	m_Time += Scene::DeltaTime();

	GameObject::Draw();	// 最初に持ってくる
}
