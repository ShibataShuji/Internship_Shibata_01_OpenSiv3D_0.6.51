#pragma once

static const float MidRadius = 1.0f;

class MidObject : public GameObject
{
private:
	double m_Time = 0.0;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};
