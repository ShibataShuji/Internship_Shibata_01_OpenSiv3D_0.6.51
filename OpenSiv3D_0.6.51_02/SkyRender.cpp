#include "stdafx.h"

// 定義
Sky* SkyRender::m_Sky = nullptr;
double SkyRender::m_SkyTime = 0.5;
double SkyRender::m_SkyAddTime = 0.005;
double SkyRender::m_SkyAddOrientation = 0.015;
bool SkyRender::m_ChangeTime = true;


void SkyRender::InitSky()
{
	if (m_Sky != nullptr)
	{
		delete m_Sky;
		m_Sky = nullptr;
	}

	m_Sky = new Sky;

	InitParm();
}

void SkyRender::InitParm()
{
	// 初期設定
	m_Sky->cloudiness = 0.2; // 0.0, 1.0
	m_Sky->cloudScale = 0.7; // 0.0, 2.0
	m_Sky->cloudPlaneHeight = 1500.0; //  20.0, 6000.0
	//m_Sky->cloudOrientation = Math::Pi; // 0.0, 360Math::TwoPi	// 空の動き。Timeを変えたくないが空を動かしたいときはこっちを使う。
	//m_Sky->fogHeightSky = 0.5; // 0.0, 1.0		// Timeで自動的に調整される
	//m_Sky->starBrightness = 0.5; // 0.0, 1.0		// Timeで自動的に調整される
	m_Sky->starBrightnessFactor = 1.0; // 0.0, 1.0
	m_Sky->starSaturation = 0.8; // 0.0, 1.0

	m_Sky->sunEnabled = true;
	m_Sky->cloudsEnabled = true;
	m_Sky->cloudsLightingEnabled = true;

	m_SkyTime = 0.5;
}


void SkyRender::DrawSky()
{
	// 時間を進める
	UpdateTimeAndOrientation();


	// [天空レンダリング]
	{
		const double time0_2 = Math::Fraction(m_SkyTime * 0.5) * 2.0;
		const double halfDay0_1 = Math::Fraction(m_SkyTime);
		const double distanceFromNoon0_1 = Math::Saturate(1.0 - (Abs(0.5 - halfDay0_1) * 2.0));
		const bool night = (1.0 < time0_2);
		const double tf = EaseOutCubic(distanceFromNoon0_1);
		const double tc = EaseInOutCubic(distanceFromNoon0_1);
		const double starCenteredTime = Math::Fmod(time0_2 + 1.5, 2.0);

		// set sun
		{
			const Quaternion q = (Quaternion::RotateY(halfDay0_1 * 180_deg) * Quaternion::RotateX(50_deg));
			const Vec3 sunDirection = q * Vec3::Right();
			const ColorF sunColor{ 0.1 + Math::Pow(tf, 1.0 / 2.0) * (night ? 0.1 : 0.9) };

			Graphics3D::SetSunDirection(sunDirection);
			Graphics3D::SetSunColor(sunColor);
			Graphics3D::SetGlobalAmbientColor(ColorF{ m_Sky->zenithColor });
		}

		// set m_Sky color
		{
			if (night)
			{
				m_Sky->zenithColor = ColorF{ 0.05, 0.05, 0.3 }.lerp(ColorF{ 0.1, 0.1, 0.15 }, tf);
				m_Sky->horizonColor = ColorF{ 0.1, 0.1, 0.20 }.lerp(ColorF{ 0.1, 0.1, 0.2 }, tf);
			}
			else
			{
				m_Sky->zenithColor = ColorF{ 0.1, 0.05, 0.4 }.lerp(ColorF{ 0.15, 0.24, 0.56 }, tf);
				m_Sky->horizonColor = ColorF{ 0.15, 0.05, 0.2 }.lerp(ColorF{ 0.3, 0.4, 0.5 }, tf);
			}
		}

		// set parameters
		{
			m_Sky->starBrightness = Math::Saturate(1.0 - Pow(Abs(1.0 - starCenteredTime) * 1.8, 4));
			m_Sky->fogHeightSky = (1.0 - tf);
			m_Sky->cloudColor = ColorF{ 0.02 + (night ? 0.0 : (0.98 * tc)) };
			m_Sky->sunEnabled = (not night);
			m_Sky->cloudTime = m_SkyTime * m_Sky->cloudScale * 40.0;
			m_Sky->starTime = m_SkyTime;
		}

		m_Sky->draw();
	}
}


void SkyRender::SetParm()
{


	//Rect{ 20, 20, 480, 76 }.draw();
	//SimpleGUI::GetFont()(U"zenith:").draw(28, 24, ColorF{ 0.11 });
	//Rect{ 100, 26, 28 }.draw(m_Sky->zenithColor.gamma(2.2)).drawFrame(1, 0, ColorF{ 0.5 });
	//SimpleGUI::GetFont()(U"horizon:").draw(148, 24, ColorF{ 0.11 });
	//Rect{ 230, 26, 28 }.draw(m_Sky->horizonColor.gamma(2.2)).drawFrame(1, 0, ColorF{ 0.5 });
	//SimpleGUI::GetFont()(U"cloud:").draw(276, 24, ColorF{ 0.11 });
	//Rect{ 340, 26, 28 }.draw(m_Sky->cloudColor.gamma(2.2)).drawFrame(1, 0, ColorF{ 0.5 });
	//SimpleGUI::GetFont()(U"sun:").draw(386, 24, ColorF{ 0.11 });
	//Rect{ 430, 26, 28 }.draw(Graphics3D::GetSunColor().gamma(2.2)).drawFrame(1, 0, ColorF{ 0.5 });
	//SimpleGUI::GetFont()(U"sunDir: {:.2f}   cloudTime: {:.1f}"_fmt(Graphics3D::GetSunDirection(), m_Sky->cloudTime)).draw(28, 60, ColorF{ 0.11 });

	//m_Sky->cloudiness = 0.2; // 0.0, 1.0
	//m_Sky->cloudScale = 0.7; // 0.0, 2.0
	//m_Sky->cloudPlaneHeight = 1500.0; //  20.0, 6000.0
	////m_Sky->cloudOrientation = Math::Pi; // 0.0, 360Math::TwoPi	// 空の動き。Timeを変えたくないが空を動かしたいときはこっちを使う。
	////m_Sky->fogHeightSky = 0.5; // 0.0, 1.0		// Timeで自動的に調整される
	////m_Sky->starBrightness = 0.5; // 0.0, 1.0		// Timeで自動的に調整される
	//m_Sky->starBrightnessFactor = 1.0; // 0.0, 1.0
	//m_Sky->starSaturation = 0.8; // 0.0, 1.0

	//m_Sky->sunEnabled = true;
	//m_Sky->cloudsEnabled = true;
	//m_Sky->cloudsLightingEnabled = true;
}


void SkyRender::UpdateTimeAndOrientation()
{
	if (m_ChangeTime)
	{
		m_SkyTime += m_SkyAddTime * Scene::DeltaTime();;
		if (m_SkyTime > 4.0)
			m_SkyTime = -2.0;
		//Print << U"m_SkyTime: {}"_fmt(m_SkyTime);

	}
	else
	{
		m_Sky->cloudOrientation += m_SkyAddOrientation * Scene::DeltaTime();;
		if (m_Sky->cloudOrientation > 360.0)
			m_Sky->cloudOrientation = 0.0;
	}
}


// 時間が進むか、時間は進まないまま雲だけ動くか
void SkyRender::SetChangeTime(bool change)
{
	m_ChangeTime = change;
}
