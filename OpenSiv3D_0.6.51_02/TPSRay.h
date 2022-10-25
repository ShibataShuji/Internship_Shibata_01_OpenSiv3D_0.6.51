#pragma once

class GameObject;

class TPSRay
{
private:
	TPSRay();

	// 宣言
	//static  ColorF backgroundColor;// = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	//static  Texture uvChecker;// { U"example/texture/uv.png", TextureDesc::MippedSRGB };
	//static  MSRenderTexture renderTexture;// { Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	static BasicCamera3D m_Camera;
	static FPSCamera	 m_fpscamera;

	static Ray			  m_Ray;
	static Sphere		  m_RaySphere;
	static Optional<Vec3> m_intersectsAt;
	static GameObject*	  m_HitGameObject;
	static Vec3			  m_HitNormal;

	//static Ray			  m_Ray{ Vec3(0,0,0), Vec3(1,0,0) };
	//static Sphere		  m_RaySphere{ Vec3(0,0,0), 0.3 };

public:
	static void RayInit();
	static void RayUpdate();
	static void RayDraw();



	static BasicCamera3D* GetCamera() { return &m_Camera; }
	static FPSCamera* GetFPSCamera() { return &m_fpscamera; }

	static void SetRay(const Vec3 &start, const Vec3 &direction)
	{
		m_Ray = Ray{ start, direction };
	}

	static Ray* GetRay() { return &m_Ray; }
	static Sphere* GetRaySphere() { return &m_RaySphere; }
	static Optional<Vec3>* GetintersectsAt() { return &m_intersectsAt; }
	static GameObject* GetHitGameObject() { return m_HitGameObject; }
	static Vec3* GetHitNormal() { return &m_HitNormal; }


};
