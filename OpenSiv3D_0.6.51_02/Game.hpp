# pragma once



// --------------------------------------------関数宣言
void StandbyGameDraw_String(const String& string, const Vec2 &pos, const float &size);


// もつことのできるコリジョンの種類
enum class GameStep
{
	NowGame,
	Standby,
	Result,
	Pause
};


// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
private:

	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	// メインとなるオブジェクト。
	Player* m_Player;
	GoalObject* m_GoalObject;

	Vec3		  m_EyePosition{ 0, 2, -16 };

	bool		m_UpdateFirst = true;	// 1回目のアップデートだったら

	double		m_SceneElapsedTime = 0.0;
	double		m_ResultElapsedTime = 0.0;
	GameStep	m_GameStep = GameStep::Standby;

	Stopwatch	m_Stopwatch;// { StartImmediately::Yes };

	bool		m_SE_Once[3];

	bool		m_PauseOnce = false;

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;


	// ステージの番号を引数をもらってそのステージの配置をするだけ。
	// ステージの番号は、0スタート。プレイヤーとゴールは引数で返す
	// StagePlacedBlockList.hの方で定義を書いている。
	void LoadStageToPlaceBlock(const int& stagenum, const int& stagemidnum, Vec3* ret_spawnpos, Vec3* ret_goalpos, bool* ret_itgoal);

	// 開始の合図やタイマーの制御をする
	void StandbyGameInit();
	void GameStepDraw() const;

	void ElapsedTimeUpdate()
	{
		m_SceneElapsedTime += Scene::DeltaTime();

		if (GetGameStep() == GameStep::NowGame)
		{

		}
		else if (GetGameStep() == GameStep::Standby)
		{
			
		}
		else if (GetGameStep() == GameStep::Result)
		{
			m_ResultElapsedTime += Scene::DeltaTime();
		}
	}

	void SetGameStep(GameStep gamestep) { m_GameStep = gamestep; }
	GameStep GetGameStep() { return m_GameStep; }

	bool UpdateFirstCheck()
	{
		if (m_UpdateFirst)
		{
			m_UpdateFirst = false;
			return true;
		}
	}

	// ゴールの方向への矢印の描写
	void ArrowDraw() const;


	// リザルトの時のもう一度遊ぶボタンと、ステージ選択に戻るボタン
	Rect m_RetryButton{ Arg::center = Scene::Center().movedBy(-250, 300), 300, 60 };
	Transition m_RetryTransition{ 0.4s, 0.2s };

	Rect m_BackStageSelectButton{ Arg::center = Scene::Center().movedBy(250, 300), 300, 60 };
	Transition m_BackStageSelectTransition{ 0.4s, 0.2s };


	// ポーズの時のもう一度遊ぶボタンと、ステージ選択に戻るボタン
	Rect m_P_RetryButton{ Arg::center = Scene::Center().movedBy(-250, 300), 300, 60 };
	Transition m_P_RetryTransition{ 0.4s, 0.2s };

	Rect m_P_BackStageSelectButton{ Arg::center = Scene::Center().movedBy(250, 300), 300, 60 };
	Transition m_P_BackStageSelectTransition{ 0.4s, 0.2s };
};
