#include "stdafx.h"

void Player::Init()
{
	// このオブジェクトの名前
	m_Name = U"Player";

	auto col = AddComponent<Collision_Sphere>();
	col->SetResponseObject(ResponseObject::PlayersPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(0.3f);

	// 接地判定のためのコリジョン。ItemsPawnにして、ブロック系だけOverlap
	auto col_Ground = AddComponent<Collision_Sphere>();
	col_Ground->SetResponseObject(ResponseObject::PlayerGround);
	col_Ground->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Overlap);
	col_Ground->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
	col_Ground->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
	col_Ground->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col_Ground->SetOffsetSize(0.1f);
	col_Ground->SetOffsetPosition(Vec3(0, -0.24, 0));
	col_Ground->SetCollisionColor(Linear::Palette::Brown);
}


void Player::Uninit()
{

}


void Player::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	/*Vec3 Forward = m_fpscamera.GetForward();
	Vec3 Right = m_fpscamera.GetRight();*/
	Vec3 Forward = TPSRay::GetFPSCamera()->GetForward();
	Vec3 Right = TPSRay::GetFPSCamera()->GetRight();

	// 接地判定のリセット
	m_HitGround = false;

	ClearPrint();
	// Hitしたもののリストでいろいろするとこ
	for (auto hitobj : m_Collision_HitObjectList)
	{
		Print << U"HitPbject: {}"_fmt(hitobj->GetName());

	}
	// Overlapしたリストでいろいろするとこ
	for (auto oberlapobj : m_Collision_OverlapObjectList)
	{
		Print << U"OverlapPbject: {}"_fmt(oberlapobj->GetName());


		if (oberlapobj->GetName() == U"Blocks" || oberlapobj->GetName() == U"KnifeBlock")
		{
			// 接地判定。
			if (!m_HitGround)
			{
				m_HitGround = true;	// 接地判定をtrueに。

			}
			// ジャンプした瞬間は接地判定を消しておく
			if (m_JumpCoolTime <= 0.1)
			{
				SetVelocity_y(0.0);
				m_Jump = false;
			}
		}
	}
	//// 何かにオーバーラップしているのであれば
	//if (!m_Collision_OverlapObjectList.empty())
	//{

	//}


	bool FallDoOnce = false;		// 落下判定で落下時にm_DeltaEaseValueをセットするために1フレーム遅らせている
	// 接地判定じゃなかったら
	if (!m_HitGround)
	{
		// ジャンプ中判定じゃなかったらジャンプ中にする。既にジャンプの落下中にする。
		if (!m_Jump)
		{
			m_Jump = true;
			m_JumpStartTime = Scene::Time() - maxjumptime * 0.55;	// 落下なので半分以上に設定する。
			m_JumpTime = 0;
			m_DeltaEaseValue = 0;
			FallDoOnce = true;
		}
	}


	// リスポーン用コマンド
	if (Key1.pressed())
		SetPosition(Vec3(0, 1, 0));

	// 弾を出す処理
	if (MouseL.down())
	{
		if (TPSRay::GetintersectsAt()->has_value())
		{
			GameData* gamedata = ManagerManager::GetGameData();
			//KnifeBullet* p_KnifeBullet = gamedata->GameObjectListData.AddGameObject<KnifeBullet>();
			
			// ブロックを生成
			KnifeBlock* p_KnifeBlock = gamedata->GameObjectListData.AddGameObject<KnifeBlock>();
			Vec3 GeneratePos = TPSRay::GetintersectsAt()->value();
			Vec3 GenerateRot;
			Vec3 hitnormal = *TPSRay::GetHitNormal();
			Vec3 defnormal = Vec3(0.0, 1.0, 0.0);

			p_KnifeBlock->SetPosition(GeneratePos);

			// 衝突したものの子供に設定する
			TPSRay::GetHitGameObject()->AddChild(p_KnifeBlock);


			Vec3 HitNor = *TPSRay::GetHitNormal();
			//p_KnifeBullet->SetPosition(TPSRay::GetintersectsAt()->value());
		}

	}


	// 減速処理。y軸の重力はジャンプのところで同時に行っている。
	Vec3 MovVel = GetVelocity();
	float friction = 0.85f;
	MovVel.x *= friction;
	MovVel.z *= friction;
	float little = 0.04f;	// 止まる誤差。AddVelValより小さな値を設定
	if (MovVel.lengthSq() < pow(little, 2))
	{
		MovVel.x = 0;
		MovVel.z = 0;
	}
	SetVelocity(MovVel);
	

	MovVel = Vec3(0, 0, 0);
	// 移動
	float AddVelVal = 0.05f;
	float AddVelVal_y = 0.05f;
	if (KeyW.pressed())
		MovVel += Forward;
	if (KeyS.pressed())
		MovVel -= Forward;
	if (KeyD.pressed())
		MovVel += Right;
	if (KeyA.pressed())
		MovVel -= Right;
	if (!MovVel.isZero())
	{
		MovVel.normalize();
		if(!IsNaN(MovVel))
			AddVelocity(MovVel * AddVelVal);
	}
	// ジャンプ
	if (KeySpace.pressed())
	{
		if (m_Jump == false && m_JumpCoolTime <= 0)
		{
			m_JumpCoolTime = 0.2;
			m_Jump = true;
			m_JumpStartTime = Scene::Time();
			m_JumpTime = 0;
			m_DeltaEaseValue = 0;
		}
	}

	// ジャンプ中だったら
	if (m_Jump)
	{
		m_JumpTime = Scene::Time() - m_JumpStartTime;
		if (m_JumpTime >= maxjumptime)
		{
			// 終了
			//m_Jump = false;
		}
		else
		{
			// ジャンプの時間の割合
			double RateOfProgress;
			if (m_JumpTime <= 0.0)
				RateOfProgress = 0.0;
			else
				RateOfProgress = m_JumpTime / maxjumptime;
			// 上昇中
			if (RateOfProgress < 0.5)
			{
				double EaseRate = RateOfProgress * 2.0;
				double EaseValue = EaseOutExpo(EaseRate);
				double EaseUpValue = EaseValue - m_DeltaEaseValue;
				m_DeltaEaseValue = EaseValue;
				SetVelocity_y(EaseUpValue * maxheight);
			}
			// 落下中
			else
			{
				double EaseRate = (1.0 - RateOfProgress) * 2.0;
				double EaseValue = EaseOutCirc(EaseRate);
				double EaseUpValue = EaseValue - m_DeltaEaseValue;
				m_DeltaEaseValue = EaseValue;
				if(!FallDoOnce)
					SetVelocity_y(EaseUpValue * maxheight);
			}
		}
	}


	// 速度制限
	float maxspeed = 0.5f;
	MovVel = GetVelocity();
	if (MovVel.x > maxspeed)
		MovVel.x = maxspeed;
	if (MovVel.x < -maxspeed)
		MovVel.x = -maxspeed;
	if (MovVel.z > maxspeed)
		MovVel.z = maxspeed;
	if (MovVel.z < -maxspeed)
		MovVel.z = -maxspeed;
	SetVelocity(MovVel);

	// 現在のベクトルで移動
	AddPosition(GetVelocity());

	Vec3 ddfdfdf = GetVelocity();
	Vec3 fdfdf = GetPosition();
	//// 着地判定(本来はコリジョンでやるのでテスト用)
	//if (GetPosition().y < 0.6)
	//{
	//	SetPosition_y(0.6);
	//	SetVelocity_y(0.0);
	//	m_Jump = false;
	//}


	// ジャンプのクールタイムの更新
	if(m_JumpCoolTime > 0)
		m_JumpCoolTime -= Scene::DeltaTime();

	// 最後に持ってくる
	GameObject::ComponentUpdate();
	GameObject::ChildUpdate();
}


void Player::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}
