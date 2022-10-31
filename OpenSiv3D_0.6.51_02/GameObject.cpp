#include "stdafx.h"


// 子供の座標や回転などの計算
void GameObject::ParentChildCalculate()
{

	// スケール 掛け算
	m_ScaleRate = m_OffsetScaleRate * m_Parent->GetScaleRate();
	// 回転 足し算
	m_Rotation = m_OffsetRotation + m_Parent->GetRotation();

	// 座標は回転とスケールを考慮したものにする
	// 原点を中心として、オフセットの値分離れた場所での回転。後の座標を求める


	// スケールレートをかけて大きさ分離してあげる
	Vec3 RotateScaleRate = m_ScaleRate * m_OffsetScaleRateAdjuste;
	
	// オフセット座標で行列を作成。スケールレートの方向分もを考慮
	Mat4x4 transmat = Mat4x4::Translate(m_OffsetPosition * RotateScaleRate);
	// 現在の回転から行列を作成
	Mat4x4 rotmat = Mat4x4::RollPitchYaw<double, double, double>(GetRotation().x, GetRotation().y, GetRotation().z);
	// かけ合わせると回転を考慮した行列が出来上がる
	Mat4x4 OffsetPosmat = transmat * rotmat;

	// 行列から座標の要素だけを取り出す
	Vec3 OffsetPosition = Vec3(OffsetPosmat.value.r[3].m128_f32[0], OffsetPosmat.value.r[3].m128_f32[1], OffsetPosmat.value.r[3].m128_f32[2]);

	// 最終的な座標
	m_Position = m_Parent->GetPosition() + OffsetPosition;



}
