#include "stdafx.h"


void KnifeBullet::Init()
{
	// このオブジェクトの名前
	m_Name = U"KnifeBullet";

	auto col = AddComponent<Collision_Sphere>();
	col->SetResponseObject(ResponseObject::PlayerBullet);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(0.3f);
	col->SetHittoStop(true);	// 壁ずりしない設定にする
}


void KnifeBullet::Uninit()
{

}


void KnifeBullet::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	// Hitしたもののリストでいろいろするとこ
	for (auto hitobj : m_Collision_HitObjectList)
	{
		SetVelocity(Vec3(0, 0, 0));
	}
	//// Overlapしたリストでいろいろするとこ
	//for (auto oberlapobj : m_Collision_OverlapObjectList)
	//{

	//}
	//// 何かにオーバーラップしているのであれば
	//if (!m_Collision_OverlapObjectList.empty())
	//{

	//}

	//// 弾を出す処理
	//if (MouseL.down())
	//{
	//	GameData* gamedata = ManagerManager::GetGameData();
	//	KnifeBlock* p_KnifeBlock = gamedata->GameObjectListData.AddGameObject<KnifeBlock>();
	//	Vec3 LaunchPosition = m_Position + (Forward * 10.0);
	//	p_KnifeBlock->SetPosition(LaunchPosition);
	//	p_KnifeBlock->SetVelocity(Forward * 4.0);
	//	//p_KnifeBlock->SetScaleRate(Vec3(4, 0.5, 8));
	//}



	AddPosition(GetVelocity());

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void KnifeBullet::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

}
