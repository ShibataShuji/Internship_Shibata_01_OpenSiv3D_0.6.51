#pragma once


class GameObject
{
protected:	// アクセス指定子

	bool				m_Destroy = false;

	// 初期の座標等。データの保存の時にも使う
	Vec3				m_InitPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_InitRotation = Vec3(0.0f, 0.0f, 0.0f);
	Quaternion			m_InitQuaternion = Quaternion::Identity();
	Vec3				m_InitScaleRate = Vec3(1.0f, 1.0f, 1.0f);

	// 実際に処理計算で使う座標等
	Vec3				m_Position = m_InitPosition;
	Vec3				m_Rotation = m_InitRotation;
	Quaternion			m_Quaternion = Quaternion::Identity();
	//Vec3				m_Scale = Vec3(1.0f, 1.0f, 1.0f);
	Vec3				m_ScaleRate = m_InitScaleRate;

	Vec3				m_Old_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Velocity = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_RotationSpeed = Vec3(0.0f, 0.0f, 0.0f);

	String				m_Name = U"noname";

	// 子供になった瞬間の親と子供の座標などを保存する
	Vec3				m_ParentStartPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_ParentStartRotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_ParentStartScaleRate = Vec3(1.0f, 1.0f, 1.0f);

	Vec3				m_OffsetPosition = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_OffsetRotation = Vec3(0.0f, 0.0f, 0.0f);
	Quaternion			m_OffsetQuaternion = Quaternion::Identity();
	Vec3				m_OffsetScaleRate = Vec3(1.0f, 1.0f, 1.0f);
	Vec3				m_OffsetScaleRateAdjuste = Vec3(1.0f, 1.0f, 1.0f);



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
		
		for (auto comp : m_ComponentList)
		{
			if (comp != nullptr)
				delete comp;
		}
		m_ComponentList.clear();

		m_ComponentNameList.clear();

		for (auto child : m_Child)
			delete child;
		m_Child.clear();
	}


	virtual void Init()	// 純粋仮想関数
	{
		// 継承先で親関数のこれ呼ぶの面倒なので
		// コンストラクタでやった方がいいのかも
	}


	virtual void Uninit()
	{
		for (auto c : m_ComponentList)
			c->Uninit();

		for (auto c : m_Child)
			c->Uninit();
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
		m_Old_Position = m_Position;

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

	String GetName() { return m_Name; }
	void SetName(const String& name) { m_Name = name; }

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
		Quaternion Qua = Quaternion::Identity();
		m_InitQuaternion = Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		m_Quaternion = m_InitQuaternion;
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

	void SetRotation(const Vec3& rotation)
	{
		m_Rotation = rotation;
		Quaternion Qua = Quaternion::Identity();
		m_Quaternion = Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	}
	Vec3 GetRotation() { return m_Rotation; }
	void AddRotation(const Vec3& rotation) { m_Rotation += rotation; }

	void SetQuaternion(const Quaternion& quaternion) { m_Quaternion = quaternion; }
	Quaternion GetQuaternion() { return m_Quaternion; }
	Quaternion GetQuaternionForRotation()
	{
		Quaternion Qua = Quaternion::Identity();	// 演算用に基本形のクォータニオンをを作成

		m_Quaternion = Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		return m_Quaternion;
	}

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
	void SetRotationSpeed(const Vec3& rotationspeed) { m_RotationSpeed = rotationspeed; }
	void AddRotationSpeed(const Vec3& rotationspeed) { m_RotationSpeed += rotationspeed; }

	void SetDestroy() { m_Destroy = true; }
	bool GetDestroyState()
	{
		if (this == nullptr)
			return true;
		return m_Destroy;
	}

	Vec3 GetForward()	// 前方向ベクトル
	{
		Mat4x4 rot = Mat4x4::Identity();
		rot.rollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 forward{};
		forward.x = rot.value.r[3].m128_f32[1];
		forward.y = rot.value.r[3].m128_f32[2];
		forward.z = rot.value.r[3].m128_f32[3];

		return forward;
	}

	Vec3 GetRight()	// 右方向ベクトル
	{
		Mat4x4 rot = Mat4x4::Identity();
		rot.rollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 right;
		right.x = rot.value.r[1].m128_f32[1];
		right.y = rot.value.r[1].m128_f32[2];
		right.z = rot.value.r[1].m128_f32[3];

		return right;
	}

	Vec3 GetUp()	// 上方向ベクトル
	{
		Mat4x4 rot = Mat4x4::Identity();
		rot.rollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vec3 up;
		up.x = rot.value.r[2].m128_f32[1];
		up.y = rot.value.r[2].m128_f32[2];
		up.z = rot.value.r[2].m128_f32[3];

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
			// 取り急ぎ。現状コリジョンしかないので
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
		gameobject->m_ParentStartPosition = GetPosition();
		gameobject->m_ParentStartRotation = GetRotation();
		gameobject->m_ParentStartScaleRate = GetScaleRate();

		gameobject->m_OffsetPosition = gameobject->GetPosition() - GetPosition();
		gameobject->m_OffsetRotation = gameobject->GetRotation() - GetRotation();
		//gameobject->m_OffsetQuaternion = gameobject->GetQuaternion();
		//gameobject->m_OffsetScaleRate = gameobject->GetScaleRate() * GetScaleRate();
		gameobject->m_OffsetScaleRate = gameobject->GetScaleRate() / GetScaleRate();	// ScaleRateは逆数を入れて、最終的な結果を現在と変わらないようにしておく
		// その瞬間の親の大きさを基準にスケールを調整するために、かけて1.0になるような値を取得しておく。
		gameobject->m_OffsetScaleRateAdjuste = Vec3(1.0, 1.0, 1.0) / gameobject->GetScaleRate();

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
		return m_Parent;
	}





	// Collision用
	void Collision_AddHitObject(GameObject* hitobject, const Vec3& hitpos, const Vec3& hitnormal)
	{
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
		m_Collision_OverlapObjectList.push_back(overlapobject);
		//m_Collision_OverlapPositionList.push_back(overlappos);
	}


};

