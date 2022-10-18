#include "stdafx.h"



void Collision::UpdateCollisionState()
{
	// 1フレーム前の値を保存
	m_DeltaPosition = m_Position;

	// ポジションや回転などを親を考慮して更新する
	Vec3 fff = m_ParentGameObject->GetPosition();
	m_Position = m_OffsetPosition + m_ParentGameObject->GetPosition();
	m_Rotation = m_OffsetRotation + m_ParentGameObject->GetRotation();
	m_Size = m_OffsetSize * m_ParentGameObject->GetScaleRate();
}

void Collision::Update()
{
	Component::Update();

	// 情報の更新
	UpdateCollisionState();

	// 自分が全てに対してIgnoreだった場合終了
	for (auto& response : m_ResponseTable)
	{
		// Ignore以外があったらその時点で先に進む
		if (response.second != ResponseType::Ignore)
			goto not_allIgnore;
	}
	return;
not_allIgnore:


	GameData* gamedata = ManagerManager::GetGameData();
	Array<GameObject*> GameObjectList = gamedata->GameObjectListData.GetGameObjectList();
	for (auto& OtherObject : GameObjectList)
	{

		// 自分だったらコンテニュー。同じオブジェクトが複数コリジョンコンポーネントを持っててもここで無視される
		if (OtherObject == m_ParentGameObject)
			continue;

		//// 全てのオブジェクトの中からCollisionコンポーネントを持っていなかったらコンテニュー
		//if (!OtherObject->HasComponent<Collision>())
		//	continue;

		// 相手のコンポーネントリストを取得
		Array<Component*> OtherCompList = OtherObject->GetComponentList();
		for (auto OtherComp : OtherCompList)
		{
			// コリジョンコンポーネント以外だとコンテニュー
			Collision* SelfCollision = this;
			Collision* OtherCollision = dynamic_cast <Collision*>(OtherComp);
			if (OtherCollision == nullptr)
				continue;

			// 初回アップデートがされていない場合はコンテニュー
			if (!OtherCollision->m_FirstRead)
				continue;

			// response 今回の相手との反応が入る
			ResponseType response = CheckResponseOther(OtherCollision);

			// 無視だったら終了
			if (response == ResponseType::Ignore)
				continue;

			// コリジョンタイプの取得
			CollisionType SelfType = GetCollisionType();
			CollisionType OtherType = OtherCollision->GetCollisionType();


			// Overlapの衝突判定処理。今回はSiv3Dの機能でOverlapしてるかどうかだけとる。
			if (response == ResponseType::Overlap)
			{
				bool overlaped = false;
				// Sphere*Sphere
				if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Sphere)
				{
					
				}
				// Sphere*Box
				else if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Box)
				{
					overlaped = SphereBoxOverlap(SelfCollision, OtherCollision);
				}
				// Sphere*Capsule
				else if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Capsule)
				{

				}
				// Box*Box
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Box)
				{
					overlaped = BoxBoxOverlap(SelfCollision, OtherCollision);
				}
				// Box*Sphere
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Sphere)
				{
					overlaped = SphereBoxOverlap(OtherCollision, SelfCollision);
				}
				// Box*Capsule
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Capsule)
				{

				}
				// Capsule*Capsule
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Capsule)
				{

				}
				// Capsule*Sphere
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Sphere)
				{

				}
				// Capsule*Box
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Box)
				{

				}

				if(overlaped)
					m_ParentGameObject->Collision_AddOverlapObject(OtherObject);
			}

			// Blockの衝突判定処理。Box*Boxは未実装
			if (response == ResponseType::Block)
			{
				bool blocked = false;
				// Sphere*Sphere
				if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Sphere)
				{

				}
				// Sphere*Box
				else if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Box)
				{
					blocked = SphereBoxBlock(SelfCollision, OtherCollision);
				}
				// Sphere*Capsule
				else if (SelfType == CollisionType::Sphere && OtherType == CollisionType::Capsule)
				{

				}
				// Box*Box
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Box)
				{
					//overlaped = BoxBoxOverlap(SelfCollision, OtherCollision);
				}
				// Box*Sphere
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Sphere)
				{
					blocked = SphereBoxBlock(OtherCollision, SelfCollision);
				}
				// Box*Capsule
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Capsule)
				{

				}
				// Capsule*Capsule
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Capsule)
				{

				}
				// Capsule*Sphere
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Sphere)
				{

				}
				// Capsule*Box
				else if (SelfType == CollisionType::Capsule && OtherType == CollisionType::Box)
				{

				}

				//if (blocked)
				//	m_ParentGameObject->Collision_AddOverlapObject(OtherObject);
			}




		}
	}

	return;
}


bool Collision::SphereSphereOverlap(Collision* ColA_Sphere, Collision* ColB_Sphere)
{
	Collision_Sphere* ColSphereA = static_cast <Collision_Sphere*>(ColA_Sphere);
	Collision_Sphere* ColSphereB = static_cast <Collision_Sphere*>(ColB_Sphere);

	return ColSphereA->GetSphere()->intersects(*ColSphereB->GetSphere());
}

