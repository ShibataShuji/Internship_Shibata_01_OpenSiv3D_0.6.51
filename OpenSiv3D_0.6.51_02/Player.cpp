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
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Overlap);
	col->SetOffsetSize(0.3f);
}


void Player::Uninit()
{

}


void Player::Update()
{
	GameObject::Update();		// 最初に持ってくる

	Vec3 Forward = m_fpscamera.GetForward();
	Vec3 Right = m_fpscamera.GetRight();

	// 弾を出す処理
	if (MouseL.down())
	{
		GameData* gamedata = ManagerManager::GetGameData();
		KnifeBlock* p_KnifeBlock = gamedata->GameObjectListData.AddGameObject<KnifeBlock>();
		Vec3 LaunchPosition = m_Position + (Forward * 10.0);
		p_KnifeBlock->SetPosition(LaunchPosition);
		p_KnifeBlock->SetVelocity(Forward * 4.0);
		//p_KnifeBlock->SetScaleRate(Vec3(4, 0.5, 8));
	}


	// 減速処理。y軸の重力はジャンプのところで同時に行っている。
	Vec3 MovVel = GetVelocity();
	float friction = 0.85f;
	MovVel.x *= friction;
	MovVel.z *= friction;
	float little = 0.04f;	// 止まる誤差。AddVelValより小さな値を設定
	if (abs(MovVel.x) < little)
		MovVel.x = 0;
	if (abs(MovVel.z) < little)
		MovVel.z = 0;
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
		if (m_Jump == false)
		{
			m_Jump = true;
			m_JumpStartTime = Scene::Time();
			m_JumpTime = 0;
			m_DeltaEaseValue = 0;
		}
	}

	// ジャンプ中だったら
	if (m_Jump)
	{
		double maxjumptime = 0.6;	// ジャンプの時間
		float maxheight = 4.0f;		// 最大到達点
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
				double EaseValue = EaseOutExpo(EaseRate);
				double EaseUpValue = EaseValue - m_DeltaEaseValue;
				m_DeltaEaseValue = EaseValue;
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
	// 着地判定(本来はコリジョンでやるのでテスト用)
	if (GetPosition().y < 0.6)
	{
		SetPosition_y(0.6);
		SetVelocity_y(0.0);
		m_Jump = false;
	}

	

	ClearPrint();
	//// Hitしたもののリストでいろいろするとこ
	//for (auto hitobj : m_Collision_HitObjectList)
	//{
	//	
	//}
	// Overlapしたリストでいろいろするとこ
	for (auto oberlapobj : m_Collision_OverlapObjectList)
	{
		Print << U"OverlapPbject: {}"_fmt(oberlapobj->GetName());
	}
	//// 何かにオーバーラップしているのであれば
	//if (!m_Collision_OverlapObjectList.empty())
	//{

	//}

	// FPS視点でのマウスでのカメラ操作
	m_fpscamera.AddDirectionX(-1.0f * Cursor::DeltaF().x);
	m_fpscamera.AddDirectionY(-1.0f * Cursor::DeltaF().y);
	// マウスカーソルを中心に戻す処理
	//Cursor::SetPos(Scene::Center());
	//Cursor::RequestStyle(CursorStyle::Hidden);

	GameObject::ComponentUpdate();		// 最後に持ってくる
}


void Player::Draw()
{
	GameObject::Draw();	// 最初に持ってくる
}
