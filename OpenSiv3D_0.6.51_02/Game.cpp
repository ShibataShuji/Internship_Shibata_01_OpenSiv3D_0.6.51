#include "stdafx.h"

static const float centerpointsize = 8;

Game::Game(const InitData& init)
	: IScene{ init }
{

	m_UpdateFirst = true;
	m_SceneElapsedTime = 0.0;
	m_ResultElapsedTime = 0.0;
	m_GameStep = GameStep::Standby;

	for (auto i : step(3))
		m_SE_Once[i] = false;


	// プレイヤーをAdd。プレイヤーは1番最初に来て欲しいので。
	m_Player = getData().GameObjectListData.AddGameObject<Player>();

	Vec3 SoawnPos;
	Vec3 GoalPos;
	int Nowstagenum = getData().SelectStage;
	int Nowstagemidnum = getData().SelectMid;
	bool itgoal= getData().itGoal;
	// ステージ番号と中間ポイントの番号を渡して配置
	LoadStageToPlaceBlock(Nowstagenum, Nowstagemidnum , &SoawnPos, &GoalPos, &itgoal);

	// プレイヤーの座標
	m_Player->SetInitPosition(SoawnPos);

	// ゴールor中間ポイント
	m_GoalObject = getData().GameObjectListData.AddGameObject<GoalObject>();
	m_GoalObject->SetInitPosition(GoalPos);
	m_GoalObject->SetitGoal(itgoal);


	if (AudioAsset(U"BGM_Title").isPlaying())
		AudioAsset(U"BGM_Title").stop();

	/*if(AudioAsset(U"BGM_Game").isPlaying())
		AudioAsset(U"BGM_Game").stop();*/

	if (AudioAsset(U"BGM_Result").isPlaying())
		AudioAsset(U"BGM_Result").stop();


	if (!AudioAsset(U"BGM_Game").isPlaying())
		AudioAsset(U"BGM_Game").play();
}

