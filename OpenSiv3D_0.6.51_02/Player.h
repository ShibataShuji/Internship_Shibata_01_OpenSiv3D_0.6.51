#pragma once


static const double maxjumptime = 0.6;	// ジャンプの時間
static const float maxheight = 4.0f;		// 最大到達点

class Player : public GameObject
{
private:
	bool m_Jump = false;
	double m_JumpTime = 0;
	double m_JumpStartTime = 0;
	double m_DeltaEaseValue = 0;
	double m_JumpCoolTime = 0;
	bool m_HitGround = false;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};
