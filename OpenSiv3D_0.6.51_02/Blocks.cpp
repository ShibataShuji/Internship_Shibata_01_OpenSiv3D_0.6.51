#include "stdafx.h"

//static const ColorF Blocks_DefColor = ColorF(0.326, 0.029, 0.029, 1.0);
//static const ColorF Blocks_DefColor = ColorF(0.246, 0.023, 0.073, 1.0);
static const ColorF Blocks_DefColor = Linear::Palette::Brown; //ColorF(0.376, 0.023,0.023,1.0)

void Blocks::Init()
{
	// このオブジェクトの名前
	m_Name = U"Blocks";

	auto col = AddComponent<Collision_Box>();
	col->SetResponseObject(ResponseObject::BlocksPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Overlap);
	col->SetOffsetSize(Vec3(1, 1, 1));
	col->SetCollisionColor(Blocks_DefColor);


}


void Blocks::Uninit()
{
	GameObject::Uninit();
}


void Blocks::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	AddPosition(GetVelocity());

	MoveingObjectUpdate();

	AddRotation(GetRotationSpeed());

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void Blocks::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}
