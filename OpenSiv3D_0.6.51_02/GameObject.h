#pragma once

class GameObject
{
protected:	// アクセス指定子

	bool				m_Destroy = false;

	// 初期の座標等。データの保存の時にも使う
	Vec3				m_InitPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_InitRotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_InitScaleRate = Vec3(1.0f, 1.0f, 1.0f);

	// 実際に処理計算で使う座標等
	Vec3				m_Position = m_InitPosition;
	Vec3				m_Rotation = m_InitRotation;
	//Vec3				m_Scale = Vec3(1.0f, 1.0f, 1.0f);
	Vec3				m_ScaleRate = m_InitScaleRate;

	Vec3				m_Old_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Delta_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Old_Rotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Delta_Rotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Velocity = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_RotationSpeed = Vec3(0.0f, 0.0f, 0.0f);
	bool				m_HasRotationSpeed = false;
	bool				m_ParentHasRotationSpeed = false;		// 親または親の親。。が回転の中心を持っているか。回転の回転...は取れない。１つの親が回転してる場合のみ。

	// 移動に便利なMove用
	bool				m_Move_Use = false;
	Vec3				m_Move_FinPos = Vec3(0.0f, 0.0f, 0.0f);
	float				m_Move_TravelTime = 10.0f;
	float				m_Move_SlowTime = 1.0f;
	//float				m_Move_StopTime = 1.0f;
	float				m_Move_ElapsedTime = m_Move_TravelTime;
	bool				m_Move_Go = true;
	bool				m_Move_Go_DoOnce = false;
	Vec3				m_Move_Velocity = Vec3(0.0f, 0.0f, 0.0f);
	float				m_Move_DelayTime = 0.0f;



	String				m_Name = U"noname";

	// 子供になった瞬間の親と子供の座標などを保存する
	//Vec3				m_ParentStartPosition = Vec3(0.0f, 0.0f, 0.0f);
	//Vec3				m_ParentStartRotation = Vec3(0.0f, 0.0f, 0.0f);
	//Vec3				m_ParentStartScaleRate = Vec3(1.0f, 1.0f, 1.0f);

	int					m_ParentNum = 0;

	Vec3				m_MomentChild_ParentPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_MomentChild_MyPosition = Vec3(0.0f, 0.0f, 0.0f);

	Vec3				m_OffsetPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_OffsetRotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_OffsetScaleRate = Vec3(1.0f, 1.0f, 1.0f);
	Vec3				m_OffsetScaleRateAdjuste = Vec3(1.0f, 1.0f, 1.0f);


	GameObject*			m_CreatedMe;		// このゲームオブジェクトを生み出したオブジェクト
	Array<Component*>	m_ComponentList;
	Array<String>		m_ComponentNameList;
	Array<GameObject*>	m_Child;
	GameObject*			m_Parent = nullptr;	// 親は一人
	bool m_UpdateOnece = false;	// 子供の場合親からそのままアップデートが呼ばれるので、2回呼ばないように。


	// Collisionコンポーネントを1つでも持っているときに使うよう変数。本当はコリジョンがついてたらもつってしたい。
	Array<GameObject*>	m_Collision_HitObjectList;
	Array<Vec3>			m_Collision_HitPositionList;
	Array<Vec3>			m_Collision_HitNormalList;	// 衝突した面(球)の法線ベクトル

	Array<GameObject*>	m_Collision_OverlapObjectList;
	//Array<Vec3>			m_Collision_OverlapPositionList;


public:

	GameObject() {}


	virtual ~GameObject()
	{
		// 子供やコンポーネントのdeleteは
		// Uninitでしてる。
	}


	virtual void Init()	// 純粋仮想関数
	{
		// 継承先で親関数のこれ呼ぶの面倒なので
		// コンストラクタでやった方がいいのかも
	}


	virtual void Uninit()
	{
		for (auto comp : m_ComponentList)
		{
			if (comp != nullptr)
				comp->Uninit();
		}

		// Child子供はSetDestroyで消す予約をしているので、自分で消えてくれる



	}

