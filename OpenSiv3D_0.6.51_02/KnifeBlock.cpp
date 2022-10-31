#include "stdafx.h"

void KnifeBlock::Init()
{
	// このオブジェクトの名前
	m_Name = U"KnifeBlock";

	auto col = AddComponent<Collision_Box>(U"KnifeBlockBody");
	col->SetResponseObject(ResponseObject::BlocksPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Overlap);
	col->SetOffsetSize(KnifeBlock_Size);

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

	// これを作ったものがプレイヤーだったら、プレイヤー発射球のリストから消す
	if (m_CreatedMe->GetName() == U"Player")
	{
		Player* player = static_cast<Player*>(m_CreatedMe);
		player->DeleteBullet(this);
	}

	int parentnum = GetParentNum() - 1;
	double delaytimebase = 0.1;
	double delaytime = parentnum * 0.05 + delaytimebase;

	Collision* col = GetCollisionComponent();
	Collision_Box* colb = static_cast<Collision_Box*>(col);

	ColorF color = KnifeBlock_HighlightColor;
	color.setA(0.4);
	
	EffectManager::GetEffect()->add<Effect_DeleteBulletBlock>(colb->GetOrientedBox(), color, delaytime);


	GameObject::Uninit();

}


void KnifeBlock::Update()
{
	// 最初に持ってくる
	GameObject::Update();


	// AddPositionと同じ。
	//OverwriteOffsetPosition(Vec3(0, 0.05, 0));


	if (m_Height < 0)
	{
		float addheight = 0.01;
		// AddPositionと同じ。
		OverwriteOffsetPosition(Vec3(0, addheight, 0));
		m_Height += addheight;

	}

	// 親の子供になると、AddPositionじゃ動かせなくなる。
	//AddPosition(GetVelocity());
	//AddRotation(GetRotationSpeed());

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void KnifeBlock::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

}
