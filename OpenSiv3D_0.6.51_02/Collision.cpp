#include "stdafx.h"



void Collision::UpdateCollisionState()
{
	// 1フレーム前の値を保存
	m_OldPosition = m_Position;

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

	bool AllIgnore = true;
	// 自分が全てに対してIgnoreだった場合終了
	for (auto& response : m_ResponseTable)
	{
		// Ignore以外があったらその時点で先に進む
		if (response.second != ResponseType::Ignore)
			AllIgnore = false;
	}

	if (AllIgnore)
		return;


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

				}
				// Box*Sphere
				else if (SelfType == CollisionType::Box && OtherType == CollisionType::Sphere)
				{
					// Block は処理が重たいのでSphereからしかとらないようにする
					//blocked = SphereBoxBlock(OtherCollision, SelfCollision);
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

	// まず普通にOrientedBoxとSphereで衝突しているかをとる
	if (ColSphere->GetSphere()->intersects(*ColBox->GetOrientedBox()))
	{
		// 計算用にSphereとOrientedBoxを作る。最後代入を忘れないように。
		Sphere		t_sphere = *ColSphere->GetSphere();
		OrientedBox t_box = *ColBox->GetOrientedBox();

		// 衝突していたらSphereの前の座標と今の座標で変化量をとる
		Vec3 OldPos = ColSphere->GetOldPosition();
		Vec3 IgnorePos = ColSphere->GetSphere()->center;
		Vec3 ChangeValue = IgnorePos - OldPos;
		double Changelength = ChangeValue.length();

		// 衝突した瞬間まで戻す(衝突しない最後+1)

		// 分割数と１分割での値を求める
		int divnum = 1000;
		float divinversenum = 1.0 / divnum;	// 割り算使いたくないけど逆数の求め方がわからなかった
		Vec3 oneValue = ChangeValue * divinversenum;

		// 戻り値用の変数、衝突した分割番号と衝突時の座標が返ってくる
		int hitdivnum = 0;
		Vec3 hitpos = Vec3(0, 0, 0);
		CalulateDivisionToHit_Sphere_Box(OldPos, 0, divnum, oneValue, &t_sphere, &t_box, &hitdivnum, &hitpos);

		// どの面と衝突しているかを計算し、その法線ベクトルを取得する
		// 計算用に衝突した瞬間のSphereを作成
		Sphere MomentHitSphere{};
		MomentHitSphere.set(t_sphere);
		MomentHitSphere.setPos(hitpos);

		// 衝突している一番近い面の法線、衝突している面の数、最接近点(Box側)を取得する
		Array<Vec3> SurfaceNormal; int hitnum; Vec3 cp;
		Sphere_Box_GetHitSurfaceNormal(&MomentHitSphere, &t_box, &SurfaceNormal, &hitnum, &cp);

		// 残りの移動をさせる処理
		if (hitnum == 1)
		{
			// 衝突した面が1つだったらその面の法線に沿って移動させる

			// 現在のSphereのベクトルと壁の法線ベクトルから壁に沿うベクトルを求める。(長さは1ではない)
			Vec3 AlongWallVec = ChangeValue - Dot(ChangeValue, SurfaceNormal.at(0)) * SurfaceNormal.at(0);

			// 衝突直前の座標を残り時間分壁にそうように移動したものを求める
			Vec3 beforhitpos = hitpos - oneValue;	//衝突直前の座標
			int RemainingDiv = divnum - hitdivnum;	// 残りの時間
			//double RemainingRate = static_cast<double>(divnum) / RemainingDiv;	// 残りの時間の割合
			double RemainingRate = static_cast<double>(RemainingDiv) / divnum;	// 残りの時間の割合
			double RemainingLength = Changelength * RemainingRate;	// 残りの長さ

			// 最終的な座標を出す
			Vec3 FinPos = beforhitpos + AlongWallVec * RemainingLength;

			t_sphere.setPos(FinPos);
		}
		else if (hitnum >= 2)
		{
			// 衝突した面が2つ以上だったら、
			// 一番近い面から順に最終座標を計算していき、その座標で衝突がなかったらそこが正しい座標となる
			for (int i = 0; i < hitnum; i++)
			{
				// 現在のSphereのベクトルと壁の法線ベクトルから壁に沿うベクトルを求める。(長さは1ではない)
				Vec3 AlongWallVec = ChangeValue - Dot(ChangeValue, SurfaceNormal.at(i)) * SurfaceNormal.at(i);

				// 衝突直前の座標を残り時間分壁にそうように移動したものを求める
				Vec3 beforhitpos = hitpos - oneValue * 100;	//衝突直前の座標
				int RemainingDiv = divnum - hitdivnum;	// 残りの時間
				//double RemainingRate = static_cast<double>(divnum) / RemainingDiv;	// 残りの時間の割合
				double RemainingRate = static_cast<double>(RemainingDiv) / divnum;	// 残りの時間の割合
				double RemainingLength = Changelength * RemainingRate;	// 残りの長さ

				// 最終的な座標を出す
				Vec3 FinPos = beforhitpos + AlongWallVec * RemainingLength;

				t_sphere.setPos(beforhitpos);
				if (t_sphere.intersects(t_box))
				{
					Print << U"なんであたってる？"_fmt();
				}

				t_sphere.setPos(FinPos);

				// 最初と同じようにOrientedBoxと現在の座標でのSphereで衝突しているか。のチェック。
				if (t_sphere.intersects(t_box))
				{
					// 衝突していたら正しくないのでもっかい
					Print << U"しょうとつしてる"_fmt();
					FinPos = (beforhitpos + AlongWallVec * RemainingLength) + (SurfaceNormal.at(i) * RemainingLength * 0.1);
					t_sphere.setPos(FinPos);
					if (t_sphere.intersects(t_box))
					{
						Print << U"しょうとつしてる222"_fmt();
					}
					else
					{
						Print << U"かいひ！222"_fmt();
						break;
					}

					if (i == hitnum - 1)
					{
						Print << U"やばああい"_fmt();
						bool yaba = true;
						// 衝突している面のどこかの方向にすこしずらす
						for (int j = 0; j < hitnum; j++)
						{
							FinPos = (beforhitpos + AlongWallVec * RemainingLength) + (SurfaceNormal.at(j) * RemainingLength * 0.6);
							t_sphere.setPos(FinPos);
							if (t_sphere.intersects(t_box))
							{
								Print << U"しょうとつしてる333"_fmt();
							}
							else
							{
								Print << U"かいひ！333"_fmt();
								yaba = false;
								break;
							}
							// 最終的に計算してもどうしてもだめだったら
							if (yaba)
							{

								break;
							}
						}
					}
					continue;
				}
				else
				{
					// 衝突していなかったら正しいので抜ける
					Print << U"ただしいー"_fmt();
					break;
				}
			}


		}
		// m_Positionの更新もする。ここでしなきゃいけないのどうにかした方がいい。
		m_Position = t_sphere.center;
		//*ColSphere->GetSphere() = t_sphere;
		ColSphere->GetSphere()->set(t_sphere);
		//ColBox->GetOrientedBox() = t_box;
		//ColSphere->GetParentGameObject()->SetVelocity(Vec3(0, 0, 0));
		// 親のオブジェクトも移動させる
		ColSphere->GetParentGameObject()->SetPosition(m_Position);

	}
	else
	{
		// そもそも衝突していなかったら、なにもしない。

	}

	return false;
}









