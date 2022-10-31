# pragma once
//# define NO_S3D_USING
# include <Siv3D.hpp>

// シーン管理のマネージャーの管理をするマネージャー。これでどっからでもアクセスできる
// 今のところゲームデータのみ。
#include "ManagerManager.h"

// 他の干渉がないデータ系
#include "SkyRender.h"
#include "EffectManager.h"
#include"FPSCamera.h"
#include "TPSRay.h"

//#include "UIEffect.h"
//#include "UIEffectManager.h"


// コンポーネント系
#include "Component.h"
#include "Collision.h"

//#include "Collision_Sub.h"	// Collisionで計算に使う関数を書いている

#include "Collision_Sphere.h"
#include "Collision_Box.h"

// ゲームオブジェクトの元
#include "GameObject.h"


// ゲームオブジェクト系
#include "EmptyObject.h"	// 空のオブジェクト。座標などは持ってるので便利
#include "Player.h"
#include "KnifeBullet.h"	// プレイヤーが発射する特殊なブロック
#include "KnifeBlock.h"		// プレイヤーが発射する特殊なブロック

#include "GoalObject.h"
#include "MidObject.h"

#include "Blocks.h"


// シーンがもつデータ系
#include "GD_GameObjectListData.h"

// ステージに配置しているブロックのリスト
#include "StagePlacedBlockList.h"

// シーン系
#include "Common.hpp"
#include "Title.hpp"
#include "Game.hpp"
