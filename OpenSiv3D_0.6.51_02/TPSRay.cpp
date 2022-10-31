#include "stdafx.h"



// 定義
//ColorF TPSRay::backgroundColor;// = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
//Texture TPSRay::uvChecker;// = Texture{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
//MSRenderTexture TPSRay::renderTexture;// = MSRenderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };


BasicCamera3D TPSRay::m_Camera = BasicCamera3D{ Size(1920,1080), 30_deg, Vec3{0, 16, -32}, Vec3{0, 0, 1}};
FPSCamera	  TPSRay::m_fpscamera;

Ray			   TPSRay::m_Ray = Ray{ Vec3(0,0,0), Vec3(1,0,0) };
Sphere		   TPSRay::m_RaySphere = Sphere{ Vec3(0,0,0), 0.3 };
Optional<Vec3> TPSRay::m_intersectsAt;
GameObject*	   TPSRay::m_HitGameObject;
Vec3		   TPSRay::m_HitNormal;
float		   TPSRay::m_Radius = 40.0f;



void TPSRay::RayInit()
{
	m_Camera = BasicCamera3D{ Scene::Size(), 30_deg, Vec3{0, 16, -32}, Vec3{0, 0, 1} };

	m_Ray = Ray{ Vec3(0,0,0), Vec3(1,0,0) };
	m_RaySphere = Sphere{ Vec3(0,0,0), 0.3 };
}

void TPSRay::RayUpdate()
{
	// リセット
	m_intersectsAt.reset();
	m_HitGameObject = nullptr;

	// -nanになっていたらりたーん
	if (m_Ray.direction.hasNaN() || m_Ray.origin.hasNaN())
		return;

	// レイを作る
	/*const Ray ForGetDirectRay = m_Camera.screenToRay(Scene::Center());
	Vec3 rayD = ForGetDirectRay.getDirection();*/

	//Vec3 RayS = m_Player->GetPosition();
	//RayS.y += 0.5;
	//Vec3 RayF = RayS + rayD * 100;
	//Vec3 RayDirect = RayF - RayS;
	//RayDirect.normalize();
	//m_Ray = Ray{ RayS , RayDirect };

	// 作ったレイで当たっているオブジェクトを探す
	Component* IntersectCollisionComponent = nullptr;
	double minDistance = Math::Inf;
	for (auto gamobj : ManagerManager::GetGameData()->GameObjectListData.GetGameObjectList())
	{
		if (gamobj->GetName() == U"Player")
			continue;

		if (gamobj->GetName() == U"GoalObject")
			continue;

		/*if (gamobj->GetName() == U"KnifeBlock")
			continue;*/

		// 赤いブロックだったら当たらない処理。あってもなくてもいいかも。悩みどころ
		//if (gamobj->GetName() == U"KnifeBlock")
		//{
		//	if (gamobj->GetCollisionComponent()->GetColor() == KnifeBlock_HighlightColor)
		//		continue;
		//}

		for (auto comp : gamobj->GetComponentList())
		{
			Optional<double> intersects;
			if (typeid(*comp) == typeid(Collision_Box))
			{
				Collision_Box* colBox = static_cast<Collision_Box*>(comp);
				intersects = m_Ray.intersects(*colBox->GetOrientedBox());
			}
			else if (typeid(*comp) == typeid(Collision_Sphere))
			{
				Collision_Sphere* colSphere = static_cast<Collision_Sphere*>(comp);
				intersects = m_Ray.intersects(*colSphere->GetSphere());
			}
			/*else if (typeid(comp) == typeid(Collision_Capsule))
			{

			}*/

			if (intersects)
			{
				// 交差地点までの距離が近すぎてもダメにする
				if (intersects.value() < minDistance && intersects.value() > 0.5)
				{
					minDistance = intersects.value();
					IntersectCollisionComponent = comp;
					m_HitGameObject = gamobj;
				}
			}
		}
	}

	// レイが衝突していたら
	if (IntersectCollisionComponent != nullptr)
	{
		if (typeid(*IntersectCollisionComponent) == typeid(Collision_Box))
		{
			Collision_Box* colBox = static_cast<Collision_Box*>(IntersectCollisionComponent);
			m_intersectsAt = m_Ray.intersectsAt(*colBox->GetOrientedBox());


			// どの面と衝突しているかで法線を取得する
			OrientedBoxSurfaces SurfacesBox;
			CreateOrientedBoxSurfaces(colBox->GetOrientedBox(), &SurfacesBox);

			double min = Math::Inf;
			Optional<double> intersects;
			for (int i = 0; i < 6; i++)
			{
				intersects = m_Ray.intersects(SurfacesBox.m_Surfaces[i]);

				if (intersects.has_value())
				{
					if (intersects.value() < min)
					{
						min = intersects.value();
						m_HitNormal = SurfacesBox.m_Normal[i];
					}
				}
			}


		}
		else if (typeid(*IntersectCollisionComponent) == typeid(Collision_Sphere))
		{
			Collision_Sphere* colSphere = static_cast<Collision_Sphere*>(IntersectCollisionComponent);
			m_intersectsAt = m_Ray.intersectsAt(*colSphere->GetSphere());
		}
		/*else if (typeid(IntersectCollisionComponent) == typeid<Collision_Capsule*>(IntersectCollisionComponent))
		{

		}*/

		m_RaySphere.setPos(m_intersectsAt.value());
	}
	else
	{
		// 衝突していなかったら
		Vec3 spherepos = m_Ray.getOrigin() + m_Ray.getDirection() * 10;
		m_RaySphere.setPos(spherepos);
	}


}


void TPSRay::RayDraw()
{
	//Cylinder rayLine{ m_Ray.getOrigin(), m_Ray.getOrigin() + m_Ray.getDirection() * 100, 0.1 };
	//rayLine.draw(Linear::Palette::Gray);
	//m_RaySphere.draw(Linear::Palette::Red);
}
