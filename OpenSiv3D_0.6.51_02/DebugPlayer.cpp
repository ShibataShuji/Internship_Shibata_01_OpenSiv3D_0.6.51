#include "stdafx.h"

void DebugPlayer::Init()
{
	// このオブジェクトの名前
	m_Name = U"DebugPlayer";

	auto col = AddComponent<Collision_Sphere>(U"PlayerBody");
	col->SetResponseObject(ResponseObject::PlayersPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(DebugPlayerRadius);

	// 接地判定のためのコリジョン。ItemsPawnにして、ブロック系だけOverlap
	auto col_Ground = AddComponent<Collision_Sphere>();
	col_Ground->SetResponseObject(ResponseObject::PlayerGround);
	col_Ground->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
	col_Ground->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col_Ground->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col_Ground->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col_Ground->SetOffsetSize(0.1f);
	col_Ground->SetOffsetPosition(Vec3(0, -0.24, 0));
	col_Ground->SetCollisionColor(Linear::Palette::Brown);
}


void DebugPlayer::Uninit()
{
	GameObject::Uninit();
}


void DebugPlayer::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	Vec3 Forward = TPSRay::GetFPSCamera()->GetForward();
	Vec3 Right = TPSRay::GetFPSCamera()->GetRight();



	// 移動処理(ジャンプ以外)
	Movement();

	// 現在のベクトルで移動
	AddPosition(GetVelocity());


	// 球の上限チェック
	BulletsNumCheck();



	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void DebugPlayer::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}


// 影の場所の設定
void DebugPlayer::GetShadowPosition()
{
	m_ShadowPosition = Vec3(0, -100, 0);

	Ray Shadowray = Ray{ m_Position, Vec3(0,-1,0) };

	// 作ったレイで当たっているオブジェクトを探す
	Component* IntersectCollisionComponent = nullptr;
	double minDistance = Math::Inf;
	for (auto gamobj : ManagerManager::GetGameData()->GameObjectListData.GetGameObjectList())
	{
		if (gamobj->GetName() == U"DebugPlayer")
			continue;

		for (auto comp : gamobj->GetComponentList())
		{
			Optional<double> intersects;
			if (typeid(*comp) == typeid(Collision_Box))
			{
				Collision_Box* colBox = static_cast<Collision_Box*>(comp);
				intersects = Shadowray.intersects(*colBox->GetOrientedBox());
			}
			else if (typeid(*comp) == typeid(Collision_Sphere))
			{
				Collision_Sphere* colSphere = static_cast<Collision_Sphere*>(comp);
				intersects = Shadowray.intersects(*colSphere->GetSphere());
			}
			/*else if (typeid(comp) == typeid(Collision_Capsule))
			{

			}*/

			if (intersects)
			{
				// 交差地点までの距離が一番近いモノの更新
				if (intersects.value() < minDistance)// && intersectsAt.value().lengthSq() > 0.2)
				{
					minDistance = intersects.value();
					IntersectCollisionComponent = comp;
				}
			}
		}
	}


	m_ShadowPosition = Shadowray.getOrigin() + Shadowray.getDirection() * minDistance;
	// 最後にZファイトが起きないように少し上げておく
	m_ShadowPosition.y += 0.05;

}


void DebugPlayer::AddBullet(GameObject* bullet)
{
	m_Bullets.push_back(bullet);
	bullet->SetCreatedMe(this);
}

// 全ての球を消す
void DebugPlayer::ResetBullets()
{
	if (m_Bullets.empty())
		return;

	for (auto bullet : m_Bullets)
	{
		bullet->SetDestroy();
	}
	m_Bullets.clear();
}

// 配列の最初の球を消す
void DebugPlayer::DeleteFirstBullet()
{
	if (m_Bullets.empty())
		return;

	m_Bullets.at(0)->SetDestroy();
	m_Bullets.pop_front();
}

// 外部から呼び出して使う。
void DebugPlayer::DeleteBullet(GameObject* deletebullet)
{
	if (m_Bullets.empty())
		return;


	for (auto bullet : m_Bullets)
	{
		if (bullet == deletebullet)
		{
			m_Bullets.remove(bullet);
			return;
		}
	}

}

// 球が上限を超えていたら出た順に消していく
void DebugPlayer::BulletsNumCheck()
{
	if (m_Bullets.size() > DebugPlayerMaxBullets)
	{
		DeleteFirstBullet();
	}

	for (auto bullet : m_Bullets)
	{
		bullet->GetCollisionComponent()->SetCollisionColor(KnifeBlock_DefColor);
	}

	// 次に壊れる足場を強調表示しておく
	if (m_Bullets.size() == DebugPlayerMaxBullets)
	{
		m_Bullets.at(0)->GetCollisionComponent()->SetCollisionColor(KnifeBlock_HighlightColor);
		BulletChildSetColor(m_Bullets.at(0), KnifeBlock_HighlightColor);
	}
}

void DebugPlayer::BulletChildSetColor(GameObject* bullet, const ColorF& setcolor)
{

	bullet->GetCollisionComponent()->SetCollisionColor(setcolor);

	for (auto child : bullet->GetChildList())
	{
		BulletChildSetColor(child, setcolor);
	}
}


void DebugPlayer::Movement()
{
	Vec3 Forward = TPSRay::GetFPSCamera()->GetForward();
	Vec3 Right = TPSRay::GetFPSCamera()->GetRight();

	{
		// 減速処理。y軸の重力はジャンプのところで同時に行っている。
		Vec3 MovVel = GetVelocity();
		float friction = 0.80f;
		MovVel.x *= friction;
		MovVel.z *= friction;
		float little = 0.01f;	// 止まる誤差。AddVelValより小さな値を設定
		Vec3 check = MovVel;
		check.y = 0;
		if (check.lengthSq() < pow(little, 2))
		{
			MovVel.x = 0;
			MovVel.z = 0;
		}
		SetVelocity(MovVel);
	}


	{
		// 移動
		Vec3 AddVel = Vec3(0, 0, 0);
		float AddVelVal = 0.05f;

		if (KeyW.pressed())
			AddVel += Forward;
		if (KeyS.pressed())
			AddVel -= Forward;
		if (KeyD.pressed())
			AddVel += Right;
		if (KeyA.pressed())
			AddVel -= Right;
		if (!AddVel.isZero())
		{
			AddVel.normalize();
			if (!IsNaN(AddVel))
				AddVelocity(AddVel * AddVelVal);
			else
				int frg = 5;
		}
	}

	{
		// 速度制限
		float maxspeed = 0.3f;
		Vec3 MovVel = GetVelocity();
		Vec3 check = MovVel;
		check.y = 0;
		if (check.lengthSq() > pow(maxspeed, 2))
		{
			Vec3 norVec = check.normalized();
			check = norVec * maxspeed;

			MovVel.x = check.x;
			MovVel.z = check.z;
		}

		SetVelocity(MovVel);
	}


}