// 最接近点を求める。そのさいにレイを使う。また、衝突しているかどうかを返す。
bool CreateRaysandCheckCP(const Array<int>* verArray, const int& verA, const int& verB, const Sphere* sphere, const OrientedBoxSurfaces* surfaces, Vec3* ret_cp)
{
	if (verArray->includes(verA) && verArray->includes(verB))
	{
		Optional<Float3> intersectsPtA;
		Optional<Float3> intersectsPtB;
		Optional<float> intersectsDistanceA;
		Optional<float> intersectsDistanceB;
		{
			Float3 distance = surfaces->m_Corners[verB] - surfaces->m_Corners[verA];
			Ray ray = Ray{ surfaces->m_Corners[verA],distance.normalized() };
			intersectsPtA = ray.intersectsAt(*sphere);

			// 長さが辺の長さより大きかったら終了
			intersectsDistanceA = ray.intersects(*sphere);
			if (intersectsDistanceA != none)
			{
				if (pow(intersectsDistanceA.value(), 2) > distance.lengthSq())
					return false;
			}

		}
		// もし衝突していたら、逆からもレイをとばす
		if (intersectsPtA != none)
		{

			Float3 distance = surfaces->m_Corners[verA] - surfaces->m_Corners[verB];
			Ray ray = Ray{ surfaces->m_Corners[verB],distance.normalized() };
			intersectsPtB = ray.intersectsAt(*sphere);

			// 長さが辺の長さより大きかったら終了
			intersectsDistanceB = ray.intersects(*sphere);
			if (intersectsDistanceB != none)
			{
				if (pow(intersectsDistanceB.value(), 2) > distance.lengthSq())
					return false;
			}
			// 近すぎると誤差で衝突が取れない場合がある。
			if (intersectsPtB == none)
			{
				// その場合角で判定をとる
				*ret_cp = (intersectsPtA.value() + surfaces->m_Corners[verB]) * 0.5;
				if (abs(ret_cp->x) > 2.1)
					int ffff = 4;
				return true;
			}
			// そのふたつのれいの衝突点のど真ん中が最接近点となる
			*ret_cp = (intersectsPtA.value() + intersectsPtB.value()) * 0.5;
			return true;
		}
	}
	return false;
}


