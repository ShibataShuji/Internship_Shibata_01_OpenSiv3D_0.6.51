#pragma once

static const float GoalRadius = 1.0f;
static const ColorF GoalColor = Linear::Palette::Yellow;
static const ColorF MidColor = Linear::Palette::Blue;

class GoalObject : public GameObject
{
private:
	double m_Time = 0.0;
	bool	m_itGoal = false;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetitGoal(bool setbool)
	{
		m_itGoal = setbool;

		ColorF conecolor = MidColor;
		Collision* col = GetCollisionComponent();
		if (m_itGoal)
			col->SetCollisionColor(GoalColor);
		else
			col->SetCollisionColor(MidColor);
	}
	bool GetitGoal()
	{
		return m_itGoal;
	}

};
