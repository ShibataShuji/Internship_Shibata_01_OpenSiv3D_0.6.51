#pragma once


class Collision_Box : public Collision
{
private:
	OrientedBox m_OrientedBox;
	OrientedBox m_OldOrientedBox;

public:

	// 親クラスのコンストラクタをやってくれる。
	using Collision::Collision;

	OrientedBox* GetOrientedBox() { return &m_OrientedBox; }
	OrientedBox* GetOldOrientedBox() { return &m_OldOrientedBox; }

	void Init() override
	{
		// 親
		Collision::Init();

		// 自分がどのコリジョンの形なのか
		m_CollisionType = CollisionType::Box;

		m_OrientedBox.setPos(m_Position);
		m_OrientedBox.setOrientation(GetQuaternionForRotation());
		m_OrientedBox.setSize(m_Size);
	}

	void Uninit() override
	{
		// 親
		Collision::Uninit();
	}


	void Update() override;


	void Draw() override;
	// 縁取りの描写
	void DrawHemming(const OrientedBox* orientedbox);

	void UpdateCollisionState() override;

};