	// virtual(純粋仮想関数)なので、これを継承したplayerクラスなどでUpdate関数を作るとそっちが呼ばれて
	// これは呼ばれないが、playerのupdateの方でこれを呼ぶ(親クラスのupdate)と呼べる。
	// これの子クラスであるplayerとかの中で明示的にGameObject::Updateって風に呼ばないといけない。
	// Drawとか忘れがちなので注意
	virtual void Update()
	{
		if (this == nullptr)
			return;

		// 座標の保存
		m_Delta_Position = m_Position - m_Old_Position;
		m_Delta_Rotation = m_Rotation - m_Old_Rotation;


		m_Old_Position = m_Position;
		m_Old_Rotation = m_Rotation;

		// 親がいる場合
		if (m_Parent != nullptr)
		{
			ParentChildCalculate();

		}

	}

	// 親子関係の計算。親を元にm_Position等が更新される
	void ParentChildCalculate();

	// この実行フレームの1回目のアップデートだったらtrue
	bool UpdateOnceCheck()
	{
		// この実行フレームの1回目のアップデートだったらtrue
		// 2回目以降だとfalse。子供が２回アップデートされないようにするため。
		if (!m_UpdateOnece && m_Parent == nullptr)	// 1回目かつ親がいない場合
		{
			m_UpdateOnece = true;
			return true;
		}
		return false;
	}
	// UpdateOneceをセットする
	void SetUpdateOnece(const bool &bo)
	{
		m_UpdateOnece = bo;
	}

	// 子供のアップデート。
	void ChildUpdate()
	{
		if (this == nullptr)
			return;

		for (auto child : m_Child)
		{
			if(child == nullptr)
				return;
			child->SetUpdateOnece(true);
			child->Update();
		}
	}


	virtual void Draw()
	{
		for (const auto& c : m_ComponentList)
			c->Draw();
	}


	// コンポーネントのアップデート
	virtual void ComponentUpdate()
	{
		//// コリジョン系の変数のリセット
		ResetCollisionHitArray();

		for (int i = 0; i < UpdatePriority_Max; i++)
		{
			for (const auto& comp : m_ComponentList)
			{
				if (comp->GetComponentUpdatePriority() == i)
					comp->Update();
			}
		}
	}

	void ResetCollisionHitArray()
	{
		// コリジョン系の変数のリセット
		m_Collision_HitObjectList.clear();
		m_Collision_HitPositionList.clear();
		m_Collision_HitNormalList.clear();
		m_Collision_OverlapObjectList.clear();
		//m_Collision_OverlapPositionList.clear();
	}

	String& GetName() { return m_Name; }
	void SetName(const String& name) { m_Name = name; }


	GameObject* GetCreatedMe()
	{
		if (m_CreatedMe == nullptr)
			return nullptr;

		if (!m_CreatedMe->GetDestroyState())
			return m_CreatedMe;
		else
			return nullptr;
	}
	void SetCreatedMe(GameObject* createdobject) { m_CreatedMe = createdobject; }

	// Init系
	void SetInitPosition(const Vec3& initposition)
	{
		m_InitPosition = initposition;
		m_Position = m_InitPosition;
		m_Old_Position = m_InitPosition;
	}
	Vec3 GetInitPosition() { return m_InitPosition; }
	void SetInitRotation(const Vec3& initrotation)
	{
		m_InitRotation = initrotation;
		m_Rotation = m_InitRotation;
		m_Old_Rotation = m_InitRotation;
	}
	Vec3 GetInitRotation() { return m_InitRotation; }
	void SetInitScaleRate(const Vec3& initscalerate)
	{
		m_InitScaleRate = initscalerate;
		m_ScaleRate = m_InitScaleRate;
	}
	Vec3 GetInitScaleRate() { return m_InitScaleRate; }