void Game::update()
{
	// 1回目のアップデートだったら
	if (UpdateFirstCheck())
	{
		StandbyGameInit();
	}

	// ステージ選択へ戻る
	if (KeyR.pressed())
	{
		AudioAsset(U"SE_Button_Enter").playOneShot();
		// ゲームオブジェクトを全部消す
		getData().GameObjectListData.DelteAllGameObjectList();
		getData().StopwatchData.reset();
		getData().Title_Step = 1;
		// ゲームシーンへ
		changeScene(State::Title);
	}

	m_PauseOnce = false;

	//// デバッグモード
	//if (Key0.pressed())
	//	getData().DebugMode = true;
	//if (Key9.pressed())
	//	getData().DebugMode = false;
	//m_Player->m_DebugMode = getData().DebugMode;

	if (m_GameStep == GameStep::Pause)
	{
		if(!getData().StopwatchData.isPaused())
			getData().StopwatchData.pause();

		if (KeyP.pressed() && m_PauseOnce == false)
		{
			m_GameStep = GameStep::NowGame;
			m_PauseOnce = true;
		}


		// トランジション処理
		m_P_RetryTransition.update(m_P_RetryButton.mouseOver());
		m_P_BackStageSelectTransition.update(m_P_BackStageSelectButton.mouseOver());

		// カーソルの見た目を変える処理
		if (m_P_RetryButton.mouseOver() || m_P_BackStageSelectButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_P_RetryButton.leftClicked())
		{
			AudioAsset(U"SE_Button_Enter").playOneShot();
			// ゲームオブジェクトを全部消す
			getData().GameObjectListData.DelteAllGameObjectList();
			getData().StopwatchData.reset();
			// ゲームシーンへ
			changeScene(State::Game);
			return;
		}

		if (m_P_BackStageSelectButton.leftClicked())
		{
			AudioAsset(U"SE_Button_Enter").playOneShot();
			// ゲームオブジェクトを全部消す
			getData().GameObjectListData.DelteAllGameObjectList();
			getData().Title_Step = 1;
			// ゲームシーンへ
			changeScene(State::Title);
			return;
		}
	}


	
	if (m_GameStep == GameStep::NowGame)
	{
		if (KeyP.pressed() && m_PauseOnce == false)
		{
			//m_GameStep = GameStep::Pause;
		}

		getData().GameObjectListData.UpdateGameObjectList();

		// プレイヤーがゴールオブジェクトに触れていたら
		if (!m_GoalObject->GetCollision_OverlapObjectList().isEmpty())
		{
			// それがゴールだったら
			if (m_GoalObject->GetitGoal())
			{
				// 中間地点のリセット
				getData().SelectMid = 0;

				AudioAsset(U"SE_Goal").playOneShot();

				if (AudioAsset(U"BGM_Title").isPlaying())
					AudioAsset(U"BGM_Title").stop();

				if (AudioAsset(U"BGM_Game").isPlaying())
					AudioAsset(U"BGM_Game").stop();

				if (AudioAsset(U"BGM_Result").isPlaying())
					AudioAsset(U"BGM_Result").stop();

				SetGameStep(GameStep::Result);
				m_Stopwatch.pause();
				getData().StopwatchData.pause();
			}
			else
			{
				// まだ中間ポイントだったら

				// まずプレイヤーとゴール以外を消す
				getData().GameObjectListData.DelteAllGameObjectList_IgnorePlayerandGoal();
				// 中間ポイントの番号を1増やして再配置する
				getData().SelectMid += 1;
				Vec3 SoawnPos;	// このプレイヤーの値はここでは使わないがリスポーン用になる。
				Vec3 GoalPos;
				int Nowstagenum = getData().SelectStage;
				int Nowstagemidnum = getData().SelectMid;
				bool itgoal = getData().itGoal;
				// ステージ番号と中間ポイントの番号を渡して配置
				LoadStageToPlaceBlock(Nowstagenum, Nowstagemidnum, &SoawnPos, &GoalPos, &itgoal);
				// ゴールの再セットをする
				m_GoalObject->SetPosition(GoalPos);
				m_GoalObject->SetitGoal(itgoal);

				AudioAsset(U"SE_Goal").playOneShot();

			}
		}

		// プレイヤーが落下しすぎたら
		if (m_Player->GetPosition().y < -15.0)
		{
			// ゲームオブジェクトを全部消す
			getData().GameObjectListData.DelteAllGameObjectList();
			getData().StopwatchData.pause();
			changeScene(State::Game);
			return;
		}


		const double deltaTime = Scene::DeltaTime();
		const double speed = (deltaTime * 2.0);

		Vec3 Forward = TPSRay::GetCamera()->getLookAtVector();
		Forward.y = 0.0;
		Forward.normalize();
		Vec3 Right = Vec3(Forward.z, 0.0, -Forward.x);




	}
	else if (m_GameStep == GameStep::Standby)
	{
		if(!getData().StopwatchData.isPaused())
			getData().StopwatchData.pause();

		getData().GameObjectListData.UpdateGameObjectList(true);

		if (0.8 < m_SceneElapsedTime && m_SceneElapsedTime < 1.1)
		{
			if (!m_SE_Once[0])
			{
				m_SE_Once[0] = true;
				AudioAsset(U"SE_Countdown").playOneShot();
			}
		}
		else if (1.2 < m_SceneElapsedTime && m_SceneElapsedTime < 1.5)
		{
			if (!m_SE_Once[1])
			{
				m_SE_Once[1] = true;
				AudioAsset(U"SE_Countdown").playOneShot();
			}
		}
		else if (1.6 < m_SceneElapsedTime && m_SceneElapsedTime < 1.9)
		{
			if (!m_SE_Once[2])
			{
				m_SE_Once[2] = true;
				AudioAsset(U"SE_Countdown").playOneShot();
			}
		}

		// ゲームスタートする
		if (2.0 < m_SceneElapsedTime)
		{
			m_GameStep = GameStep::NowGame;
			m_Stopwatch.start();
			getData().StopwatchData.start();

		}
	}
	else if (m_GameStep == GameStep::Result)
	{
		if (1.0 < m_ResultElapsedTime && 2.0 > m_ResultElapsedTime)
		{
			if (!AudioAsset(U"BGM_Result").isPlaying())
				AudioAsset(U"BGM_Result").play();
		}

		// リトライとステージ選択に戻るボタン
		if (2.7 < m_ResultElapsedTime)
		{
			// トランジション処理
			m_RetryTransition.update(m_RetryButton.mouseOver());
			m_BackStageSelectTransition.update(m_BackStageSelectButton.mouseOver());

			// カーソルの見た目を変える処理
			if (m_RetryButton.mouseOver() || m_BackStageSelectButton.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (m_RetryButton.leftClicked())
			{
				AudioAsset(U"SE_Button_Enter").playOneShot();
				// ゲームオブジェクトを全部消す
				getData().GameObjectListData.DelteAllGameObjectList();
				getData().StopwatchData.reset();
				// ゲームシーンへ
				changeScene(State::Game);
				return;
			}

			if (m_BackStageSelectButton.leftClicked())
			{
				AudioAsset(U"SE_Button_Enter").playOneShot();
				// ゲームオブジェクトを全部消す
				getData().GameObjectListData.DelteAllGameObjectList();
				getData().Title_Step = 1;
				// ゲームシーンへ
				changeScene(State::Title);
				return;
			}
		}
	}




	//Print << U"posA: {}"_fmt(p_blocksA->GetPosition());
	//Print << U"rotA: {}"_fmt(p_blocksA->GetRotation());
	//Print << U"scaA: {}"_fmt(p_blocksA->GetScaleRate());
	//Print << U"posB: {}"_fmt(p_blocksB->GetPosition());
	//Print << U"rotB: {}"_fmt(p_blocksB->GetRotation());
	//Print << U"scaB: {}"_fmt(p_blocksB->GetScaleRate());

	// どのゲームステップだとしてもアップデートされるもの
	{
		// FPS視点でのマウスでのカメラ操作。リザルト以外で操作可能
		if (m_GameStep != GameStep::Result || m_GameStep != GameStep::Pause)
		{
			TPSRay::GetFPSCamera()->AddDirectionX(-1.0f * Cursor::DeltaF().x);
			TPSRay::GetFPSCamera()->AddDirectionY(-1.0f * Cursor::DeltaF().y);
			// マウスカーソルを中心に戻す処理
			Cursor::SetPos(Scene::Center());
			Cursor::RequestStyle(CursorStyle::Hidden);
		}

		// 3人称視点
		// m_EyePosition
		m_EyePosition = m_Player->GetPosition();
		m_EyePosition -= TPSRay::GetFPSCamera()->GetDirection() * TPSRay::GetRadius();

		// forcuspos
		Vec3 forcuspos = m_Player->GetPosition();
		forcuspos.y += ForcusOffsetY;							// ちょっとプレイヤーの上にしてあげる。
		TPSRay::GetCamera()->setView(m_EyePosition, forcuspos);


		// レイをプレイヤーの頭上からカメラの向いてる方向に飛ばす
		const Ray ForGetDirectRay = TPSRay::GetCamera()->screenToRay(Scene::Center());
		Vec3 rayD = ForGetDirectRay.getDirection();

		Vec3 RayF = forcuspos + rayD * 100;
		Vec3 RayDirect = RayF - forcuspos;
		RayDirect.normalize();
		TPSRay::SetRay(forcuspos - RayDirect * 0.3, RayDirect);

		// レイ・カメラのアップデート
		TPSRay::RayUpdate();


		// 経過時間の更新
		ElapsedTimeUpdate();
	}

}

void Game::draw() const
{
	Graphics3D::SetCameraTransform(*TPSRay::GetCamera());

	// 3D 描画
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

		const ScopedRenderStates3D blend{ BlendState::OpaqueAlphaToCoverage };

		// 現在のシーンにあるゲームオブジェクトのアップデートを行う
		getData().GameObjectListData.DrawGameObjectList();

		// レイの描写
		TPSRay::RayDraw();

		// 空の描写
		SkyRender::DrawSky();

		// ゴールの向きへの矢印の表示
		if (m_GameStep == GameStep::NowGame)
		{
			ArrowDraw();
		}


	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}


	// 2D描写

	// そのStepのDraw,2Dのみ
	GameStepDraw();


}