// 引数１のboxから６つの面を生成する
void CreateOrientedBoxSurfaces(const OrientedBox* box, OrientedBoxSurfaces* ret_surfaces)
{

	// ８つの角をセット
	std::array<Vec3, 8> Corners;
	Corners = box->getCorners();

	int co = 0;
	for (const auto& Corner : Corners)
	{
		ret_surfaces->m_Corners[co] = Corner;
		co++;
	}

	// 回転はサイズが変わるとずれてしまうので、原点での回転と座標のセットは別で計算する。


	// Boxのxyzの長さ
	Vec3 AxisLength[3]{};
	AxisLength[0] = Corners[1] - Corners[0];
	AxisLength[1] = Corners[2] - Corners[0];
	AxisLength[2] = Corners[4] - Corners[0];

	// 法線をセット
	ret_surfaces->m_Normal[0] = -AxisLength[2].normalized();
	ret_surfaces->m_Normal[1] = AxisLength[2].normalized();
	ret_surfaces->m_Normal[2] = -AxisLength[0].normalized();
	ret_surfaces->m_Normal[3] = AxisLength[0].normalized();
	ret_surfaces->m_Normal[4] = -AxisLength[1].normalized();
	ret_surfaces->m_Normal[5] = AxisLength[1].normalized();

	// それぞれの面の中心座標
	Vec3 SurfacePos[6]{ box->center, box->center, box->center, box->center, box->center, box->center };
	/*SurfacePos[0].z -= box->size.z * 0.5;
	SurfacePos[1].z += box->size.z * 0.5;
	SurfacePos[2].x -= box->size.x * 0.5;
	SurfacePos[3].x += box->size.x * 0.5;
	SurfacePos[4].y -= box->size.y * 0.5;
	SurfacePos[5].y += box->size.y * 0.5;*/	// この方法だと回転を考慮できていないので間違い

	SurfacePos[0] -= AxisLength[2] * 0.5;
	SurfacePos[1] += AxisLength[2] * 0.5;
	SurfacePos[2] -= AxisLength[0] * 0.5;
	SurfacePos[3] += AxisLength[0] * 0.5;
	SurfacePos[4] -= AxisLength[1] * 0.5;
	SurfacePos[5] += AxisLength[1] * 0.5;

	// それぞれの面のサイズ
	Vec3 SurfaceSize[6]{ box->size, box->size, box->size, box->size, box->size , box->size };
	SurfaceSize[0].z = 0;
	SurfaceSize[1].z = 0;
	SurfaceSize[2].x = 0;
	SurfaceSize[3].x = 0;
	SurfaceSize[4].y = 0;
	SurfaceSize[5].y = 0;



	// 面(OrientedBox)をセット
	for (int i = 0; i < 6; i++)
	{
		ret_surfaces->m_Surfaces[i] = OrientedBox{ SurfacePos[i], SurfaceSize[i], box->orientation };
	}
}


