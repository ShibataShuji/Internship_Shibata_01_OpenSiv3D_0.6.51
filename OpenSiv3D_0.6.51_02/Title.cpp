#include "stdafx.h"

Title::Title(const InitData& init)
	: IScene{ init }
{
	getData().StopwatchData.reset();

	m_Camera = BasicCamera3D{ Scene::Size(), 30_deg, Vec3{0, 16, -32}, Vec3{0, 0, 1} };
	m_EyePos = Vec3(0, 5, -30);
	m_forcusPos = Vec3(0, 3, 0);

	//m_Step = 0;
	m_tStep = -1;
	m_StepElapsedTime = 0.0;

	for (auto i : step(StageMaxNum))
	{
		m_StageSelectButton[i] = { Arg::center = Scene::Center().movedBy(0,  -200 + i * 100), 300, 60 };
		m_StageSelectTransition[i] = Transition{ 0.4s, 0.2s };
	}


	// ブロックの配置
	{

		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(0, -1, -1));
		p_Blocks_0->SetInitScaleRate(Vec3(5, 5, 5));

		Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_1->SetInitPosition(Vec3(-10, 2, -1));
		p_Blocks_1->SetInitScaleRate(Vec3(3, 3, 3));

		Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_2->SetInitPosition(Vec3(-10, 6, -1));
		p_Blocks_2->SetInitScaleRate(Vec3(2.5, 1, 2.5));
		p_Blocks_2->SetMoveState(Vec3(10, 6, -1), 10, 2.5);

		Blocks* p_Blocks_3 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_3->SetInitPosition(Vec3(-16, 1, 20));
		p_Blocks_3->SetInitScaleRate(Vec3(12, 12, 12));
		p_Blocks_3->SetInitRotation(Vec3(0, 0, 0));
		p_Blocks_3->SetRotationSpeed(Vec3(0.0, -0.0003, 0.0));
		p_Blocks_3->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

		Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_4->SetInitPosition(Vec3(24, 16, 24));
		p_Blocks_4->SetInitScaleRate(Vec3(18, 18, 18));
		p_Blocks_4->SetInitRotation(Vec3(0, 0, 0));
		p_Blocks_4->SetRotationSpeed(Vec3(0.0, -0.0003, 0.0));
		p_Blocks_4->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Blue);

		Blocks* p_Blocks_8 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_8->SetInitPosition(Vec3(7, 1, 2));
		p_Blocks_8->SetInitScaleRate(Vec3(1, 5, 1));
		p_Blocks_8->SetInitRotation(Vec3(0, 0, 0));
		p_Blocks_8->SetRotationSpeed(Vec3(0.0, 0.005, 0.0));
		p_Blocks_8->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);


		Blocks* p_Blocks_9 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_9->SetInitPosition(Vec3(11, 1, 4));
		p_Blocks_9->SetInitScaleRate(Vec3(3, 1, 3));
		p_Blocks_9->SetInitRotation(Vec3(0, 0, 0));
		p_Blocks_9->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
		p_Blocks_9->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

		p_Blocks_8->AddChild(p_Blocks_9);
	}


	if (AudioAsset(U"BGM_Title").isPlaying())
		AudioAsset(U"BGM_Title").stop();

	if (AudioAsset(U"BGM_Game").isPlaying())
		AudioAsset(U"BGM_Game").stop();

	if (AudioAsset(U"BGM_Result").isPlaying())
		AudioAsset(U"BGM_Result").stop();

	AudioAsset(U"BGM_Title").play();
}