	void AddPosition(const Vec3& AddPosition) { m_Position += AddPosition; }
	void SetPosition(const Vec3& position) { m_Position = position; }
	void SetPosition_x(const float& x) { m_Position.x = x; }
	void SetPosition_y(const float& y) { m_Position.y = y; }
	void SetPosition_z(const float& z) { m_Position.z = z; }
	Vec3 GetPosition() { return m_Position; }
	void AddPosition_y(const float& y) { m_Position.y += y; }


	Vec3 GetOldPosition() { return m_Old_Position; }
	Vec3 GetDeltaPosition() { return m_Delta_Position; }
	Vec3 GetOldRotation() { return m_Old_Rotation; }
	Vec3 GetDeltaRotation() { return m_Delta_Rotation; }

	void SetRotation(const Vec3& rotation)
	{
		m_Rotation = rotation;
	}
	Vec3 GetRotation() { return m_Rotation; }
	void AddRotation(const Vec3& rotation) { m_Rotation += rotation; }




	/*void SetScale(Vec3 scale) { m_Scale = scale; }
	Vec3 GetScale() { return m_Scale; }*/
	void SetScaleRate(const Vec3& SetScaleRate) { m_ScaleRate = SetScaleRate; }
	Vec3 GetScaleRate() { return m_ScaleRate; }

	Vec3 GetVelocity() { return m_Velocity; }
	void SetVelocity(const Vec3& Velocity) { m_Velocity = Velocity; }
	void SetVelocity_x(const float& x) { m_Velocity.x = x; }
	void SetVelocity_y(const float& y) { m_Velocity.y = y; }
	void SetVelocity_z(const float& z) { m_Velocity.z = z; }
	void AddVelocity(const Vec3& Velocity) { m_Velocity += Velocity; }
	void AddVelocity_y(const float& y) { m_Velocity.y += y; }

	Vec3 GetRotationSpeed() { return m_RotationSpeed; }
	void SetRotationSpeed(const Vec3& rotationspeed)
	{
		m_RotationSpeed = rotationspeed;
		if(!m_RotationSpeed.isZero())
			m_HasRotationSpeed = true;
	}
	void AddRotationSpeed(const Vec3& rotationspeed) { m_RotationSpeed += rotationspeed; }

	void SetDestroy()
	{
		//// 既に消す予約が入っていたら
		//if (m_Destroy)
		//	return;


		m_Destroy = true;

		// これの子供も消す準備する
		if (!m_Child.empty())
		{
			int feg = m_Child.size();
			Array<GameObject*> childlist;
			for (auto child : m_Child)
				childlist.push_back(child);

			for (auto child : childlist)
				child->SetDestroy();
		}

		// 親のリストから外す
		if (GetParent() != nullptr)
		{
			if (!m_Parent->m_Child.empty())
			{
				int index = 0;
				for (auto Pchild : m_Parent->m_Child)
				{
					if (Pchild == this)
					{
						break;
					}
					index++;
				}
				m_Parent->m_Child.remove_at(index);
			}
		}

	}

	bool GetDestroyState()
	{
		if (this == nullptr)
			return true;
		return m_Destroy;
	}
	// 現在のm_Destroyの状態によってdeleteする。
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	Vec3 GetForward()	// 前方向ベクトル
	{
		Mat4x4 rot = Mat4x4::RollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 forward{};
		forward.x = rot.value.r[2].m128_f32[0];
		forward.y = rot.value.r[2].m128_f32[1];
		forward.z = rot.value.r[2].m128_f32[2];

		return forward;
	}

	Vec3 GetRight()	// 右方向ベクトル
	{
		Mat4x4 rot = Mat4x4::RollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 right;
		right.x = rot.value.r[0].m128_f32[0];
		right.y = rot.value.r[0].m128_f32[1];
		right.z = rot.value.r[0].m128_f32[2];

		return right;
	}

	Vec3 GetUp()	// 上方向ベクトル
	{
		Mat4x4 rot = Mat4x4::RollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 up;
		up.x = rot.value.r[1].m128_f32[0];
		up.y = rot.value.r[1].m128_f32[1];
		up.z = rot.value.r[1].m128_f32[2];

		return up;
	}

