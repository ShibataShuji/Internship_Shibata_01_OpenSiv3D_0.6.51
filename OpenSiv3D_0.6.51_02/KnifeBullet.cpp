#include "stdafx.h"


void KnifeBullet::Init()
{
	// このオブジェクトの名前
	m_Name = U"KnifeBullet";

	auto col = AddComponent<Collision_Sphere>();
	col->SetResponseObject(ResponseObject::PlayerBullet);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(KnifeBulletSize);
	col->SetVisibility(false);	// 見えない設定にして、本体は別にDrawで描く
	//col->SetHittoStop(true);	// 壁ずりしない設定にする
}


void KnifeBullet::Uninit()
{

	GameObject::Uninit();
}

void KnifeBullet::EndKnifeBullet()
{
	// 衝突のエフェクト
	EffectManager::GetEffect()->add<BulletEffect_Hit>(GetPosition(), Random(0.0, 360.0));

	if (GetCreatedMe() != nullptr)
	{
		String name = GetCreatedMe()->GetName();
		if (name == U"KnifeBlock")
		{
			Collision* col = GetCreatedMe()->GetCollisionComponent();
			if (col != nullptr)
				col->SetVisibility(true);
		}
	}
	m_DoOnce = false;
	SetDestroy();
}


void KnifeBullet::Update()
{
	if (!m_DoOnce)
		return;

	// 座標指定で衝突判定をとる場合(この場合親の設定がされてないはず、赤のブロックに当たった判定)
	if (m_Spherepos.has_value())
	{
		Sphere finsphere{ m_Spherepos.value() , 1.0};
		Sphere selfsphere{ m_Position , 1.0};
		if (selfsphere.intersects(finsphere))
		{
			EndKnifeBullet();
			AudioAsset(U"SE_Bullet_Buu").playOneShot();	// ぶーおん
		}
	}

	Sphere InitPosSphere{ GetInitPosition() , 3.0 };

	GameObject* createdme = GetCreatedMe();
	if (createdme != nullptr)
	{
		String name = createdme->GetName();
		if (name == U"KnifeBlock")
		{
			Collision* col = GetCreatedMe()->GetCollisionComponent();
			Collision_Box* colb = static_cast<Collision_Box*>(col);
			if (colb != nullptr)
			{
				OrientedBox* oribox = colb->GetOrientedBox();
				if (InitPosSphere.intersects(*oribox))
				{
					EndKnifeBullet();
					AudioAsset(U"SE_Bullet_Hit").playOneShot();
				}
			}
		}
	}

	// 最初に持ってくる
	GameObject::Update();

	// 5秒たっても当たってなかったら消す
	if(m_ElapsedTime > 5.0)
	{
		EndKnifeBullet();
	}


	//if (GetCreatedMe() == nullptr)
	//{
	//	EndKnifeBullet();
	//}

	// Overlapしたリストでいろいろするとこ
	for (auto oberlapobj : m_Collision_OverlapObjectList)
	{
		if (GetCreatedMe() != nullptr)
		{
			if (oberlapobj == GetCreatedMe())
			{
				EndKnifeBullet();
				AudioAsset(U"SE_Bullet_Hit").playOneShot();
			}
		}
	}


	if (m_IntervalTime >= 0.03)
	{
		m_IntervalTime = 0.0;
		EffectManager::GetEffect()->add<BulletEffect_WithBullet>(GetPosition(), Random(0.0, 360.0));
	}


	AddPosition(GetVelocity());

	m_ElapsedTime += Scene::DeltaTime();
	m_IntervalTime += Scene::DeltaTime();;

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void KnifeBullet::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

	Sphere{ m_Position, KnifeBulletSize }.draw(KnifeBulletColor);
}
