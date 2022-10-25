#include "stdafx.h"

//static Blocks* p_blocksA = nullptr;
//static Blocks* p_blocksB = nullptr;

Game::Game(const InitData& init)
	: IScene{ init }
{

	m_Player = getData().GameObjectListData.AddGameObject<Player>();
	m_Player->SetInitPosition(Vec3(0, 1, 0));

	//Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
	//p_Blocks_0->SetInitPosition(Vec3(10, 0, 10));
	////p_Blocks->m_Size = Vec3(2, 2, 2);

	//Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
	//p_Blocks_1->SetInitPosition(Vec3(10, 0, 0));
	//p_Blocks_1->SetInitScaleRate(Vec3(1.5, 1.5, 1.5));

	//Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
	//p_Blocks_2->SetInitPosition(Vec3(10, 0, -10));
	//p_Blocks_2->SetInitScaleRate(Vec3(2, 2, 2));

	Blocks* p_Blocks_3 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_3->SetInitPosition(Vec3(0, -5, 0));
	p_Blocks_3->SetInitScaleRate(Vec3(10, 2, 10));
	//// 親子の設定
	//p_Blocks_1->AddChild(p_Blocks_0);
	//p_Blocks_1->AddChild(p_Blocks_2);




	//Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
	//p_Blocks_4->SetInitPosition(Vec3(10, 10, 10));
	//p_Blocks_4->SetInitScaleRate(Vec3(2, 2, 2));
	//p_Blocks_4->SetInitRotation(Vec3(0.314, 0, 0));
	//p_Blocks_4->SetRotationSpeed(Vec3(0.0, 0, 0.02));
	//p_blocksA = p_Blocks_4;


	//Blocks* p_Blocks_5 = getData().GameObjectListData.AddGameObject<Blocks>();
	//p_Blocks_5->SetInitPosition(Vec3(20, 10, 10));
	//p_Blocks_5->SetInitScaleRate(Vec3(1.5, 1.5, 1.5));
	//p_Blocks_5->SetInitRotation(Vec3(0, 0, 0));
	//p_blocksB = p_Blocks_5;

	//p_Blocks_4->AddChild(p_Blocks_5);




	Blocks* p_Blocks_6 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_6->SetInitPosition(Vec3(30, 1, 0));
	p_Blocks_6->SetInitScaleRate(Vec3(2, 2, 2));
	p_Blocks_6->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_6->SetRotationSpeed(Vec3(0.0, 0.005, 0.0));
	p_Blocks_6->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);


	Blocks* p_Blocks_7 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_7->SetInitPosition(Vec3(40, 2, 0));
	p_Blocks_7->SetInitScaleRate(Vec3(3, 3, 3));
	p_Blocks_7->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_7->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
	p_Blocks_7->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

	//p_Blocks_6->AddChild(p_Blocks_7);

	Blocks* p_Blocks_8 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_8->SetInitPosition(Vec3(30, 1, 20));
	p_Blocks_8->SetInitScaleRate(Vec3(1, 5, 1));
	p_Blocks_8->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_8->SetRotationSpeed(Vec3(0.0, 0.005, 0.0));
	p_Blocks_8->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);


	Blocks* p_Blocks_9 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_9->SetInitPosition(Vec3(33, 1, 20));
	p_Blocks_9->SetInitScaleRate(Vec3(3, 1, 3));
	p_Blocks_9->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_9->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
	p_Blocks_9->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

	p_Blocks_8->AddChild(p_Blocks_9);

	Blocks* p_Blocks_10 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_10->SetInitPosition(Vec3(10, 1, 60));
	p_Blocks_10->SetInitScaleRate(Vec3(2, 20, 10));
	p_Blocks_10->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_10->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
	p_Blocks_10->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

	Blocks* p_Blocks_11 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_11->SetInitPosition(Vec3(0, 0, 90));
	p_Blocks_11->SetInitScaleRate(Vec3(10, 1, 10));
	p_Blocks_11->SetInitRotation(Vec3(0, 0, 0));
	p_Blocks_11->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
	p_Blocks_11->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);



}