	// コンポーネントを追加する。引き数で名前を付けることができる。空白の場合勝手に命名される
	template <typename T>
	T* AddComponent()
	{
		// このオブジェクトが追加するコンポーネントの親になるので、コンストラクタでthisを設定する
		T* ccomponent = new T(this);
		ccomponent->Init();
		m_ComponentList.push_back(ccomponent);
		m_ComponentNameList.push_back(U"noname");

		return ccomponent;
	}
	// 名前つけるバージョン
	template <typename T>
	T* AddComponent(const String& name)
	{
		T* ccomponent = new T(this);
		ccomponent->Init();
		m_ComponentList.push_back(ccomponent);
		m_ComponentNameList.push_back(name);

		return ccomponent;
	}

	// このゲームオブジェクトの中に引き数の名前をつけているコンポーネントがあればそのコンポーネントを返す
	// あってはならないが複数あったらリストの最初のものが返る
	template <typename T>
	T* GetComponentWithName(const String& name)
	{
		int itrCount = 0;
		for (const auto& cName : m_ComponentNameList)
		{
			// 文字列が同じものがあったら
			if (name == cName)
			{
				auto itr = m_ComponentList.begin();		// 本当は std::list<int>::iterator itr だけどautoで省略
				for (int i = 0; i < itrCount; i++)
				{
					++itr;
				}
				return (T*)*itr;						// itrはポインタなので*itrで中身を返してあげる
			}

			itrCount++;
		}
		return nullptr;
	}

	Array<Component*> GetComponentList()
	{
		return m_ComponentList;
	}

	template <typename T>
	bool HasComponent()
	{
		for (const auto& c : m_ComponentList)
		{
			if (typeid(*c) == typeid(T))
			{
				return true;
			}
		}
		return false;
	}

	Collision* GetCollisionComponent()
	{
		for (auto comp : m_ComponentList)
		{
			Collision* ret = static_cast<Collision*>(comp);
			return ret;

			if (typeid(comp) == typeid(Collision))
			{
				Collision* ret = static_cast<Collision*>(comp);
				return ret;
			}
		}
		return nullptr;
	}

	int GetComponentNum()
	{
		int count = 0;
		for (const auto& Comp : m_ComponentList)
		{
			count++;
		}
		return count;
	}

	void DestroyComponent(const int& compCount)
	{


		Component* temp = nullptr;

		int count = 0;
		for (const auto& Comp : m_ComponentList)
		{
			if (count == compCount)
			{
				temp = Comp;				// あとでdeleteするために保存しておく
				break;						// リストで消した後にdeleteする。がポインタが消えてしまうため。
			}
			count++;
		}


		auto it = m_ComponentList.begin();
		for (int i = 0; i < compCount; i++)
			it++;
		m_ComponentList.erase(it);

		temp->Uninit();
		return;
	}

	void DestroyComponentList()
	{

		Array<Component*> templist;
		templist = m_ComponentList;

		m_ComponentList.clear();

		for (const auto& tempc : templist)
		{
			tempc->Uninit();
		}
		return;
	}


