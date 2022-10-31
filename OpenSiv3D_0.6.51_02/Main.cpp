# include "stdafx.h"


void Main()
{
	Window::Resize(1280, 720);
	//Window::SetFullscreen(true);



	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);


	// Audioアセットの登録
	AudioAsset::Register(U"BGM_Game", Audio::Stream, U"assets/Audio/BGM_Game.mp3");
	AudioAsset::Register(U"BGM_Title", Audio::Stream, U"assets/Audio/BGM_Title.mp3");
	AudioAsset::Register(U"BGM_Result", Audio::Stream, U"assets/Audio/BGM_Result.mp3");

	AudioAsset::Register(U"SE_Bullet_Buu", Audio::Stream, U"assets/Audio/SE_Bullet_Buu.mp3");
	AudioAsset::Register(U"SE_Bullet_Hit", Audio::Stream, U"assets/Audio/SE_Bullet_Hit.mp3");
	AudioAsset::Register(U"SE_Bullet_Shot", Audio::Stream, U"assets/Audio/SE_Bullet_Shot.mp3");
	AudioAsset::Register(U"SE_Button_Enter", Audio::Stream, U"assets/Audio/SE_Button_Enter.mp3");
	AudioAsset::Register(U"SE_Countdown", Audio::Stream, U"assets/Audio/SE_Countdown.mp3");
	AudioAsset::Register(U"SE_Goal", Audio::Stream, U"assets/Audio/SE_Goal.mp3");
	AudioAsset::Register(U"SE_Jump", Audio::Stream, U"assets/Audio/SE_Jump.mp3");
	AudioAsset::Register(U"SE_Landing", Audio::Stream, U"assets/Audio/SE_Landing.mp3");


	// 事前ロード
	AudioAsset::Load(U"BGM_Game");
	AudioAsset::Load(U"BGM_Title");
	AudioAsset::Load(U"BGM_Result");

	AudioAsset::Load(U"SE_Bullet_Buu");
	AudioAsset::Load(U"SE_Bullet_Hit");
	AudioAsset::Load(U"SE_Bullet_Shot");
	AudioAsset::Load(U"SE_Button_Enter");
	AudioAsset::Load(U"SE_Countdown");
	AudioAsset::Load(U"SE_Goal");
	AudioAsset::Load(U"SE_Jump");
	AudioAsset::Load(U"SE_Landing");

	// ループ再生させる
	AudioAsset(U"BGM_Game").setLoop(true);
	AudioAsset(U"BGM_Title").setLoop(true);
	AudioAsset(U"BGM_Result").setLoop(true);

	// 音量調整
	AudioAsset(U"SE_Landing").setVolume(0.4);



	SceneManager<State, GameData> manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	// ゲームデータにどこからでもアクセスできるように
	ManagerManager::SetGameData(manager.get().get());

	

	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);

	SkyRender::InitSky();
	TPSRay::RayInit();
	EffectManager::Init();
	//UIEffectManager::Init();


	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
		// 2D描写最後に持ってくるよ。エフェクトが3Dのやつも2Dで描写しちゃってるから分けたいけど時間に余裕あったら。
		EffectManager::DrawAndUpdate();
		//UIEffectManager::Update();
		//UIEffectManager::Draw();

	}
}
