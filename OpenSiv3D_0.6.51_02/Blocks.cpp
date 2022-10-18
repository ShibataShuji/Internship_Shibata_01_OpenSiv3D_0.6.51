#include "stdafx.h"


void Blocks::Init()
{
	// このオブジェクトの名前
	m_Name = U"Blocks";

	auto col = AddComponent<Collision_Box>();
	col->SetResponseObject(ResponseObject::BlocksPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Block);
	col->SetOffsetSize(Vec3(5, 5, 5));
	// テスト用にItemにしてオーバーラップするところ見せてるよ。後で消してね
	col->SetResponseObject(ResponseObject::ItemsPawn);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);


}


void Blocks::Uninit()
{

}


void Blocks::Update()
{
	GameObject::Update();		// 最初に持ってくる

	GameObject::ComponentUpdate();		// 最後に持ってくる
}


void Blocks::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}
