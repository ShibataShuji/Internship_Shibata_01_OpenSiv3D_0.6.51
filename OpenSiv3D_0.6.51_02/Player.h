#pragma once


static const double maxjumptime = 0.6;	// ジャンプの時間
static const float maxheight = 4.0f;		// 最大到達点
static const int16 maxBulletNum = 3;		// 存在できる最大の球数

static const float PlayerRadius = 0.3f;
static const int16 PlayerMaxBullets = 5;

class Player : public GameObject
{
private:
	bool m_Jump = false;
	double m_JumpTime = 0;
	double m_JumpStartTime = 0;
	double m_DeltaEaseValue = 0;
	double m_JumpCoolTime = 0;
	bool m_HitGround = false;
	bool m_LandingOnce = false;	// 着地した瞬間をとる

	Vec3 m_ShadowPosition = Vec3(0, 0, 0);

	Array<GameObject*> m_Bullets;

public:

	// デバッグモード
	bool m_DebugMode = false;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void GetShadowPosition();

	void AddBullet(GameObject* bullet);
	void ResetBullets();
	void DeleteFirstBullet();
	void DeleteBullet(GameObject* bullet);
	void BulletsNumCheck();
	void BulletChildSetColor(GameObject* bullet, const ColorF& setcolor);

	void Movement();

};