void Game::StandbyGameInit()
{
	m_SceneElapsedTime = 0.0;
	SetGameStep(GameStep::Standby);

}

void Game::GameStepDraw() const
{

	if (m_GameStep == GameStep::Standby)
	{
		// デバッグモード
		if (!getData().DebugMode)
		{
			// タイマーの表示
			//String time = m_Stopwatch.format();
			String time = getData().StopwatchData.format();
			Vec2 disptime = Vec2(Scene::Center().x, 16);
			StandbyGameDraw_String(time, disptime, 26);

			int stagenum = getData().SelectStage;
			int midnum = getData().SelectMid;
			String stagename = U"Stage {}-{}"_fmt(stagenum + 1, midnum + 1);
			StandbyGameDraw_String(stagename, Vec2(70, 10), 20);
		}
		// 中心点の描写
		Circle{ Scene::Center(), centerpointsize }.draw(ColorF{ 0.0, 0.5, 1.0, 0.8 });

		if (-0.1 <= m_SceneElapsedTime && m_SceneElapsedTime < 0.6)
		{
			StandbyGameDraw_String(U"Ready...", Scene::Center(), 250);
		}
		else if (0.8 < m_SceneElapsedTime && m_SceneElapsedTime < 1.1)
		{
			StandbyGameDraw_String(U"3", Scene::Center(), 250);
		}
		else if (1.2 < m_SceneElapsedTime && m_SceneElapsedTime < 1.5)
		{
			StandbyGameDraw_String(U"2", Scene::Center(), 250);
		}
		else if (1.6 < m_SceneElapsedTime && m_SceneElapsedTime < 1.9)
		{
			StandbyGameDraw_String(U"1", Scene::Center(), 250);
		}
		//else if (2.0 < m_SceneElapsedTime && m_SceneElapsedTime < 3.6)
		//{
		//	StandbyGameDraw_String(U"GO!!!", Scene::Center(), 250);		// Goの表示はゲームが始まってからもちょっと行う
		//}
	}

	// Goの表示はゲームが始まってからもちょっと行いたいので全てのところで行う。
	if (2.0 < m_SceneElapsedTime && m_SceneElapsedTime < 3.3)
	{
		StandbyGameDraw_String(U"GO!!!", Scene::Center(), 250);	
	}



	if (m_GameStep == GameStep::NowGame)
	{
		// 中心点の描写
		Circle{ Scene::Center(), centerpointsize }.draw(ColorF{ 0.0, 0.5, 1.0, 0.8 });

		// タイマーの表示
		//String time = m_Stopwatch.format();
		String time = getData().StopwatchData.format();
		Vec2 disptime = Vec2(Scene::Center().x, 16);
		StandbyGameDraw_String(time, disptime, 26);


		if (2.0 < m_SceneElapsedTime)
		{
			// デバッグモード
			if (!getData().DebugMode)
			{
				int stagenum = getData().SelectStage;
				int midnum = getData().SelectMid;
				String stagename = U"Stage {}-{}"_fmt(stagenum + 1, midnum + 1);

				StandbyGameDraw_String(stagename, Vec2(70, 10), 20);
				StandbyGameDraw_String(U"ゴールを目指せ!", Vec2(130, 37), 30);
			}
		}
	}

	if (m_GameStep == GameStep::Pause)
	{
		m_P_RetryButton.draw(ColorF{ 1.0, m_P_RetryTransition.value() }).drawFrame(2);
		FontAsset(U"Menu")(U"Retry").drawAt(m_P_RetryButton.center(), ColorF{ 0.25 });

		m_P_BackStageSelectButton.draw(ColorF{ 1.0, m_P_BackStageSelectTransition.value() }).drawFrame(2);
		FontAsset(U"Menu")(U"StageSelect").drawAt(m_P_BackStageSelectButton.center(), ColorF{ 0.25 });
	}

	if (m_GameStep == GameStep::Result)
	{

		{
			// 黒の上下のラインが出てくる
			float MoveMax = 230.0;

			float offsetHeight = 200.0 * (m_ResultElapsedTime - 0.5f);
			if (offsetHeight > MoveMax)
				offsetHeight = MoveMax;

			// offsetHeightを最大値までの割合にしてEaseで計算する
			float wariai = offsetHeight / MoveMax;
			float AfteroffsetHeight = EaseOutExpo(wariai) * MoveMax;



			Vec2 rectpos_up = Vec2(Scene::Center().x, -200 + AfteroffsetHeight);
			Vec2 rectpos_down = Vec2(Scene::Center().x, 200 + Scene::Height() - AfteroffsetHeight);

			float rectwidth = Scene::Width();

			RectF{ Arg::center(rectpos_up), rectwidth, 200 }.draw(Palette::Black);
			RectF{ Arg::center(rectpos_down), rectwidth, 200 }.draw(Palette::Black);
		}

		{
			if (2.0 < m_ResultElapsedTime)
			{
				// この中での経過時間
				double ElapsedTime = m_ResultElapsedTime - 2.0;

				Vec2 center = Scene::Center();
				float rectwidth = Scene::Width();
				float rectheight = Scene::Height();
				ColorF color = Linear::Palette::Black;


				double maxtime = 0.8;	// 暗くなる最大時間
				float alfamax = 0.5;

				float wariai = ElapsedTime / maxtime;
				float alfa = EaseOutExpo(wariai) * alfamax;

				color.a = alfa;
				RectF{ Arg::center(center), rectwidth, rectheight }.draw(color);

			}
		}

		{
			// クリアタイムとクリアの文字の表示
			if (2.0 < m_ResultElapsedTime)
			{
				// この中での経過時間
				double ElapsedTime = m_ResultElapsedTime - 2.0;

				Vec2 center = Scene::Center();
				//float rectwidth = Scene::Width();
				//float rectheight = Scene::Height();
				ColorF color = Linear::Palette::Black;


				double maxtime = 0.8;	// 暗くなる最大時間
				float alfamax = 1.0;

				float wariai = ElapsedTime / maxtime;
				float alfa = EaseOutExpo(wariai) * alfamax;

				color.a = alfa;

				//String time =  m_Stopwatch.format();
				String time = getData().StopwatchData.format();
				StandbyGameDraw_String(time, center, 150);

				Vec2 up = center;
				up.y -= 200.0;
				String clear = U"Clear";
				StandbyGameDraw_String(clear, up, 200);

				Vec2 leftup = center;
				leftup.y -= 300.0;
				leftup.x -= 450.0;
				int stagenum = getData().SelectStage;
				String stagename = U"Stage {}"_fmt(stagenum + 1);
				StandbyGameDraw_String(stagename, leftup, 60);

			}
		}


		{
			// リトライとステージ選択に戻るボタン
			if (2.7 < m_ResultElapsedTime)
			{
				m_RetryButton.draw(ColorF{ 1.0, m_RetryTransition.value() }).drawFrame(2);
				FontAsset(U"Menu")(U"Retry").drawAt(m_RetryButton.center(), ColorF{ 0.25 });

				m_BackStageSelectButton.draw(ColorF{ 1.0, m_BackStageSelectTransition.value() }).drawFrame(2);
				FontAsset(U"Menu")(U"StageSelect").drawAt(m_BackStageSelectButton.center(), ColorF{ 0.25 });
			}
		}
		

	}


}

