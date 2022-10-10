# pragma once
//# define NO_S3D_USING
# include <Siv3D.hpp>

// シーン管理のマネージャーの管理をするマネージャー。これでどっからでもアクセスできる
// 今のところゲームデータのみ。
#include "ManagerManager.h"

// 他の干渉がないデータ系
#include"FPSCamera.h"

// ゲームオブジェクトの元
#include "Component.h"
#include "GameObject.h"

// ゲームオブジェクト系
#include "KnifeBlock.h"	// プレイヤーが発射する特殊なブロック

#include "Blocks.h"


// シーンがもつデータ系
#include "GD_GameObjectListData.h"

// シーン系
#include "Common.hpp"
#include "Title.hpp"
#include "Game.hpp"
