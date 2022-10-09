//# include <Siv3D.hpp>
# include "stdafx.h"

//Vec3 GetDirection(double angleX, double angleY)
//{
//	const Vec3 dir = Spherical{ 1.0, angleY, angleX };
//	return dir;
//
//	//const Vec2 dir = Circular{ 1.0, angle };
//	//return{ dir.x, 0.0, -dir.y };
//}
//
//Vec3 GetFocusPosition(const Vec3& eyePosition, double angleX, double angleY)
//{
//	return (eyePosition + GetDirection(angleX, angleY));
//}

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Vec3 eyePosition{ 0, 2, -16 };
	FPSCamera fpscamera;
	BasicCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, fpscamera.GetFocusPosition(eyePosition)};

	while (System::Update())
	{
		ClearPrint();
		const double deltaTime = Scene::DeltaTime();
		const double speed = (deltaTime * 2.0);
		Vec3 Forward = camera.getLookAtVector();
		Forward.y = 0.0;
		Forward.normalize();
		Vec3 Right = Vec3(Forward.z, 0.0, -Forward.x);

		//Cursor::DeltaF();


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
		fpscamera.AddDirectionX(-1.0f * Cursor::DeltaF().x);
		fpscamera.AddDirectionY(-1.0f * Cursor::DeltaF().y);
		Cursor::SetPos(Scene::Center());
		

		// 位置・注目点情報を更新
		camera.setView(eyePosition, fpscamera.GetFocusPosition(eyePosition));
		Print << U"angleX: {:.1f}°"_fmt(fpscamera.angleX);
		Print << U"angleYvalue: {:.1f}"_fmt(fpscamera.angleYvalue);
		Print << U"direction: {:.2f}"_fmt(fpscamera.GetDirection());
		Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
		Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
			Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());
			Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
