#pragma once


class Collision_Sphere : public Collision
{
private:
	Sphere m_Sphere;

public:

	// 親クラスのコンストラクタをやってくれる。
	using Collision::Collision;

	Sphere* GetSphere() { return &m_Sphere; }

	void Init() override
	{
		// 親
		Collision::Init();

		// 自分がどのコリジョンの形なのか
		m_CollisionType = CollisionType::Sphere;

		m_Sphere.setPos(m_Position);
		m_Sphere.setR(m_Size.x);
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

		m_Sphere.draw(GetColor());
	}

	void UpdateCollisionState() override;

};

