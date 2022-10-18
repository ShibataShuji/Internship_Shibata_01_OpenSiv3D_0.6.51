#pragma once


// 前方宣言
class Collision_Sphere;
class Collision_Box;
class Collision_Capsule;

// もつことのできるコリジョンの種類
enum class CollisionType
{
	Sphere,
	Box,
	Capsule
};

// レスポンスタイプの種類
enum class ResponseType
{
	Ignore,
	Overlap,
	Block,
	NotSet
};


// レスポンスオブジェクトの種類
enum class ResponseObject
{
	BlocksPawn,
	EnemysPawn,
	PlayersPawn,
	ItemsPawn
};




class Collision : public Component
{
private:

	// コリジョンの可視性
	bool		m_Visibility = true;
	ColorF		m_ColorF = Linear::Palette::Aqua;


protected:

	// 自分がどのコリジョンの形なのか
	CollisionType	m_CollisionType;// = CollisionType::Sphere;初期設定は継承先で行う

	// 自分がどのレスポンスオブジェクトなのか
	ResponseObject	m_ResponseObject = ResponseObject::BlocksPawn;

	// 他のものに衝突したときにそのレスポンスオブジェクトに対する反応のリスト。ハッシュテーブルの構築
	HashTable<ResponseObject, ResponseType> m_ResponseTable =
	{
		// レスポンスオブジェクトの種類分作成する。今回はエンジン作るわけじゃないので静的でOK。
		// むしろ途中で追加されたりしてちゃんと検索に引っかからない可能性出るからここでセットする以外触らない。
		{ ResponseObject::BlocksPawn, ResponseType::NotSet },
		{ ResponseObject::EnemysPawn, ResponseType::NotSet },
		{ ResponseObject::PlayersPawn, ResponseType::NotSet },
		{ ResponseObject::ItemsPawn, ResponseType::NotSet },
	};
	// 動的にしたい場合、こんな風に追加すればOK
	//table.emplace(U"Yellow", 5);

	// 親を考慮しないオフセット値
	Vec3	m_OffsetPosition = Vec3(0, 0, 0);
	Vec3	m_OffsetRotation = Vec3(0, 0, 0);
	Vec3	m_OffsetSize = Vec3(1, 1, 1);

	// 親も考慮した計算後の値
	Vec3	m_Position = Vec3(0, 0, 0);
	Vec3	m_Rotation = Vec3(0, 0, 0);
	Vec3	m_Size = Vec3(1, 1, 1);


	// 1フレーム前の値
	Vec3	m_DeltaPosition = Vec3(0, 0, 0);



public:

	// 親クラスのコンストラクタをやってくれる。
	using Component::Component;

	void SetOffsetPosition(Vec3 position) { m_OffsetPosition = position; }
	void SetOffsetRotation(Vec3 rotation) { m_OffsetRotation = rotation; }
	void SetOffsetSize(Vec3 size) { m_OffsetSize = size; }
	void SetOffsetSize(Vec2 size) { m_OffsetSize.x = size.x; m_OffsetSize.y = size.y; m_OffsetSize.z = size.x; }
	void SetOffsetSize(float size) { m_OffsetSize.x = size; m_OffsetSize.y = size, m_OffsetSize.z = size;}
	Vec3 GetPosition() { return m_Position; }
	Vec3 GetRotation() { return m_Rotation; }
	Vec3 GetSize() { return m_Size; }

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType CollisionType) { m_CollisionType = CollisionType; }
	ResponseObject GetResponseObject() { return m_ResponseObject; }
	void SetResponseObject(ResponseObject ResponseObject) { m_ResponseObject = ResponseObject; }
	HashTable<ResponseObject, ResponseType> GetResponseTable() { return m_ResponseTable; }
	void SetResponseTableOneItem(ResponseObject ResObj, ResponseType ResType)
	{
		for (auto it = m_ResponseTable.begin(); it != m_ResponseTable.end(); ++it)
		{
			if (it->first == ResObj)
			{
				it->second = ResType;
				break;
			}
		}
	}

	ColorF GetColor() { return m_ColorF; }
	void SetCollisionColor(ColorF colorF) { m_ColorF = colorF; }

	virtual void Init() override
	{
		Component::Init();

		// 親
		UpdateCollisionState();
	}

	virtual void Uninit() override
	{

		Component::Uninit();
	}


	virtual void Update() override;


	virtual void Draw() override
	{
		Component::Draw();
	}

	virtual void UpdateCollisionState();


	// 自分と相手のレスポンスがどうなのかを返す。お互いに同じレスポンスじゃないと反応しない
	ResponseType CheckResponseOther(Collision* othercollision)
	{
		// それぞれのオブジェクトタイプの取得
		ResponseObject SelfResponseObject = GetResponseObject();
		ResponseObject OtherResponseObject = othercollision->GetResponseObject();

		auto hashtable = GetResponseTable();
		ResponseType aaa = hashtable[ResponseObject::BlocksPawn];

		// お互いに対するレスポンスがどうなのか
		ResponseType SelfResponse = GetResponseTable()[OtherResponseObject];
		ResponseType OtherResponse = othercollision->GetResponseTable()[SelfResponseObject];

		// お互いが違ったらIgnoreを返す
		if (SelfResponse != OtherResponse)
			return ResponseType::Ignore;

		// お互いが反応するならそれを返す(同じなのでselfとotherどちらを返しても一緒)
		return SelfResponse;
	}

	// Overlap
	bool SphereSphereOverlap(Collision* ColA, Collision* ColB);
	bool SphereBoxOverlap(Collision* ColA_Sphere, Collision* ColB_Box);
	bool BoxBoxOverlap(Collision* ColA, Collision* ColB);

	// Block
	bool SphereBoxBlock(Collision* ColA_Sphere, Collision* ColB_Box);





	Quaternion GetQuaternion()
	{
		Quaternion Qua = Quaternion::Identity();	// 演算用に基本形のクォータニオンをを作成

		return Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	}

};




//// 最接近点を求める関数
//static void ClosestPtPointOBB(const Vec3& point, const Vec3& box_center, const Vec3 *box_rotnormal, const float* box_axissize,  Vec3& retvec)
//{
//	Vec3 d = point - box_center;	// OBB->ポイント のベクトル
//	retvec = box_center;
//	float dist;
//	for (int i = 0; i < 3; i++)
//	{
//		dist = d.dot(box_rotnormal[i]);
//		if (dist > box_axissize[i])						// 内積は符号がつく
//		{
//			dist = box_axissize[i];
//		}
//		if (dist < -box_axissize[i])
//		{
//			dist = -box_axissize[i];
//		}
//		retvec += dist * box_rotnormal[i];
//	}
//}