bool Collision::SphereBoxOverlap(Collision* ColA_Sphere, Collision* ColB_Box)
{
	Collision_Sphere* ColSphere = static_cast <Collision_Sphere*>(ColA_Sphere);
	Collision_Box* ColBox = static_cast <Collision_Box*>(ColB_Box);

	return ColSphere->GetSphere()->intersects(*ColBox->GetOrientedBox());
}

bool Collision::BoxBoxOverlap(Collision* ColA_Box, Collision* ColB_Box)
{
	Collision_Box* ColBoxA = static_cast <Collision_Box*>(ColA_Box);
	Collision_Box* ColBoxB = static_cast <Collision_Box*>(ColB_Box);

	return ColBoxA->GetOrientedBox()->intersects(*ColBoxB->GetOrientedBox());
}


bool Collision::SphereBoxBlock(Collision* ColA_Sphere, Collision* ColB_Box)
{
	Collision_Sphere* ColSphere = static_cast <Collision_Sphere*>(ColA_Sphere);
	Collision_Box* ColBox = static_cast <Collision_Box*>(ColB_Box);

	if (ColSphere->GetSphere()->intersects(*ColBox->GetOrientedBox()))
	{

		Vec3 SphereCenter = ColSphere->GetSphere()->center;
		float SphereRadius = ColSphere->GetSphere()->r;

	//	// Box側でワールドマトリクスを作る
	//	Mat4x4 world, scale, rot, trans;
	//	scale = Mat4x4::Scale(Float3(ColB_Box->m_Size.x, ColB_Box->m_Size.y, ColB_Box->m_Size.z));
	//	rot = Mat4x4::RollPitchYaw<double, double, double>(ColB_Box->m_Rotation.x, ColB_Box->m_Rotation.y, ColB_Box->m_Rotation.z);
	//	trans = Mat4x4::Translate(Float3(ColB_Box->m_Position.x, ColB_Box->m_Position.y, ColB_Box->m_Position.z));
	//	world = scale * rot * trans;

	//	Vec3 ColBox_Center;   // 中心点の座標
	//	Vec3 ColBox_RotNormal[3];	// XYZ の各座標軸の傾きを表す方向ベクトル
	//	float ColBox_AxisSize[3];     // OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）

	//	ColBox_Center.x = world.value.r[3].m128_f32[0];
	//	ColBox_Center.y = world.value.r[3].m128_f32[1];
	//	ColBox_Center.z = world.value.r[3].m128_f32[2];
	//	Vec3 VecX = Vec3(world.value.r[0].m128_f32[0], world.value.r[0].m128_f32[1], world.value.r[0].m128_f32[2]);
	//	Vec3 VecY = Vec3(world.value.r[1].m128_f32[0], world.value.r[1].m128_f32[1], world.value.r[1].m128_f32[2]);
	//	Vec3 VecZ = Vec3(world.value.r[2].m128_f32[0], world.value.r[2].m128_f32[1], world.value.r[2].m128_f32[2]);
	//	/*ColBox_AxisSize[0] = ColB_Box->m_Size.x * VecX.length();
	//	ColBox_AxisSize[1] = ColB_Box->m_Size.y * VecY.length();
	//	ColBox_AxisSize[2] = ColB_Box->m_Size.z * VecZ.length();*/
	//	ColBox_AxisSize[0] = VecX.length();
	//	ColBox_AxisSize[1] = VecY.length();
	//	ColBox_AxisSize[2] = VecZ.length();

	//	ColBox_RotNormal[0] = VecX.normalize();
	//	ColBox_RotNormal[1] = VecY.normalize();
	//	ColBox_RotNormal[2] = VecZ.normalize();




	//	// distance スフィアからみたOBBへの最短距離(ベクトル)
	//	Vec3 distance;
	//	distance = cp_Box - SphereCenter;

	//	// length スフィアからOBBへの最短距離
	//	float length;
	//	length = distance.length();

	//	// overlaplength スフィアとOBBの重なっている距離
	//	float overlaplength;
	//	overlaplength = SphereRadius - length;

	//	// スフィアからみたOBBへの方向ベクトル
	//	Vec3 normal;
	//	normal = distance.normalized();
	//	ClearPrint();
	//	float rrr = ColSphere->GetSphere()->r;
	//	if (length <= SphereRadius)
	//	{
	//		Vec3 backVector = Vec3(0, 0, 0);
	//		backVector = normal * overlaplength * 1.0;	// 方向ベクトルのむきに重なっている距離分戻す

	//		Print << U"backVector: {}"_fmt(-backVector);
	//		if (!backVector.isZero())
	//		{
	//			ColA_Sphere->m_ParentGameObject->AddPosition(backVector);
	//			//ColA_Sphere->m_ParentGameObject->AddPosition(Vec3(1, 0, 0));
	//		}
	//	}



	//	Print << U"distance: {}"_fmt(distance);
	//	Print << U"length: {}"_fmt(length);
	//	//Print << U"Right: {}"_fmt(Right);

	}

	return ColSphere->GetSphere()->intersects(*ColBox->GetOrientedBox());
}