void Game::update()
{
	// 現在のシーンにあるゲームオブジェクトのアップデートを行う
	getData().GameObjectListData.UpdateGameObjectList();

	const double deltaTime = Scene::DeltaTime();
	const double speed = (deltaTime * 2.0);
	//Vec3 Forward = m_Camera.getLookAtVector();
	Vec3 Forward = TPSRay::GetCamera()->getLookAtVector();
	Forward.y = 0.0;
	Forward.normalize();
	Vec3 Right = Vec3(Forward.z, 0.0, -Forward.x);

	// 位置・注目点情報を更新。プレイヤーの位置と向きにカメラをセット
	//m_EyePosition = m_Player->GetPosition();
	//m_EyePosition.y += 1.0f;
	//m_Camera.setView(m_EyePosition, m_Player->GetFPSCamera().GetFocusPosition(m_EyePosition));
	//Print << U"angleX: {:.1f}°"_fmt(fpsm_Camera.angleX);
	//Print << U"angleYvalue: {:.1f}"_fmt(fpsm_Camera.angleYvalue);
	//Print << U"direction: {:.2f}"_fmt(fpsm_Camera.GetDirection());
	//Print << U"eyePositon: {:.1f}"_fmt(m_Camera.getEyePosition());
	//Print << U"focusPosition: {:.1f}"_fmt(m_Camera.getFocusPosition());
	//Print << U"Vel: {}"_fmt(m_Player->GetVelocity());

	//Vec3 rotaa = p_blocksA->GetRotation();
	//Vec3 posaa = p_blocksA->GetPosition();
	//Vec3 scalerateaaa = p_blocksA->GetScaleRate();

	// テスト用
	//if (Key1.pressed())
	//	rotaa.x += 0.1;
	//p_blocksA->SetRotation(rotaa);

	//if (Key2.pressed())
	//	posaa.x += 0.1;
	//p_blocksA->SetPosition(posaa);

	//if (Key3.pressed())
	//	scalerateaaa.x += 0.1;
	//p_blocksA->SetScaleRate(scalerateaaa);

	//if (Key4.pressed())
	//	rotaa.y += 0.1;
	//p_blocksA->SetRotation(rotaa);

	//Print << U"posA: {}"_fmt(p_blocksA->GetPosition());
	//Print << U"rotA: {}"_fmt(p_blocksA->GetRotation());
	//Print << U"scaA: {}"_fmt(p_blocksA->GetScaleRate());
	//Print << U"posB: {}"_fmt(p_blocksB->GetPosition());
	//Print << U"rotB: {}"_fmt(p_blocksB->GetRotation());
	//Print << U"scaB: {}"_fmt(p_blocksB->GetScaleRate());

	// FPS視点でのマウスでのカメラ操作
	TPSRay::GetFPSCamera()->AddDirectionX(-1.0f * Cursor::DeltaF().x);
	TPSRay::GetFPSCamera()->AddDirectionY(-1.0f * Cursor::DeltaF().y);
	// マウスカーソルを中心に戻す処理
	Cursor::SetPos(Scene::Center());
	Cursor::RequestStyle(CursorStyle::Hidden);




	// 3人称視点
	// m_EyePosition
	m_EyePosition = m_Player->GetPosition();
	m_EyePosition -= TPSRay::GetFPSCamera()->GetDirection() * 20;

	// forcuspos
	Vec3 forcuspos = m_Player->GetPosition();
	forcuspos.y += 0.5;							// ちょっとプレイヤーの上にしてあげる。
	TPSRay::GetCamera()->setView(m_EyePosition, forcuspos);


	// レイをプレイヤーの頭上からカメラの向いてる方向に飛ばす
	const Ray ForGetDirectRay = TPSRay::GetCamera()->screenToRay(Scene::Center());
	Vec3 rayD = ForGetDirectRay.getDirection();

	Vec3 RayF = forcuspos + rayD * 100;
	Vec3 RayDirect = RayF - forcuspos;
	RayDirect.normalize();
	TPSRay::SetRay(forcuspos, RayDirect);

	// レイ・カメラのアップデート
	TPSRay::RayUpdate();
}

void Game::draw() const
{
	Graphics3D::SetCameraTransform(*TPSRay::GetCamera());

	// 3D 描画
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

		// 現在のシーンにあるゲームオブジェクトのアップデートを行う
		getData().GameObjectListData.DrawGameObjectList();

		// レイの描写
		TPSRay::RayDraw();

		//cyl->draw(Linear::Palette::Gray);
		
		//Plane{ 64 }.draw(uvChecker);
		//Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		//Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());
		//Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());


		// 勉強でやってた用
		/*
		Mat4x4 defmat = Mat4x4::Identity();			// 演算用に基本形の行列を作成
		Quaternion Qua = Quaternion::Identity();	// 演算用に基本形のクォータニオンをを作成

		Float3 po = Vec3(30, 1, -20);		// Boxの座標
		Vec3 size = Vec3(1, 3, 6);			// Boxのサイズ(形)
		Float3 scale = Vec3(1, 1, 1);		// Boxのサイズの倍率(伸び縮み)
		Vec3 rotvec = Vec3(45, 0, 0);		// Rotation(度)

		OrientedBox{ po, size, Qua }.draw(Linear::Palette::Aqua);


		static double mmm = 1.57;
		if (MouseR.down())
		{
			mmm += 0.01;
		}
		//Print << U"mmm: {:}"_fmt(mmm);

		// Rotationで回転後のクォータニオンを求める。戻り値じゃないとダメ。元の値は変わらない。
		Vec3 rot = Vec3(mmm, 0, 0);		// Rotation(ラジアン)
		Quaternion RotQua = Qua.RollPitchYaw<double, double, double>(rot.x, rot.y, rot.z);


		Float3 po2 = Vec3(0, 0, 0);		// Boxの座標
		OrientedBox{ po, size, RotQua }.draw(Linear::Palette::Brown);
		*/



	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}


	// 2D描写

	// 中心点の描写
	Circle{ Scene::Center(), 10 }.draw(ColorF{ 0.0, 0.5, 1.0, 0.8 });
}
