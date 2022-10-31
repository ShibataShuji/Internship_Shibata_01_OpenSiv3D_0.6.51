#pragma once

//#include "Collision_Sub.h"	// Collisionで計算に使う関数を書いている

// 前方宣言
class Collision_Sphere;
class Collision_Box;
class Collision_Capsule;



// 1つのOrientedBoxからつくられた6つの面
struct OrientedBoxSurfaces {

	OrientedBox m_Surfaces[6];
	Vec3		m_Normal[6];
	Vec3		m_Corners[8];
};

// 関数宣言
void CreateOrientedBoxSurfaces(const OrientedBox* box, OrientedBoxSurfaces* ret_surfaces);
void Sphere_HitOneSurface(const Sphere* sphere, const OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp);
Array<int> Sphere_HitTwoSurface(Sphere* sphere, OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp);
Array<int> Sphere_HitThreeSurface(Sphere* sphere, OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp);
void Sphere_Box_GetHitSurfaceNormal(Sphere* sphere, const OrientedBox* box, Array<Vec3>* ret_normal, int* ret_hitnum, Vec3* ret_cp);
void CalulateDivisionToHit_Sphere_Box(const Vec3& oldpos, int divmin, int divmax, const Vec3& oneValue, const Sphere* sphere, const OrientedBox* box, int* ret_hitdivnum, Vec3* ret_hitpos);



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
};


// レスポンスオブジェクトの種類
enum class ResponseObject
{
	BlocksPawn,
	EnemysPawn,
	PlayersPawn,
	ItemsPawn,
	PlayerBullet,
	PlayerGround
};




class Collision : public Component
{
private:

	// コリジョンの可視性
	bool		m_Visibility = true;
	float		m_Alfa = 1.0f;			// コリジョンの形の透明度
	ColorF		m_ColorF = Linear::Palette::Aqua;

	// Blockの時、true:衝突したところで止まる。	false:壁ずりさせる
	bool		m_HittoStop = false;


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
		{ ResponseObject::BlocksPawn, ResponseType::Ignore },
		{ ResponseObject::EnemysPawn, ResponseType::Ignore },
		{ ResponseObject::PlayersPawn, ResponseType::Ignore },
		{ ResponseObject::ItemsPawn, ResponseType::Ignore },
		{ ResponseObject::PlayerBullet, ResponseType::Ignore },
		{ ResponseObject::PlayerGround, ResponseType::Ignore },
	};
	// 動的にしたい場合、こんな風に追加すればOK
	//table.emplace(U"Yellow", 5);

	// 親を考慮しないオフセット値
	Vec3	m_OffsetPosition = Vec3(0, 0, 0);
	Vec3	m_OffsetRotation = Vec3(0, 0, 0);
	Quaternion	m_OffsetQuaternion = Quaternion::Identity();
	Vec3	m_OffsetSize = Vec3(1, 1, 1);

	// 親も考慮した計算後の値
	Vec3	m_Position = Vec3(0, 0, 0);
	Vec3	m_Rotation = Vec3(0, 0, 0);
	Quaternion	m_Quaternion = Quaternion::Identity();
	Vec3	m_Size = Vec3(1, 1, 1);


	// 1フレーム前の値
	Vec3	m_OldPosition = Vec3(0, 0, 0);
	Vec3	m_OldRotation = Vec3(0, 0, 0);

	// 1フレーム前の値からの変化量
	Vec3	m_DeltaPosition = Vec3(0, 0, 0);
	Vec3	m_DeltaRotation = Vec3(0, 0, 0);



public:

	// 親クラスのコンストラクタをやってくれる。
	using Component::Component;

	void SetVisibility(bool visibility) { m_Visibility = visibility; }
	bool GetVisibility() { return m_Visibility; }

	void SetOffsetPosition(Vec3 position) { m_OffsetPosition = position; }
	void SetOffsetRotation(Vec3 rotation)
	{
		m_OffsetRotation = rotation;
		Quaternion Qua = Quaternion::Identity();
		m_OffsetQuaternion = Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	}
	void SetOffsetm_Quaternion(Quaternion quaternion) { m_OffsetQuaternion = quaternion; }
	void SetOffsetSize(Vec3 size) { m_OffsetSize = size; }
	void SetOffsetSize(Vec2 size) { m_OffsetSize.x = size.x; m_OffsetSize.y = size.y; m_OffsetSize.z = size.x; }
	void SetOffsetSize(float size) { m_OffsetSize.x = size; m_OffsetSize.y = size, m_OffsetSize.z = size;}
	Vec3 GetPosition() { return m_Position; }
	void SetPosition(Vec3 pos) { m_Position = pos; }
	Vec3 GetRotation() { return m_Rotation; }
	Quaternion GetQuaternion() { return m_Quaternion; }
	Vec3 GetSize() { return m_Size; }

	void SetHittoStop(bool hittostop) { m_HittoStop = hittostop; }
	bool GetHittoStop() { return m_HittoStop; }

	Vec3 GetOldPosition() { return m_OldPosition; }
	Vec3 GetOldRotation() { return m_OldRotation; }

	Vec3 GetDeltaPosition() { return m_DeltaPosition; }
	Vec3 GetDeltaRotation() { return m_DeltaRotation; }

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

	float GetAlfa() { return m_Alfa; }
	void SetAlfa(float alfa) { m_Alfa = alfa; }

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
		//Component::Draw();
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
	bool BoxSphereBlock_Rotation(Collision* ColB_Box, Collision* ColA_Sphere);



	static void CalulateDivisionToHit_RotateBox_Sphere(Collision* BaseBoxCol, const Vec3& oldrotate, int divmin, int divmax, const Vec3& oneValue, const Sphere* sphere, int* ret_hitdivnum);


	Quaternion GetQuaternionForRotation()
	{
		Quaternion Qua = Quaternion::Identity();	// 演算用に基本形のクォータニオンをを作成
		m_Quaternion = Qua.RollPitchYaw<double, double, double>(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		return m_Quaternion;
	}

};
