#pragma once


class GameObject
{
protected:	// アクセス指定子

	bool				m_Destroy = false;

	Vec3				m_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Rotation = Vec3(0.0f, 0.0f, 0.0f);
	Quaternion			m_Quaternion = Quaternion::Identity();
	//Vec3				m_Scale = Vec3(1.0f, 1.0f, 1.0f);
	Vec3				m_ScaleRate = Vec3(1.0f, 1.0f, 1.0f);

	Vec3				m_Delta_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3				m_Velocity = Vec3(0.0f, 0.0f, 0.0f);


	Array<CComponent*>	m_ComponentList;
	Array<String>		m_ComponentNameList;
	Array<GameObject*>	m_Child;


	// Collisionコンポーネントを1つでも持っているときに使うよう変数
	Array<GameObject*>	m_Collision_HitObjectList;
	Array<Vec3>			m_Collision_HitPositionList;
	Array<GameObject*>	m_Collision_OverlapObjectList;
	Array<Vec3>			m_Collision_OverlapPositionList;

public:

	// 本当はモデルとコリジョンコンポーネントでやるけどテスト用
	Vec3 m_Size;

	GameObject() {}


	virtual ~GameObject()
	{
		for (auto c : m_ComponentList)
		{
			if (c != nullptr)
				delete c;
		}
		m_ComponentList.clear();

		//for (auto c : m_ComponentNameList)	// これはクラスじゃないのでdeleteする必要ない
		//	delete c;
		m_ComponentNameList.clear();

		for (auto c : m_Child)
			delete c;
		m_Child.clear();
	}


	virtual void Init()	// 純粋仮想関数
	{
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
		m_Delta_Position = m_Position;

	}


	virtual void Draw()
	{
		for (auto c : m_ComponentList)
			c->Draw();
	}


	// コンポーネントのアップデート
	virtual void ComponentUpdate()
	{
		//// コリジョン系の変数のリセット
		ResetCollisionHitArray();

		for (int i = 0; i < UpdatePriority_Max; i++)
		{
			for (auto comp : m_ComponentList)
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
		m_Collision_OverlapObjectList.clear();
		m_Collision_OverlapPositionList.clear();
	}



	void AddPosition(Vec3 AddPosition) { m_Position += AddPosition; }
	void SetPosition(Vec3 Position) { m_Position = Position; }
	void SetPosition_x(float x) { m_Position.x = x; }
	void SetPosition_y(float y) { m_Position.y = y; }
	void SetPosition_z(float z) { m_Position.z = z; }
	Vec3 GetPosition() { return m_Position; }

	Vec3 GetDelataPosition() { return m_Delta_Position; }

	void SetRotation(Vec3 rotation) { m_Rotation = rotation; }
	Vec3 GetRotation() { return m_Rotation; }

	void SetQuaternion(Quaternion quaternion) { m_Quaternion = quaternion; }
	Quaternion GetQuaternion() { return m_Quaternion; }

	/*void SetScale(Vec3 scale) { m_Scale = scale; }
	Vec3 GetScale() { return m_Scale; }*/
	void SetScaleRate(Vec3 setscalerate) { m_ScaleRate = setscalerate; }
	Vec3 GetScaleRate() { return m_ScaleRate; }

	Vec3 GetVelocity() { return m_Velocity; }
	void SetVelocity(Vec3 Velocity) { m_Velocity = Velocity; }
	void SetVelocity_x(float x) { m_Velocity.x = x; }
	void SetVelocity_y(float y) { m_Velocity.y = y; }
	void SetVelocity_z(float z) { m_Velocity.z = z; }



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
		m_ComponentNameList.push_back("noname");

		return ccomponent;
	}
	// 名前つけるバージョン
	template <typename T>
	T* AddComponent(String name)
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
	T* GetComponentWithName(String name)
	{
		int itrCount = 0;
		for (auto cName : m_ComponentNameList)
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

	Array<CComponent*> GetComponentList()
	{
		return m_ComponentList;
	}

	template <typename T>
	bool HasComponent()
	{
		for (auto c : m_ComponentList)
		{
			if (typeid(*c) == typeid(T))
			{
				return true;
			}
		}
		return false;
	}

	int GetComponentNum()
	{
		int count = 0;
		for (auto Comp : m_ComponentList)
		{
			count++;
		}
		return count;
	}

	void DestroyComponent(int compCount)
	{


		CComponent* temp = nullptr;

		int count = 0;
		for (auto Comp : m_ComponentList)
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

		Array<CComponent*> templist;
		templist = m_ComponentList;

		m_ComponentList.clear();

		for (auto tempc : templist)
		{
			tempc->Uninit();
		}
		return;
	}







	// Collision用
	void Collision_AddHitObject(GameObject* hitobject, Vec3 hitpos)
	{
		m_Collision_HitObjectList.push_back(hitobject);
		m_Collision_HitPositionList.push_back(hitpos);
	}
	void Collision_AddOverlapObject(GameObject* overlapobject, Vec3 overlappos)
	{
		m_Collision_OverlapObjectList.push_back(overlapobject);
		m_Collision_OverlapPositionList.push_back(overlappos);
	}


};

