#include "stdafx.h"

Game::Game(const InitData& init)
	: IScene{ init }
{
	Blocks* p_Blocks = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks->SetPosition(Vec3(0, 0, 20));
	p_Blocks->m_Size = Vec3(40, 40, 1);
}

void Game::update()
{
	// 現在のシーンにあるゲームオブジェクトのアップデートを行う
	getData().GameObjectListData.UpdateGameObjectList();

	ClearPrint();
	const double deltaTime = Scene::DeltaTime();
	const double speed = (deltaTime * 2.0);
	Vec3 Forward = camera.getLookAtVector();
	Forward.y = 0.0;
	Forward.normalize();
	Vec3 Right = Vec3(Forward.z, 0.0, -Forward.x);

	//Cursor::DeltaF();


	if (MouseL.down())
	{
		KnifeBlock* p_KnifeBlock = getData().GameObjectListData.AddGameObject<KnifeBlock>();
		Vec3 LaunchPosition = eyePosition + (camera.getLookAtVector() * 10.0);
		p_KnifeBlock->SetPosition(LaunchPosition);
		p_KnifeBlock->SetVelocity(camera.getLookAtVector() * 2.0);
		p_KnifeBlock->SetQuaternion(camera.getLookAtOrientation());

		p_KnifeBlock->m_Size = Vec3(4, 0.5, 8);
	}




	if (KeyW.pressed())
	{
		eyePosition += Forward;
	}

	if (KeyA.pressed())
	{
		eyePosition += -Right;
	}

	if (KeyS.pressed())
	{
		eyePosition += -Forward;
	}

	if (KeyD.pressed())
	{
		eyePosition += Right;
	}

	if (KeyLeft.pressed())
	{
		fpscamera.AddDirectionX(-1.0f);
	}

	if (KeyRight.pressed())
	{
		fpscamera.AddDirectionX(1.0f);
	}

	if (KeyUp.pressed())
	{
		fpscamera.AddDirectionY(1.0f);
	}

	if (KeyDown.pressed())
	{
		fpscamera.AddDirectionY(-1.0f);
	}

	// マウス操作
	// ほんの少しのブレは考慮しないバージョン
	//Vec2 CursorDelta = Cursor::DeltaF();
	//if (fabs(CursorDelta.x) < 0.3f)
	//	CursorDelta.x = 0;
	//if (fabs(CursorDelta.y) < 0.3f)
	//	CursorDelta.y = 0;
	//fpscamera.AddDirectionX(-1.0f * CursorDelta.x);
	//fpscamera.AddDirectionY(-1.0f * CursorDelta.y);
	fpscamera.AddDirectionX(-1.0f * Cursor::DeltaF().x);
	fpscamera.AddDirectionY(-1.0f * Cursor::DeltaF ().y);
	// マウスカーソルを中心に戻す処理
	Cursor::SetPos(Scene::Center());



	// 位置・注目点情報を更新
	camera.setView(eyePosition, fpscamera.GetFocusPosition(eyePosition));
	Print << U"angleX: {:.1f}°"_fmt(fpscamera.angleX);
	Print << U"angleYvalue: {:.1f}"_fmt(fpscamera.angleYvalue);
	Print << U"direction: {:.2f}"_fmt(fpscamera.GetDirection());
	Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
	Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
}

void Game::draw() const
{



	Graphics3D::SetCameraTransform(camera);

	// 3D 描画
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

		// 現在のシーンにあるゲームオブジェクトのアップデートを行う
		getData().GameObjectListData.DrawGameObjectList();

		Plane{ 64 }.draw(uvChecker);
		//Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());
		Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());
	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}

	//Scene::SetBackground(ColorF{ 0.2 });

	//// すべてのブロックを描画する
	//for (const auto& brick : m_bricks)
	//{
	//	brick.stretched(-1).draw(HSV{ brick.y - 40 });
	//}

	//// ボールを描く
	//m_ball.draw();

	//// パドルを描く
	//getPaddle().draw();

	//FontAsset(U"GameScore")(m_score).draw(10, 10);
}
