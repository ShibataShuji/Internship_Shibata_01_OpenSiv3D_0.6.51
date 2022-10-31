#pragma once

static const float KnifeBulletSize = 0.3f;
static const ColorF KnifeBulletColor = Linear::Palette::Aquamarine;

class KnifeBullet : public GameObject
{
private:
	bool m_DoOnce = true;
	double m_ElapsedTime = 0.0;
	double m_IntervalTime = 1.1;
	Optional<Vec3> m_Spherepos;	// 座標指定で衝突判定をとる場合使う
public:
	void Init() override;
	void Uninit() override;
	void EndKnifeBullet();
	void Update() override;
	void Draw() override;

	void SetSpherepos(Vec3 &pos)
	{
		m_Spherepos = pos;
	}

};
