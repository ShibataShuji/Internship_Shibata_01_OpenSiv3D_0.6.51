#pragma once



class SkyRender
{
private:
	SkyRender();

	// 宣言
	static Sky* m_Sky;
	static double m_SkyTime;
	static double m_SkyAddTime;
	static double m_SkyAddOrientation;
	static bool m_ChangeTime;		// 時間が進むか、時間は進まないまま雲だけ動くか
	

public:
	static void InitSky();
	static void DrawSky();
	static void SetParm();
	static void InitParm();
	static void UpdateTimeAndOrientation();
	static void SetChangeTime(bool change);



};
