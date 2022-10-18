#pragma once

class Player : public GameObject
{
private:
	bool m_Jump = false;
	double m_JumpTime = 0;
	double m_JumpStartTime = 0;
	double m_DeltaEaseValue = 0;

	FPSCamera m_fpscamera;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	FPSCamera GetFPSCamera() { return m_fpscamera; }

};
