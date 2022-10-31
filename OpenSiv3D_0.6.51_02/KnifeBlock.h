#pragma once

static const Vec3 KnifeBlock_Size = Vec3(6, 1.3, 6);
static const ColorF KnifeBlock_DefColor = Linear::Palette::Aqua;
static const ColorF KnifeBlock_HighlightColor = Linear::Palette::Red;
//static const ColorF KnifeBlock_HighlightColor = { 1.0,0.0,0.0,0.4 };

class KnifeBlock : public GameObject
{
private:
	float m_Height = 0.0;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetHeight(float height) { m_Height = height; }

};
