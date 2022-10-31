#include "stdafx.h"



void Player::Init()
{
	// このオブジェクトの名前
	m_Name = U"Player";

	auto col = AddComponent<Collision_Sphere>(U"PlayerBody");
	col->SetResponseObject(ResponseObject::PlayersPawn);
	col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Block);
	col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Overlap);
	col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
	col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
	col->SetOffsetSize(PlayerRadius);

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
	//col_Ground->SetCollisionColor(Linear::Palette::Brown);
	col_Ground->SetCollisionColor(ColorF(0.326, 0.029, 0.029, 0.0));
	col_Ground->SetVisibility(false);
}


void Player::Uninit()
{
	GameObject::Uninit();
}


void Player::Update()
{
	// 最初に持ってくる
	GameObject::Update();

	Vec3 Forward = TPSRay::GetFPSCamera()->GetForward();
	Vec3 Right = TPSRay::GetFPSCamera()->GetRight();

	// 接地判定のリセット
	m_HitGround = false;

	//ClearPrint();
	// Hitしたもののリストでいろいろするとこ
	for (auto hitobj : m_Collision_HitObjectList)
	{
		//Print << U"HitPbject: {}"_fmt(hitobj->GetName());

	}
	// Overlapしたリストでいろいろするとこ
	for (auto oberlapobj : m_Collision_OverlapObjectList)
	{
		//Print << U"OverlapPbject: {}"_fmt(oberlapobj->GetName());


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

			//{
			//	// 回転の中心オブジェクト
			//	GameObject* rotatecenterobj = nullptr;
			//	rotatecenterobj = oberlapobj->GetIfRotateParent(rotatecenterobj);
			//	if (rotatecenterobj != nullptr)
			//	{
			//		CalcRotateforObject(rotatecenterobj, this);
			//	}
			//}

			{
				// 移動床などで埋まってしまうので、ちょっとだけプレイヤーを上げてあげる。
				// あげすぎるとかたかたかたとなってしまう
				AddPosition(oberlapobj->GetDeltaPosition());
				Collision* playercol = GetCollisionComponent();
				Collision_Sphere* playerspher = static_cast<Collision_Sphere*>(playercol);
				Collision* othercol = oberlapobj->GetCollisionComponent();
				Collision_Box* otherbox = static_cast<Collision_Box*>(othercol);
				if (otherbox->GetOrientedBox()->intersects(*playerspher->GetSphere()))
					AddPosition_y(0.02);
			}
			

		}
	}
	//// 何かにオーバーラップしているのであれば
	//if (!m_Collision_OverlapObjectList.empty())
	//{

	//}

	//if (m_Jump && m_HitGround && m_JumpCoolTime <= 0.1)
	//{
	//	//m_Jump = false;
	//	AudioAsset(U"SE_Landing").playOneShot();
	//}


	// 着地した瞬間なら
	if (m_JumpTime > 0.3 && m_HitGround)
	{
		if (!m_LandingOnce)
		{
			m_LandingOnce = true;
			AudioAsset(U"SE_Landing").playOneShot();
		}
	}

	bool FallDoOnce = false;		// 落下判定で落下時にm_DeltaEaseValueをセットするために1フレーム遅らせている
	// 接地判定じゃなかったら
	if (!m_HitGround)
	{
		// ジャンプ中判定じゃなかったらジャンプ中にする。既にジャンプの落下中にする。
		if (!m_Jump)
		{
			m_LandingOnce = false;
			m_Jump = true;
			m_JumpStartTime = Scene::Time() - maxjumptime * 0.55;	// 落下なので半分以上に設定する。
			m_JumpTime = 0;
			m_DeltaEaseValue = 0;
			FallDoOnce = true;
		}
	}


	// 弾を出す処理
	if (MouseL.down())
	{
		bool safe = false;
		Optional<Vec3> hitposition;
		// 値を持っているかつ、
		if (TPSRay::GetintersectsAt()->has_value())
		{
			// それが赤ブロックじゃなければOK
			GameObject* rayhitobj = TPSRay::GetHitGameObject();
			Collision* collision = rayhitobj->GetCollisionComponent();
			if (collision->GetColor() != KnifeBlock_HighlightColor)
			{
				safe = true;
			}
			else
			{
				// 赤ブロックだった場合、そこで爆発エフェクトだけ出す。
				hitposition = TPSRay::GetintersectsAt()->value();
			}
		}


		if (safe)
		{

			GameData* gamedata = ManagerManager::GetGameData();
			//KnifeBullet* p_KnifeBullet = gamedata->GameObjectListData.AddGameObject<KnifeBullet>();
			
			// ブロックを生成
			KnifeBlock* p_KnifeBlock = gamedata->GameObjectListData.AddGameObject<KnifeBlock>();

			// バレットを生成
			KnifeBullet* p_KnifeBullet = gamedata->GameObjectListData.AddGameObject<KnifeBullet>();

			Vec3 RayHitPos = TPSRay::GetintersectsAt()->value();
			Vec3 GeneratePos = TPSRay::GetintersectsAt()->value();
			Vec3 hitnormal = *TPSRay::GetHitNormal();
			Vec3 defnormal = Vec3(0.0, 1.0, 0.0);
			// ブロックにめり込まないように法線の方にずらしてあげる
			GeneratePos.x += hitnormal.x * (KnifeBlock_Size.x * 0.5);
			GeneratePos.y += hitnormal.y * (KnifeBlock_Size.y * 0.5);
			GeneratePos.z += hitnormal.z * (KnifeBlock_Size.z * 0.5);

			// プレイヤーのコリジョンと衝突していたら、下にずらしてあげる。
			Collision_Sphere* colPlayer = GetComponentWithName<Collision_Sphere>(String{ U"PlayerBody" });
			OrientedBox box{ GeneratePos , KnifeBlock_Size };
			if (colPlayer->GetSphere()->intersects(box))
			{
				//GeneratePos.y -= PlayerRadius;
				GeneratePos.y -= PlayerRadius * 7;
				// 後から高さを上げてあげるようにする->ボツ
				p_KnifeBlock->SetHeight(-PlayerRadius * 7 * 0.5);
			}

			p_KnifeBlock->SetPosition(GeneratePos);

			// 衝突したものの子供に設定する
			GameObject* rayhitobj = TPSRay::GetHitGameObject();
			Collision* collision = rayhitobj->GetCollisionComponent();
			if (collision->GetColor() == KnifeBlock_HighlightColor)
			{
				// この時、親がもう壊れるブロック(赤色)だったら親子付けしないで破壊だけされるようにする。
				int parentnum = rayhitobj->GetParentNum() + 1;
				p_KnifeBlock->SetParentNum(parentnum);
				p_KnifeBlock->SetDestroy();
				p_KnifeBullet->SetDestroy();

			}
			else
			{
				// こっちが通常
				TPSRay::GetHitGameObject()->AddChild(p_KnifeBlock);

				p_KnifeBullet->SetCreatedMe(p_KnifeBlock);

			}

			// 球として配列に追加する。また、CreatedMeとしてプレイヤーをセットしておく
			AddBullet(p_KnifeBlock);

			// 球の軌道のためのオブジェクトを作る
			//Vec3 PtoGdistance = GeneratePos - GetPosition();
			Vec3 PtoGdistance = RayHitPos - GetPosition();
			Vec3 PtoGnorml = PtoGdistance.normalized();
			Vec3 PtoGnormlxz = PtoGnorml;
			PtoGnormlxz.y = 0;
			PtoGnormlxz.normalize();
			float r = 1.2;
			Vec3 BulletPos = GetPosition() + PtoGnormlxz * r;
			p_KnifeBullet->SetInitPosition(BulletPos);
			//Vec3 BtoGdistance = GeneratePos - BulletPos;
			Vec3 BtoGdistance = RayHitPos - BulletPos;
			Vec3 BtoGnorml = BtoGdistance.normalized();
			float speed = 2.0;
			p_KnifeBullet->SetVelocity(BtoGnorml* speed);

			
			Collision* col = p_KnifeBlock->GetCollisionComponent();
			col->SetVisibility(false);



			Vec3 HitNor = *TPSRay::GetHitNormal();
			//p_KnifeBullet->SetPosition(TPSRay::GetintersectsAt()->value());
		}
		else
		{
			// 衝突がない場合でも球は打てるようにしておく。
			GameData* gamedata = ManagerManager::GetGameData();

			KnifeBullet* p_KnifeBullet = gamedata->GameObjectListData.AddGameObject<KnifeBullet>();
			if(hitposition.has_value())
				p_KnifeBullet->SetSpherepos(hitposition.value());
			Vec3 Direction = TPSRay::GetRay()->getDirection();

			float r = 1.2;
			Vec3 BulletPos = GetPosition() + Direction * r;
			p_KnifeBullet->SetInitPosition(BulletPos);
			float speed = 2.0;
			p_KnifeBullet->SetVelocity(Direction * speed);

			// コンポーネントリスト全部を消す(今回はCollisionのみ)
			p_KnifeBullet->DestroyComponentList();
		}


		AudioAsset(U"SE_Bullet_Shot").playOneShot();

	}



	// 移動処理(ジャンプ以外)
	Movement();
	
	// ジャンプ
	if (KeySpace.pressed())
	{
		if (m_Jump == false && m_JumpCoolTime <= 0)
		{
			m_LandingOnce = false;
			AudioAsset(U"SE_Jump").playOneShot();
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
				//double EaseValue = EaseOutExpo(EaseRate);
				double EaseValue = EaseOutCirc(EaseRate);
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

	if (GetVelocity().y < -0.3)
		SetVelocity_y(-0.3);

	// デバッグモード
	if (m_DebugMode)
	{
		GameData* gamedata = ManagerManager::GetGameData();

		Collision* col = GetCollisionComponent();
		col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
		SetVelocity(Vec3(0, 0, 0));

		static Blocks* p_Blocks = nullptr;
		static Blocks* p_TestBlocks = gamedata->GameObjectListData.AddGameObject<Blocks>();

		double mova = 0.5;
		Vec3 forw = Forward * mova;
		Vec3 righ = Right * mova;
		Vec3 uppp = Vec3(0,1,0) * mova;

		if (KeyW.pressed())
			AddPosition(forw);
		if (KeyS.pressed())
			AddPosition(-forw);
		if (KeyD.pressed())
			AddPosition(righ);
		if (KeyA.pressed())
			AddPosition(-righ);
		if (KeyE.pressed())
			AddPosition(uppp);
		if (KeyQ.pressed())
			AddPosition(-uppp);

		static Vec3 blocksscale = Vec3(6, 6, 6);
		double cval = 0.08;
		if (Key1.pressed())
			blocksscale.x += cval;
		if (Key2.pressed())
			blocksscale.x -= cval;
		if (Key3.pressed())
			blocksscale.y += cval;
		if (Key4.pressed())
			blocksscale.y -= cval;
		if (Key5.pressed())
			blocksscale.z += cval;
		if (Key6.pressed())
			blocksscale.z -= cval;

		ClearPrint();
		Print << U"Pos: {:.2f}"_fmt(m_Position);
		Print << U"Scale: {:.2f}"_fmt(blocksscale);
		if (p_Blocks != nullptr) {
			Print << U"BlockPos: {:.2f}"_fmt(p_Blocks->GetPosition());
			Print << U"BlockScale: {:.2f}"_fmt(p_Blocks->GetScaleRate());
		}

		{
			// 透明なブロックのための。
			float radi = 6.0;
			Vec3 setpos = m_Position + Forward * radi;
			p_TestBlocks->SetInitPosition(setpos);
			p_TestBlocks->SetInitScaleRate(blocksscale);
			Collision* col = GetCollisionComponent();
			ColorF colortest = Linear::Palette::Brown;
			colortest.setA(0.2);
			col->SetCollisionColor(colortest);



			// 弾を出す処理
			if (MouseR.down())
			{
				gamedata = ManagerManager::GetGameData();
				// ブロックを生成
				p_Blocks = gamedata->GameObjectListData.AddGameObject<Blocks>();
				p_Blocks->SetInitPosition(setpos);
				p_Blocks->SetInitScaleRate(blocksscale);
			}
		}

		if (KeyP.pressed())
			p_Blocks->SetDestroy();

	}
	else
	{
		Collision* col = GetCollisionComponent();
		col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Block);
	}

	// 現在のベクトルで移動
	AddPosition(GetVelocity());


	// 影の場所の設定
	GetShadowPosition();

	// 球の上限チェック
	BulletsNumCheck();




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
	Disc{ m_ShadowPosition, 1 }.draw(Linear::Palette::Black);
}


