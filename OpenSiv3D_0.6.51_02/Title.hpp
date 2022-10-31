# pragma once

static const int16 StageMaxNum = 5;

// タイトルシーン
class Title : public SceneManager<State, GameData>::Scene
{
private:

	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	BasicCamera3D m_Camera = BasicCamera3D{ Scene::Size(), 30_deg, Vec3{0, 16, -32}, Vec3{0, 0, 1} };
	Vec3 m_EyePos = Vec3(0, 0, 0);
	Vec3 m_forcusPos = Vec3(0, 0, 0);

	Rect m_startButton{ Arg::center = Scene::Center(), 300, 60 };
	Transition m_startTransition{ 0.4s, 0.2s };

	//Rect m_rankingButton{ Arg::center = Scene::Center().movedBy(0, 100), 300, 60 };
	//Transition m_rankingTransition{ 0.4s, 0.2s };

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(0, 150), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };


	// ステージセレクト
	Rect m_StageSelectButton[StageMaxNum];
	Transition m_StageSelectTransition[StageMaxNum];

	Rect m_backtitleButton{ Arg::center = Scene::Center().movedBy(-300, 400), 300, 60 };
	Transition m_backtitleTransition{ 0.4s, 0.2s };


	//int16	m_Step = 0;
	int16	m_tStep = -1;
	float	m_StepElapsedTime = 0.0;

public:

	Title(const InitData& init);

	void update() override;

	void draw() const override;

	void SetStep(const int16 toStep);
	void ChangeStepUpdate();


};