void Title::update()
{
	m_Camera.setView(m_EyePos, m_forcusPos);

	// 現在のシーンにあるゲームオブジェクトのアップデートを行う
	getData().GameObjectListData.UpdateGameObjectList();


	// クリックでエフェクト表示
	if (MouseL.down())
	{
		EffectManager::GetEffect()->add<BubbleEffect>(Cursor::PosF(), Random(0.0, 360.0));
		//EffectManager::GetEffect()->add<BulletEffect_Hit>(Vec3(0,0,0), Random(0.0, 360.0));
	}



	// マウスが重なった時の色が変わるトランジションのアップデート
	{
		m_startTransition.update(m_startButton.mouseOver());
		//m_rankingTransition.update(m_rankingButton.mouseOver());
		m_exitTransition.update(m_exitButton.mouseOver());

		for (auto i : step(StageMaxNum))
		{
			m_StageSelectTransition[i].update(m_StageSelectButton[i].mouseOver());
		}
		m_backtitleTransition.update(m_backtitleButton.mouseOver());
	}


	// Stepの変化の時の経過の更新
	ChangeStepUpdate();

	// Stepごとの処理
	if (getData().Title_Step == 0)
	{
		// カーソルの見た目を変える処理
		if (m_startButton.mouseOver() || m_exitButton.mouseOver())	//m_rankingButton.mouseOver()
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_startButton.leftClicked())
		{
			AudioAsset(U"SE_Button_Enter").playOneShot();
			SetStep(1);
			//// ゲームオブジェクトを全部消す
			//getData().GameObjectListData.DelteAllGameObjectList();
			//// ゲームシーンへ
			//changeScene(State::Game);
			//return;
		}
		//else if (m_rankingButton.leftClicked())
		//{
		//	// ランキングシーンへ
		//	//changeScene(State::Ranking);
		//	//return;
		//}
		else if (m_exitButton.leftClicked())
		{
			// 終了
			System::Exit();
			//return;
		}

	}

	// Step == 1
	if (getData().Title_Step == 1)
	{
		for (auto i : step(StageMaxNum))
		{
			// カーソルの見た目を変える処理
			if (m_StageSelectButton[i].mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (m_StageSelectButton[i].leftClicked())
			{
				// 洗濯したステージ番号をセットする
				getData().SelectStage = i;
				getData().SelectMid = 0;
				AudioAsset(U"SE_Button_Enter").playOneShot();
				// ゲームオブジェクトを全部消す
				getData().GameObjectListData.DelteAllGameObjectList();
				// ゲームシーンへ
				changeScene(State::Game);
				return;
			}
		}

		// タイトルに戻るボタン
		// カーソルの見た目を変える処理
		if (m_backtitleButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
		if (m_backtitleButton.leftClicked())
		{
			AudioAsset(U"SE_Button_Enter").playOneShot();
			SetStep(0);
		}
		//m_backtitleTransition.update(m_backtitleButton.mouseOver());

	}



}

void Title::draw() const
{
	Graphics3D::SetCameraTransform(m_Camera);

	// 3D 描画
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

		const ScopedRenderStates3D blend{ BlendState::OpaqueAlphaToCoverage };

		// 現在のシーンにあるゲームオブジェクトのアップデートを行う
		getData().GameObjectListData.DrawGameObjectList();


		// 空の描写
		SkyRender::DrawSky();




	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}


	// 2D描写

	Scene::SetBackground(ColorF{ 0.2, 0.8, 0.4 });


	if(getData().Title_Step == 0)
	{
		FontAsset(U"TitleFont")(U"BREAKOUT")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

		m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(2);
		//m_rankingButton.draw(ColorF{ 1.0, m_rankingTransition.value() }).drawFrame(2);
		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"PLAY").drawAt(m_startButton.center(), ColorF{ 0.25 });
		//FontAsset(U"Menu")(U"RANKING").drawAt(m_rankingButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"EXIT").drawAt(m_exitButton.center(), ColorF{ 0.25 });
	}

	if (getData().Title_Step == 1)
	{

		FontAsset(U"TitleFont")(U"Stage Select")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

		for (auto i : step(StageMaxNum))
		{
			m_StageSelectButton[i].draw(ColorF{1.0, m_StageSelectTransition[i].value()}).drawFrame(2);

			FontAsset(U"Menu")(U"Stage {}"_fmt(i + 1)).drawAt(m_StageSelectButton[i].center(), ColorF{0.25});

		}

		m_backtitleButton.draw(ColorF{ 1.0, m_backtitleTransition.value() }).drawFrame(2);
		FontAsset(U"Menu")(U"Back").drawAt(m_backtitleButton.center(), ColorF{ 0.25 });
	}


}


void Title::SetStep(const int16 toStep)
{
	// まずStepをチェンジ中(どのシーンにも属さないにする)
	getData().Title_Step = -1;
	m_tStep = toStep;
	m_StepElapsedTime = 0.0;
}

void Title::ChangeStepUpdate()
{
	if (m_tStep == -1)
		return;

	// この時間を超えてるとステップが変わる(クリックのCTになっている)
	float maxtime = 0.5;
	if (m_StepElapsedTime > maxtime)
	{
		getData().Title_Step = m_tStep;
		m_tStep = -1;
	}


	m_StepElapsedTime += Scene::DeltaTime();
}