// プレイヤーからゴールの方向(yは無視)への矢印を表示する
void Game::ArrowDraw() const
{
	float ArrowLength = 1.4f;
	float ArrowSideLength = 0.8;
	constexpr float ArrowSideRotateAngle = 60_deg;
	float ArrowSize = 0.05;
	ColorF ArrowColor = Linear::Palette::Yellow;
	float alfa = 0.2f;
	//float alfa = cos(m_SceneElapsedTime);
	//if (alfa < 0.0)
	//	alfa = 0.0;
	//if (alfa > 0.2)
	//	alfa = 0.2;
	ArrowColor.setA(alfa);

	// プレイヤーと同じ高さにしたゴールのポジション
	Vec3 GoalChangeY = m_GoalObject->GetPosition();
	GoalChangeY.y = m_Player->GetPosition().y;

	Vec3 ToGoalNormal = GoalChangeY - m_Player->GetPosition();
	ToGoalNormal.y = 0;		// yは無視してxzだけで作る
	ToGoalNormal.normalize();

	Vec3 start = m_Player->GetPosition();
	Vec3 end = start + ToGoalNormal * ArrowLength;

	Vec2 normal = Vec2(ToGoalNormal.x, ToGoalNormal.z);
	Vec2 posAaddvec2 = normal.rotated(ArrowSideRotateAngle);
	Vec2 posBaddvec2 = normal.rotated(-ArrowSideRotateAngle);

	Vec3 posA = start + Vec3(posAaddvec2.x, 0, posAaddvec2.y);
	Vec3 posB = start + Vec3(posBaddvec2.x, 0, posBaddvec2.y);

	Cylinder{ start, end, ArrowSize }.draw(ArrowColor);
	Cylinder{ posA, end, ArrowSize }.draw(ArrowColor);
	Cylinder{ posB, end, ArrowSize }.draw(ArrowColor);


}





// --------------------------------------------関数定義

// 中心に文字を表示(数字3,2,1する時使う)
void StandbyGameDraw_String(const String& string, const Vec2& pos, const float& size)
{
	ColorF color = Linear::Palette::White;

	FontAsset(U"TitleFont")(string)
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), size, pos, color);
}