	// Child系	Array<GameObject*>	m_Child;
	// 子供の追加。先にゲームオブジェクトA,Bを作って、そのあとにAにBを追加する。という感じで使う。
	void AddChild(GameObject* gameobject)
	{
		m_Child.push_back(gameobject);
		gameobject->m_Parent = this;	// 子供の親には自分を設定する

		// 子供になった瞬間、子供側で、オフセット値等を保存する
		//gameobject->m_ParentStartPosition = GetPosition();
		//gameobject->m_ParentStartRotation = GetRotation();
		//gameobject->m_ParentStartScaleRate = GetScaleRate();

		gameobject->m_MomentChild_ParentPosition = GetPosition();
		gameobject->m_MomentChild_MyPosition = gameobject->GetPosition();

		gameobject->m_OffsetPosition = gameobject->GetPosition() - GetPosition();
		gameobject->m_OffsetRotation = gameobject->GetRotation() - GetRotation();
		//gameobject->m_OffsetQuaternion = gameobject->GetQuaternion();
		//gameobject->m_OffsetScaleRate = gameobject->GetScaleRate() * GetScaleRate();
		gameobject->m_OffsetScaleRate = gameobject->GetScaleRate() / GetScaleRate();	// ScaleRateは逆数を入れて、最終的な結果を現在と変わらないようにしておく
		// その瞬間の親の大きさを基準にスケールを調整するために、かけて1.0になるような値を取得しておく。
		gameobject->m_OffsetScaleRateAdjuste = Vec3(1.0, 1.0, 1.0) / gameobject->GetScaleRate();

		// 自分の親の数+1してあげる
		gameobject->m_ParentNum = m_ParentNum + 1;

		// 自分が回転の中心だったら、子供に教えてあげる
		if (m_HasRotationSpeed)
			gameobject->m_ParentHasRotationSpeed = true;
		if (m_ParentHasRotationSpeed)
			gameobject->m_ParentHasRotationSpeed = true;

	}

	void OverwriteOffsetPosition(const Vec3 &addvec)
	{
		m_MomentChild_MyPosition += addvec;

		// もともと、Offset = 瞬間の子供 - 瞬間の親なので、瞬間の子供を変えれば変わる
		m_OffsetPosition = m_MomentChild_MyPosition - m_MomentChild_ParentPosition;
	}

	Array<GameObject*> GetChildList()
	{
		return m_Child;
	}

	// 子供リストにそのゲームオブジェクトを含んでいるかどうか。
	bool GetChild(GameObject* &gameobject)
	{
		if(m_Child.includes(gameobject))
			return true;

		return false;
	}

	// 親を返す。いない場合nullptr
	GameObject* GetParent()
	{
		if (m_Parent == nullptr)
			return nullptr;
		else if (m_Parent->GetDestroyState())
			return nullptr;

		return m_Parent;

	}





	// Collision用
	void Collision_AddHitObject(GameObject* hitobject, const Vec3& hitpos, const Vec3& hitnormal)
	{
		if (hitobject->GetDestroyState())
			return;

		m_Collision_HitObjectList.push_back(hitobject);
		m_Collision_HitPositionList.push_back(hitpos);
		m_Collision_HitNormalList.push_back(hitnormal);
	}
	/*void Collision_AddHitObject(GameObject* hitobject)
	{
		m_Collision_HitObjectList.push_back(hitobject);
	}
	void Collision_AddHitPosition(const Vec3& hitpos)
	{
		m_Collision_HitPositionList.push_back(hitpos);
	}
	void Collision_AddHitNormal(const Vec3& hitnormal)
	{
		m_Collision_HitNormalList.push_back(hitnormal);
	}*/

	void Collision_AddOverlapObject(GameObject* overlapobject)//, const Vec3& overlappos)
	{
		if (overlapobject->GetDestroyState())
			return;

			m_Collision_OverlapObjectList.push_back(overlapobject);
		//m_Collision_OverlapPositionList.push_back(overlappos);
	}

	// Get
	Array<GameObject*> GetCollision_HitObjectList()
	{
		return m_Collision_HitObjectList;
	}
	Array<GameObject*> GetCollision_OverlapObjectList()
	{
		return m_Collision_OverlapObjectList;
	}


