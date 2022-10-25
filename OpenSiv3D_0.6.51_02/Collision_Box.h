#pragma once


class Collision_Box : public Collision
{
private:
	OrientedBox m_OrientedBox;

public:

	// 親クラスのコンストラクタをやってくれる。
	using Collision::Collision;

	OrientedBox* GetOrientedBox() { return &m_OrientedBox; }

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


	void Draw() override
	{
		// 親
		Collision::Draw();

		m_OrientedBox.draw(GetColor());
	}

	void UpdateCollisionState() override;

};

