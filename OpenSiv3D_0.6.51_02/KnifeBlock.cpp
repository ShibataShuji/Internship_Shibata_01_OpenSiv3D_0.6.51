#include "stdafx.h"


void KnifeBlock::Init()
{
	
}


void KnifeBlock::Uninit()
{

}


void KnifeBlock::Update()
{
	GameObject::Update();		// 最初に持ってくる

	AddPosition(GetVelocity());

	OrientedBox box = OrientedBox{ GetPosition(), m_Size, GetQuaternion() }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());



	//}
	Array<GameObject*> GameObjectList = ManagerManager::GetGameData()->GameObjectListData.GetGameObjectList();
	for (auto gameobject : GameObjectList)
	{
		if (gameobject == this)
			continue;

		OrientedBox other = OrientedBox{ gameobject->GetPosition(), gameobject->m_Size, gameobject->GetQuaternion()};

		bool hit = box.intersects(other);

		if (hit)
		{
			SetVelocity(Vec3(0, 0, 0));
			break;
		}

	}

	GameObject::ComponentUpdate();		// 最後に持ってくる
}


void KnifeBlock::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

	// テスト用
	//Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
	//OrientedBox{ Vec3{0, 2, 0}, 4, Quaternion::RotateY(1.5 * 30_deg) }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());


	OrientedBox box = OrientedBox{ GetPosition(), m_Size, GetQuaternion() }.draw(Linear::Palette::Aqua);




}
