#pragma once


struct FPSCamera
{

	double angleX = 90_deg;
	double angleYvalue = 0.0;
	float sensitivity = 1.0f;


	Vec3 GetDirection()
	{
		Vec3 re;

		const Vec2 dirX = Circular{ 1.0, angleX };

		// 球とレイを使ってFPS視点でのカメラを制御する
		Sphere sphere{ Vec3(0.0, 0.0, 0.0),0.5 };
		Vec3 rayS(dirX.x, angleYvalue, dirX.y);
		Vec3 rayDirection(-dirX.x, 0.0, -dirX.y);
		rayDirection.normalize();
		Ray ray{ rayS,rayDirection };

		const auto distance = ray.intersects(sphere);
		const auto intersectPoint = ray.intersectsAt(sphere);
		if (intersectPoint)
			re = intersectPoint.value();
		else
			re = Vec3(0.0, 1.0, 0.0);


		//return Vec3(1.0, 0.0, 0.0);
		return re;
	}

	void AddDirectionX(float magnification)
	{
		double def_variation_x = Scene::DeltaTime() * 30_deg;
		angleX += def_variation_x * magnification * sensitivity;

		if (360_deg < angleX)
		{
			angleX -= 360_deg;
		}
		if (angleX < 0_deg)
		{
			angleX += 360_deg;
		}
	}

	void AddDirectionY(float magnification)
	{
		double def_variation_y = Scene::DeltaTime() * 0.1;
		angleYvalue += def_variation_y * magnification * sensitivity;
		if (angleYvalue > 0.49)
			angleYvalue = 0.49;
		if (angleYvalue < -0.49)
			angleYvalue = -0.49;
	}

	void SetSensitivity(float value)
	{
		sensitivity = value;
	}

	Vec3 GetFocusPosition(const Vec3& eyePosition)
	{
		return (eyePosition + GetDirection());
	}

};