	// 指定した２点(1点目はInitPos)を指定した秒数で行き来する。
	void MoveingObjectUpdate()
	{
		// 使わない設定だったら終わる
		if (!m_Move_Use)
			return;

		Vec3 MoveDistance = m_Move_FinPos - m_InitPosition;
		Vec3 MoveDistanceOne = MoveDistance * 0.1;

		// 2割りゆっくり６割ふつう２割ゆっくり。たして10になるようにする
		float LnegthWari_Slow = 2.0;
		float LnegthWari_Norm = 6.0;

		// Positionをそのまま変えちゃう。
		Vec3 ThisOffsetPos = Vec3(0, 0, 0);
		float wariai = 0.0;

		if (m_Move_Go)
		{
			// 行きだったら

			MoveingObject_DoOnceCheck();

			if (m_Move_ElapsedTime < m_Move_SlowTime)
			{
				// 0~1なら、1秒で１割進む
				wariai = m_Move_ElapsedTime / m_Move_SlowTime;
				ThisOffsetPos = EaseInSine(wariai) * (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime < m_Move_TravelTime - m_Move_SlowTime)
			{
				// 1~9なら
				wariai = (m_Move_ElapsedTime - m_Move_SlowTime) / (m_Move_TravelTime - m_Move_SlowTime * 2);
				ThisOffsetPos = EaseInLinear(wariai) * MoveDistanceOne * LnegthWari_Norm + (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime - (m_Move_TravelTime - m_Move_SlowTime) < m_Move_SlowTime)
			{
				// 9~10なら
				wariai = (m_Move_ElapsedTime - (m_Move_TravelTime - m_Move_SlowTime)) / m_Move_SlowTime;
				ThisOffsetPos = MoveDistance - EaseInSine(1.0 - wariai) * (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime >= m_Move_TravelTime)
			{
				m_Move_Go = false;
				m_Move_Go_DoOnce = false;
			}
			if (m_Move_ElapsedTime >= m_Move_TravelTime)
				SetPosition(m_Move_FinPos);
			else
				SetPosition(m_InitPosition + ThisOffsetPos);
		}
		else
		{
			// 帰りだったら

			MoveingObject_DoOnceCheck();

			if (m_Move_ElapsedTime < m_Move_SlowTime)
			{
				// 0~1なら、1秒で１割進む
				wariai = m_Move_ElapsedTime / m_Move_SlowTime;
				ThisOffsetPos = EaseInSine(wariai) * (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime < m_Move_TravelTime - m_Move_SlowTime)
			{
				// 1~9なら
				wariai = (m_Move_ElapsedTime - m_Move_SlowTime) / (m_Move_TravelTime - m_Move_SlowTime * 2);
				ThisOffsetPos = EaseInLinear(wariai) * MoveDistanceOne * LnegthWari_Norm + (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime - (m_Move_TravelTime - m_Move_SlowTime) < m_Move_SlowTime)
			{
				// 9~10なら
				wariai = (m_Move_ElapsedTime - (m_Move_TravelTime - m_Move_SlowTime)) / m_Move_SlowTime;
				ThisOffsetPos = MoveDistance - EaseInSine(1.0 - wariai) * (MoveDistanceOne * LnegthWari_Slow);
			}
			else if (m_Move_ElapsedTime >= m_Move_TravelTime)
			{
				m_Move_Go = true;
				m_Move_Go_DoOnce = false;
			}

			if (m_Move_ElapsedTime >= m_Move_TravelTime)
				SetPosition(m_InitPosition);
			else
				SetPosition(m_Move_FinPos - ThisOffsetPos);
			
		}

		m_Move_ElapsedTime += Scene::DeltaTime();

	}


	void MoveingObject_DoOnceCheck()
	{
		if (!m_Move_Go_DoOnce)
		{
			m_Move_Go_DoOnce = true;
			m_Move_ElapsedTime = 0;
		}
	}

	void SetMoveUse(bool use)
	{
		m_Move_Use = use;
	}

	// Moveの変数のセット+Useをtrueにする
	void SetMoveState(const Vec3& finpos, const float& traveltime, const float& slowtime, const float& delaytime = 0.0f)
	{
		m_Move_Use = true;
		m_Move_FinPos = finpos;
		m_Move_TravelTime = traveltime;
		m_Move_SlowTime = slowtime;
		m_Move_DelayTime = delaytime;

		m_Move_ElapsedTime = m_Move_TravelTime - m_Move_DelayTime;
		if (delaytime >= 0.001)
		{
			// 帰り道にする。
			m_Move_Go = false;
			m_Move_Go_DoOnce = true;
		}

	}

	//// 歴代の親の数を調べる。再起関数。最初は引数0で渡す。デストロイする前は使えるけど、その時に使いたかったからボツ
	//void GetParentNum(int *parentnum)
	//{

	//	if (m_Parent != nullptr)
	//	{
	//		*parentnum += 1;
	//		m_Parent->GetParentNum(parentnum);
	//	}
	//}

	// 親の数(親の親の親の親～)を返す
	int GetParentNum()
	{
		return m_ParentNum;
	}

	void SetParentNum(int &num)
	{
		m_ParentNum = num;
	}

	// 引数のやつはもとの二はnullptrを設定してある前提。
	// 回転の原点となるゲームオブジェクトがかえる。再起関数
	GameObject* GetIfRotateParent(GameObject* ret_object, GameObject* parent = nullptr)
	{
		if (m_HasRotationSpeed)
		{
			ret_object = this;
			int fef = 45;
			return this;
		}

		if (m_ParentHasRotationSpeed)
		{
			if (m_Parent != nullptr)
			{
				if (!m_Parent->GetDestroyState())
				{
					parent = GetParent();
					ret_object = m_Parent->GetIfRotateParent(ret_object, parent);
					return ret_object;
				}
			}
		}
	}

	// otherをcenterの回転分座標をずらしてあげる
	void CalcRotateforObject(GameObject* center, GameObject* other)
	{

		// うまくいってない！！！


		Vec3 otherpos = other->GetPosition();
		Vec3 centerpos = center->GetPosition();

		double gosa = 0.0001;
		// 回転は１方向限定前提で考える
		double absx = abs(center->GetRotationSpeed().x);
		double absy = abs(center->GetRotationSpeed().y);
		double absz = abs(center->GetRotationSpeed().z);
		if (absx > gosa)
			centerpos.x = otherpos.x;
		if (absy > gosa)
			centerpos.y = otherpos.y;
		if (absz > gosa)
			centerpos.z = otherpos.z;

		Vec3 offset = otherpos - centerpos;



		Vec3 OldRotate = center->GetOldRotation();
		Vec3 NewRotate = OldRotate + center->GetDeltaRotation();


		// オフセット座標で行列を作成。スケールレートの方向分もを考慮
		Mat4x4 Otransmat = Mat4x4::Translate(offset);
		Mat4x4 Ntransmat = Mat4x4::Translate(offset);
		// 現在の回転から行列を作成
		Mat4x4 Orotmat = Mat4x4::RollPitchYaw<double, double, double>(OldRotate.x, OldRotate.y, OldRotate.z);
		Mat4x4 Nrotmat = Mat4x4::RollPitchYaw<double, double, double>(NewRotate.x, NewRotate.y, NewRotate.z);
		// かけ合わせると回転を考慮した行列が出来上がる
		Mat4x4 OOffsetPosmat = Otransmat * Orotmat;
		Mat4x4 NOffsetPosmat = Ntransmat * Nrotmat;

		// 行列から座標の要素だけを取り出す
		Vec3 OOffsetPosition = Vec3(OOffsetPosmat.value.r[3].m128_f32[0], OOffsetPosmat.value.r[3].m128_f32[1], OOffsetPosmat.value.r[3].m128_f32[2]);
		Vec3 NOffsetPosition = Vec3(NOffsetPosmat.value.r[3].m128_f32[0], NOffsetPosmat.value.r[3].m128_f32[1], NOffsetPosmat.value.r[3].m128_f32[2]);

		Vec3 deltapos = OOffsetPosition - NOffsetPosition;
		



		//Vec3 deltapos = OOffsetPosition - offset;



		// otherの座標をずらしてあげる
		other->AddPosition(deltapos);

	}




	//Optional<Vec3>		m_HitedPlayerPosition;
	//Vec3				m_AddDeltaposOnce = Vec3(0, 0, 0);
};

