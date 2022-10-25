#include "stdafx.h"


void KnifeBlock::Init()
{
	// このオブジェクトの名前
	m_Name = U"KnifeBlock";

	auto col = AddComponent<Collision_Box>();
	col->SetResponseObject(ResponseObject::BlocksPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Overlap);
	col->SetOffsetSize(Vec3(6, 0.8, 6));

	//auto col = AddComponent<Collision_Sphere>();
	//col->SetResponseObject(ResponseObject::BlocksPawn);
	//col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	//col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	//col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	//col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	//col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	//col->SetOffsetSize(5.0f);
}


void KnifeBlock::Uninit()
{

}


void KnifeBlock::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	AddPosition(GetVelocity());
	//AddRotation(GetRotationSpeed());

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void KnifeBlock::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

}
