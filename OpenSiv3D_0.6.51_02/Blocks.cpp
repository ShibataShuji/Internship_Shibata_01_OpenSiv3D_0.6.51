#include "stdafx.h"


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
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Overlap);
	col->SetOffsetSize(Vec3(5, 5, 5));
	//// テスト用にItemにしてオーバーラップするところ見せてるよ。後で消してね
	//col->SetResponseObject(ResponseObject::ItemsPawn);
	//col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);


}


void Blocks::Uninit()
{

}


void Blocks::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	AddPosition(GetVelocity());
	AddRotation(GetRotationSpeed());

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void Blocks::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}
