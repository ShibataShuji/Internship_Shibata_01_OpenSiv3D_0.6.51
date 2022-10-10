#include "stdafx.h"


void Blocks::Init()
{

}


void Blocks::Uninit()
{

}


void Blocks::Update()
{
	GameObject::Update();		// 最初に持ってくる

	// テスト用
	OrientedBox box = OrientedBox{ GetPosition(), m_Size, GetQuaternion() }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());

	GameObject::ComponentUpdate();		// 最後に持ってくる
}


void Blocks::Draw()
{
	GameObject::Draw();	// 最初に持ってくる

	// テスト用
	//Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
	OrientedBox box = OrientedBox{ GetPosition(), m_Size, GetQuaternion() }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());





}
