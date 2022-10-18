#include "stdafx.h"

Game::Game(const InitData& init)
	: IScene{ init }
{

	m_Player = getData().GameObjectListData.AddGameObject<Player>();
	m_Player->SetPosition(Vec3(0, 1, 0));

	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_0->SetPosition(Vec3(10, 0, 10));
	//p_Blocks->m_Size = Vec3(2, 2, 2);

	Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_1->SetPosition(Vec3(10, 0, 0));
	p_Blocks_1->SetScaleRate(Vec3(1.5, 1.5, 1.5));

	Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
	p_Blocks_2->SetPosition(Vec3(10, 0, -10));
	p_Blocks_2->SetScaleRate(Vec3(2, 2, 2));

}

void Game::update()
{
	// 現在のシーンにあるゲームオブジェクトのアップデートを行う
	getData().GameObjectListData.UpdateGameObjectList();

	const double deltaTime = Scene::DeltaTime();
	const double speed = (deltaTime * 2.0);
	Vec3 Forward = camera.getLookAtVector();
	Forward.y = 0.0;
	Forward.normalize();
	Vec3 Right = Vec3(Forward.z, 0.0, -Forward.x);

	// 位置・注目点情報を更新。プレイヤーの位置と向きにカメラをセット
	eyePosition = m_Player->GetPosition();
	eyePosition.y += 1.0f;
	camera.setView(eyePosition, m_Player->GetFPSCamera().GetFocusPosition(eyePosition));
	//Print << U"angleX: {:.1f}°"_fmt(fpscamera.angleX);
	//Print << U"angleYvalue: {:.1f}"_fmt(fpscamera.angleYvalue);
	//Print << U"direction: {:.2f}"_fmt(fpscamera.GetDirection());
	//Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
	//Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
	//Print << U"Vel: {}"_fmt(m_Player->GetVelocity());



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
}