// 影の場所の設定
void Player::GetShadowPosition()
{
	m_ShadowPosition = Vec3(0, -100, 0);

	Ray Shadowray = Ray{ m_Position, Vec3(0,-1,0) };

	// 作ったレイで当たっているオブジェクトを探す
	Component* IntersectCollisionComponent = nullptr;
	double minDistance = Math::Inf;
	for (auto gamobj : ManagerManager::GetGameData()->GameObjectListData.GetGameObjectList())
	{
		if (gamobj->GetName() == U"Player")
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


void Player::AddBullet(GameObject* bullet)
{
	m_Bullets.push_back(bullet);
	bullet->SetCreatedMe(this);
}

// 全ての球を消す
void Player::ResetBullets()
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
void Player::DeleteFirstBullet()
{
	if (m_Bullets.empty())
		return;

	m_Bullets.at(0)->SetDestroy();
	m_Bullets.pop_front();
}

// 外部から呼び出して使う。
void Player::DeleteBullet(GameObject* deletebullet)
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
void Player::BulletsNumCheck()
{
	if (m_Bullets.size() > PlayerMaxBullets)
	{
		DeleteFirstBullet();
	}

	for (auto bullet : m_Bullets)
	{
		bullet->GetCollisionComponent()->SetCollisionColor(KnifeBlock_DefColor);
	}

	// 次に壊れる足場を強調表示しておく
	if (m_Bullets.size() == PlayerMaxBullets)
	{
		m_Bullets.at(0)->GetCollisionComponent()->SetCollisionColor(KnifeBlock_HighlightColor);
		BulletChildSetColor(m_Bullets.at(0), KnifeBlock_HighlightColor);
	}
}

void Player::BulletChildSetColor(GameObject* bullet, const ColorF &setcolor)
{

	bullet->GetCollisionComponent()->SetCollisionColor(setcolor);

	for (auto child : bullet->GetChildList())
	{
		BulletChildSetColor(child, setcolor);
	}
}


void Player::Movement()
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