// 1つの面としか衝突していない場合
void Sphere_HitOneSurface(const Sphere* sphere, const OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp)
{
	// 先頭ポインタを取得
	int* hitnum = hit->data();

	// surface側の最接近点
	Optional<Float3> cp_surface{};

	// 球の真ん中からその面の-法線にレイをとばして衝突点が最接近点となる。
	// ただし、球の移動が速かったり小さかったりした場合真ん中が壁の中に埋まってる可能性があるため、レイの開始位置を
	// 壁の法線ベクトルの方向にある程度ずらしてあげる。
	Vec3 rayCenter = sphere->center;
	Vec3 rayDirection = -surfaces->m_Normal[hitnum[0]];
	rayDirection.normalize();
	rayCenter -= rayDirection * sphere->r;		// 中心が埋まってる可能性があるので半径分ずらしてあげている
	Ray ray{ rayCenter,rayDirection };

	cp_surface = ray.intersectsAt(surfaces->m_Surfaces[hitnum[0]]);
	if (!cp_surface.has_value())
		*ret_cp = sphere->center + rayDirection * sphere->r;

	// 最接近点を返す
	*ret_cp = cp_surface.value();

	// 理論上レイが当たらないことはない。
}

// 2つの面と衝突している場合
Array<int> Sphere_HitTwoSurface(Sphere* sphere, OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp)
{
	// 先頭ポインタを取得
	int* hitnum = hit->data();

	// surface側の最接近点
	Vec3 cp_surface{};


	// まず、その面達が持っている頂点番号を取得し整理する
	Array<int> VertexNum;

	for (int i = 0; i < 2; i++)
	{
		switch (hitnum[i])
		{
		case 0:
			VertexNum.push_back(0); VertexNum.push_back(1); VertexNum.push_back(2); VertexNum.push_back(3);
			break;
		case 1:
			VertexNum.push_back(4); VertexNum.push_back(5); VertexNum.push_back(6); VertexNum.push_back(7);
			break;
		case 2:
			VertexNum.push_back(0); VertexNum.push_back(2); VertexNum.push_back(4); VertexNum.push_back(6);
			break;
		case 3:
			VertexNum.push_back(1); VertexNum.push_back(3); VertexNum.push_back(5); VertexNum.push_back(7);
			break;
		case 4:
			VertexNum.push_back(2); VertexNum.push_back(3); VertexNum.push_back(6); VertexNum.push_back(7);
			break;
		case 5:
			VertexNum.push_back(0); VertexNum.push_back(1); VertexNum.push_back(4); VertexNum.push_back(5);
			break;
		default:
			break;
		}
	}
	// ユニークで同じものを消してもらう。このかんすうできえる？
	VertexNum.stable_unique();

	// その頂点番号の情報からレイを作って衝突を見てもらう。
	// 立方体の線分は12あるので12回チェックする。
	// この中で最接近点も返す
	if (CreateRaysandCheckCP(&VertexNum, 0, 1, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 0, 2, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 1, 3, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 2, 3, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 4, 5, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 4, 6, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 5, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 6, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 0, 4, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 2, 6, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 1, 5, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 3, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;

AfterGetCP:
	// 最接近点を求めた後は２面のうちどちらが球と近いかを法線から求める
	Vec3 toSphere = sphere->center - *ret_cp;	// 最接近点から球へのベクトル
	toSphere.normalize();


	// スコアを配列に入れていく
	Array<double> Scores;
	for (int i = 0; i < 2; i++)
	{
		Vec3 score = surfaces->m_Normal[hitnum[i]] - toSphere;
		Scores.push_back(score.lengthSq());
	}

	// スコアから順位付けをして、スコアの識別子をランク順にソートして入れていく
	Array<int> ScoreRank;
	int size = Scores.size();
	for (int i = 0; i < size; i++)
	{
		ScoreRank.push_back(0);

		for (int j = 0; j < size; j++)
		{
			if (Scores.at(i) > Scores.at(j))
				ScoreRank.at(i) += 1;
		}
	}

	// 近い面の順番に面の番号を入れていく
	Array<int> ClosestSurfaceRank;
	int scoresize = Scores.size();
	for (int i = 0; i < scoresize; i++)
	{
		ClosestSurfaceRank.push_back(hitnum[ScoreRank.at(i)]);
	}

	return ClosestSurfaceRank;
}


// 3つの面と衝突している場合
Array<int> Sphere_HitThreeSurface(Sphere* sphere, OrientedBoxSurfaces* surfaces, Array<int>* hit, Vec3* ret_cp)
{
	// 先頭ポインタを取得
	int* hitnum = hit->data();

	// surface側の最接近点
	Vec3 cp_surface{};


	// まず、その面達が持っている頂点番号を取得し整理する
	Array<int> VertexNum;

	for (int i = 0; i < 3; i++)
	{
		switch (hitnum[i])
		{
		case 0:
			VertexNum.push_back(0); VertexNum.push_back(1); VertexNum.push_back(2); VertexNum.push_back(3);
			break;
		case 1:
			VertexNum.push_back(4); VertexNum.push_back(5); VertexNum.push_back(6); VertexNum.push_back(7);
			break;
		case 2:
			VertexNum.push_back(0); VertexNum.push_back(2); VertexNum.push_back(4); VertexNum.push_back(6);
			break;
		case 3:
			VertexNum.push_back(1); VertexNum.push_back(3); VertexNum.push_back(5); VertexNum.push_back(7);
			break;
		case 4:
			VertexNum.push_back(2); VertexNum.push_back(3); VertexNum.push_back(6); VertexNum.push_back(7);
			break;
		case 5:
			VertexNum.push_back(0); VertexNum.push_back(1); VertexNum.push_back(4); VertexNum.push_back(5);
			break;
		default:
			break;
		}
	}
	// ユニークで同じものを消してもらう。
	VertexNum.stable_unique();

	// その頂点番号の情報からレイを作って衝突を見てもらう。
	// 立方体の線分は12あるので12回チェックする。
	// この中で最接近点も返す
	if (CreateRaysandCheckCP(&VertexNum, 0, 1, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 0, 2, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 1, 3, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 2, 3, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 4, 5, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 4, 6, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 5, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 6, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 0, 4, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 2, 6, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 1, 5, sphere, surfaces, ret_cp))
		goto AfterGetCP;
	if (CreateRaysandCheckCP(&VertexNum, 3, 7, sphere, surfaces, ret_cp))
		goto AfterGetCP;

AfterGetCP:
	// 最接近点を求めた後は3面のうちどちらが球と近いかを法線から求める
	Vec3 toSphere = sphere->center - *ret_cp;	// 最接近点から球へのベクトル
	toSphere.normalize();

	// スコアを配列に入れていく
	Array<double> Scores;
	for (int i = 0; i < 3; i++)
	{
		Vec3 score = surfaces->m_Normal[hitnum[i]] - toSphere;
		Scores.push_back(score.lengthSq());
	}

	// スコアから順位付けをして、スコアの識別子をランク順にソートして入れていく
	Array<int> ScoreRank;
	int size = Scores.size();
	for (int i = 0; i < size; i++)
	{
		ScoreRank.push_back(0);

		for (int j = 0; j < size; j++)
		{
			if (Scores.at(i) > Scores.at(j))
				ScoreRank.at(i) += 1;
		}
	}

	// 近い面の順番に面の番号を入れていく
	Array<int> ClosestSurfaceRank;
	int scoresize = Scores.size();
	for (int i = 0; i < scoresize; i++)
	{
		ClosestSurfaceRank.push_back(hitnum[ScoreRank.at(i)]);
	}

	return ClosestSurfaceRank;
}


// 衝突した面の法線、面の数、最接近点(Box側)を返す
void Sphere_Box_GetHitSurfaceNormal(Sphere* sphere, const OrientedBox* box, Array<Vec3>* ret_normal, int* ret_hitnum, Vec3* ret_cp)
{
	// まず面を作る
	OrientedBoxSurfaces SurfacesBox[6];
	CreateOrientedBoxSurfaces(box, SurfacesBox);

	Array<int> hit;
	for (int i = 0; i < 6; i++)
	{
		bool HitSurface = sphere->intersects(SurfacesBox->m_Surfaces[i]);
		SurfacesBox->m_Surfaces[i].draw(HitSurface ? Linear::Palette::Orange : Linear::Palette::White);
		if (HitSurface)
			hit.push_back(i);
	}

	// 1つの面にしか当たっていない場合
	if (hit.size() == 1)
	{
		Vec3 cp{};
		Sphere_HitOneSurface(sphere, SurfacesBox, &hit, &cp); //draw(Linear::Palette::Red);
		Sphere cp_sphere{ cp ,0.2 };
		cp_sphere.draw(Linear::Palette::Red);
		SurfacesBox->m_Surfaces[hit.data()[0]].draw(Linear::Palette::Blue);

		//*ret_normal = SurfacesBox->m_Normal[hit.data()[0]];
		ret_normal->push_back(SurfacesBox->m_Normal[hit.data()[0]]);
		*ret_cp = cp;
	}
	// 2つの面に当たっている場合
	else if (hit.size() == 2)
	{
		Vec3 cp{};
		Array<int> ClosestSurfaceArray = Sphere_HitTwoSurface(sphere, SurfacesBox, &hit, &cp); //draw(Linear::Palette::Red);
		Sphere cp_sphere{ cp ,0.2 };
		cp_sphere.draw(Linear::Palette::Red);
		//SurfacesBox->m_Surfaces[hit.data()[ClosestSurfaceArray.at(0)]].draw(Linear::Palette::Blue);// ふるいの。hitdataの識別番号をもらっていた
		SurfacesBox->m_Surfaces[ClosestSurfaceArray.at(0)].draw(Linear::Palette::Blue);

		//*ret_normal = SurfacesBox->m_Normal[ClosestSurfaceArray.at(0)];
		for (int i = 0; i < 2; i++)
			ret_normal->push_back(SurfacesBox->m_Normal[ClosestSurfaceArray.at(i)]);
		*ret_cp = cp;
	}
	//3つの面に当たっている場合
	else if (hit.size() == 3)
	{
		Vec3 cp{};
		Array<int> ClosestSurfaceArray = Sphere_HitThreeSurface(sphere, SurfacesBox, &hit, &cp); //draw(Linear::Palette::Red);
		Sphere cp_sphere{ cp ,0.2 };
		cp_sphere.draw(Linear::Palette::Red);
		SurfacesBox->m_Surfaces[ClosestSurfaceArray.at(0)].draw(Linear::Palette::Blue);

		//*ret_normal = SurfacesBox->m_Normal[ClosestSurfaceArray.at(0)];
		for (int i = 0; i < 3; i++)
			ret_normal->push_back(SurfacesBox->m_Normal[ClosestSurfaceArray.at(i)]);
		*ret_cp = cp;
	}

	*ret_hitnum = hit.size();
	Print << U"size: {}"_fmt(hit.size());
	return;


}


// 衝突した瞬間を求めるために再起させる関数。divmin,divmax は更新されていくのでconstを付けない。
void CalulateDivisionToHit_Sphere_Box(const Vec3& oldpos, int divmin, int divmax, const Vec3& oneValue, const Sphere* sphere, const OrientedBox* box, int* ret_hitdivnum, Vec3* ret_hitpos)
{
	// 0チェックのため
	if (divmax - divmin == 0)
		return;
	// 現在計算中の値は真ん中の値となる
	int nowdiv = (divmin + divmax) / 2;

	Vec3 NewPos = oldpos + (oneValue * nowdiv);

	Sphere NowSphere{ NewPos, sphere->r };

	if (NowSphere.intersects(*box))
	{
		// hitした場合、このdivnumより値が小さいところにあるので手前半分にする
		int olddivmax = divmax;
		divmax = nowdiv;

		// 値が変わっていなかったりしたら終了
		if (divmax <= divmin || divmax == olddivmax)
		{
			*ret_hitdivnum = nowdiv;
			*ret_hitpos = oldpos + (oneValue * nowdiv);
			return;
		}
		CalulateDivisionToHit_Sphere_Box(oldpos, divmin, divmax, oneValue, sphere, box, ret_hitdivnum, ret_hitpos);
	}
	else
	{
		// hitしなかった場合、このdivnumより値が大きいところにあるので奥の半分にする
		int olddivmin = divmin;
		divmin = nowdiv;

		// 値が変わっていなかったりしたら終了
		if (divmin >= divmax || divmin == olddivmin)
		{
			*ret_hitdivnum = nowdiv + 1;
			*ret_hitpos = oldpos + (oneValue * (nowdiv + 1));
			return;
		}
		CalulateDivisionToHit_Sphere_Box(oldpos, divmin, divmax, oneValue, sphere, box, ret_hitdivnum, ret_hitpos);
	}
}
