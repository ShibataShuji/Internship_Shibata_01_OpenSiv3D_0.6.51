#include "stdafx.h"


void KnifeBlock::Init()
{
	// このオブジェクトの名前
	m_Name = U"KnifeBlock";

	/*auto col = AddComponent<Collision_Box>();
	col->SetResponseObject(ResponseObject::BlocksPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	col->SetOffsetSize(Vec3(5, 5, 5));*/

	auto col = AddComponent<Collision_Sphere>();
	col->SetResponseObject(ResponseObject::ItemsPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	col->SetOffsetSize(5.0f);
}


void KnifeBlock::Uninit()
{

}


void KnifeBlock::Update()
{
	GameObject::Update();		// 最初に持ってくる

	AddPosition(GetVelocity());

	GameObject::ComponentUpdate();		// 最後に持ってくる
}


void KnifeBlock::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

}
