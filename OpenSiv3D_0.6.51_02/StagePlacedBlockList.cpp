#include "stdafx.h"


// ステージの番号を引数をもらってそのステージの配置をするだけ。
// ステージの番号は、0スタート。プレイヤーとゴールは引数で返す。ゴールなのか中間ポイントなのかも返す。
void Game::LoadStageToPlaceBlock(const int& stagenum, const int& midnum, Vec3* ret_spawnpos, Vec3* ret_goalpos, bool* ret_itgoal)
{

	if (stagenum == 0)
	{
		if (midnum == 0)
		{
			//// プレイヤーとゴール
			*ret_spawnpos = Vec3(0, 1, 0);
			*ret_goalpos = Vec3(0, 8, 60);
			*ret_itgoal = false;

			// スタート地点
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -5, 0));
				p_Blocks_0->SetInitScaleRate(Vec3(20, 10, 20));
			}
			// 足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -2, 25));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
			}
			// 横の壁
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(7, 5, 45));
				p_Blocks_0->SetInitScaleRate(Vec3(4, 50, 40));
			}
			// 中間地点のある足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -2, 60));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
			}
		}
		else if (midnum == 1)
		{
			//// プレイヤーとゴール
			*ret_spawnpos = Vec3(0, 8, 60);
			*ret_goalpos = Vec3(0, 21.5, 140);
			*ret_itgoal = true;
			// 中間地点のある足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -2, 60));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
			}
			// ミニ足場地帯
			{
				// 足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(-3, 0, 71));
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				}
				// 足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(4, 3, 78));
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				}
				// 足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(-5, 7, 87));
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				}
				// 足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(-5, 7, 87));
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				}
				// 足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(2, 10, 93));
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				}
				// ミニ足場のゴール足場
				{
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(0, 13.8, 111.5));
					p_Blocks_0->SetInitScaleRate(Vec3(13.5, 8.3, 8.2));
				}
			}
			// ゴール前の
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 21, 148));
				p_Blocks_0->SetInitScaleRate(Vec3(15, 35, 12));
			}



			Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_4->SetInitPosition(Vec3(10, 10, 10));
			p_Blocks_4->SetInitScaleRate(Vec3(2, 2, 2));
			p_Blocks_4->SetInitRotation(Vec3(0.314, 0, 0));
			p_Blocks_4->SetRotationSpeed(Vec3(0.0, 0, 0));


			Blocks* p_Blocks_5 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_5->SetInitPosition(Vec3(20, 10, 10));
			p_Blocks_5->SetInitScaleRate(Vec3(1.5, 1.5, 1.5));
			p_Blocks_5->SetInitRotation(Vec3(0, 0, 0));

			p_Blocks_4->AddChild(p_Blocks_5);



			Blocks* p_Blocks_8 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_8->SetInitPosition(Vec3(30, 1, 20));
			p_Blocks_8->SetInitScaleRate(Vec3(1, 5, 1));
			p_Blocks_8->SetInitRotation(Vec3(0, 0, 0));
			p_Blocks_8->SetRotationSpeed(Vec3(0.0, 0.005, 0.0));
			p_Blocks_8->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);


			Blocks* p_Blocks_9 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_9->SetInitPosition(Vec3(33, 1, 20));
			p_Blocks_9->SetInitScaleRate(Vec3(3, 1, 3));
			p_Blocks_9->SetInitRotation(Vec3(0, 0, 0));
			p_Blocks_9->SetRotationSpeed(Vec3(0.0, 0.0, 0.0));
			p_Blocks_9->GetCollisionComponent()->SetCollisionColor(Linear::Palette::Brown);

			p_Blocks_8->AddChild(p_Blocks_9);
		}
	}
	else if (stagenum == 1)
	{
		if (midnum == 0)
		{
			//// プレイヤー
			*ret_spawnpos = Vec3(0, 1, 0);
			// スタート地点
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -5, 0));
				p_Blocks_0->SetInitScaleRate(Vec3(20, 10, 20));
			}
			// 動く足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 1, 50));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 5, 10));
				p_Blocks_0->SetMoveState(Vec3(0, -2, 15), 10, 2.5);
			}
			// 足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 1, 60));
				p_Blocks_0->SetInitScaleRate(Vec3(40, 10, 10));
			}
			// 動く足場1
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-23, 2, 78));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(23, 1, 78), 10, 2.5);
			}
			// 動く足場2
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(23, 2, 94));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(-23, 1, 94), 10, 2.5, 0.2);
			}
			// 動く足場2
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-23, 2, 110));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(23, 1, 110), 10, 2.5, 0.2);
			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 3, 126));
				p_Blocks_0->SetInitScaleRate(Vec3(30, 10, 10));
			}
			// ゴール
			*ret_goalpos = Vec3(0, 9, 126);
			*ret_itgoal = false;
		}
		else if (midnum == 1)
		{
			//// プレイヤー
			*ret_spawnpos = Vec3(0, 9, 126);
			// 前回の最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 3, 126));
				p_Blocks_0->SetInitScaleRate(Vec3(30, 10, 10));
			}
			// 回転親子足場
			{
				// 子供1
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 7, 150));
				p_Blocks_0->SetInitScaleRate(Vec3(7, 6, 24));
				// 子供2
				Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_1->SetInitPosition(Vec3(0, 7, 183));
				p_Blocks_1->SetInitScaleRate(Vec3(7, 6, 24));
				// 子供3
				Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_2->SetInitPosition(Vec3(16, 7, 167));
				p_Blocks_2->SetInitScaleRate(Vec3(24, 6, 7));
				// 子供4
				Blocks* p_Blocks_3 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_3->SetInitPosition(Vec3(-16, 7, 167));
				p_Blocks_3->SetInitScaleRate(Vec3(24, 6, 7));
				// 親
				Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_4->SetInitPosition(Vec3(0, 20, 167));
				p_Blocks_4->SetInitScaleRate(Vec3(10, 50, 10));
				p_Blocks_4->SetRotationSpeed(Vec3(0.0, -0.003, 0.0));
				p_Blocks_4->AddChild(p_Blocks_0);
				p_Blocks_4->AddChild(p_Blocks_1);
				p_Blocks_4->AddChild(p_Blocks_2);
				p_Blocks_4->AddChild(p_Blocks_3);
			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 5, 201));
				p_Blocks_0->SetInitScaleRate(Vec3(30, 10, 10));
			}
			// 動く足場1
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0 + 10, 13, 209));	//(Vec3(0, 13, 209));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(0 - 10, 13, 209), 10, 2.5);
			}
			// 動く足場2
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(6, 19 - 1, 215));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(6, 19 + 7, 215), 10, 2.5);
			}
			// 動く足場3
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 25, 221 + 10));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(0, 25, 221 - 10), 10, 2.5);
			}
			// 動く足場4
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-6, 31, 227 - 10));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(-6, 31, 227 + 10), 10, 2.5);
			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 37, 235));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 6, 10));
			}

			// ゴール
			*ret_goalpos = Vec3(0, 41.5, 235);
			*ret_itgoal = true;
		}
	}
	else if (stagenum == 2)
	{
	if (midnum == 0)
	{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 1, 0);

		// スタート地点
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, -5, 0));
			p_Blocks_0->SetInitScaleRate(Vec3(20, 10, 20));
		}
		// 動く足場1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(15, 20, 6));
			p_Blocks_0->SetInitScaleRate(Vec3(10, 50, 10));
			p_Blocks_0->SetMoveState(Vec3(15, 20, 55), 10, 2.5, 8.0);
		}
		// 最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 25, 65));
			p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 10));
		}
		// ゴール
		*ret_goalpos = Vec3(0, 32.5, 65);
		*ret_itgoal = false;
	}
	else if (midnum == 1)
	{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 32.5, 65);

		// 前回の最後
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 25, 65));
			p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 10));
		}
		// 壁
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 35, 110));
			p_Blocks_0->SetInitScaleRate(Vec3(50, 50, 50));
		}
		// 足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, -1, 75));
			p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 10));
		}
		// 柱1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 10, 110));
			p_Blocks_0->SetInitScaleRate(Vec3(5, 20, 5));
		}
		// 柱2
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(18, 10, 121));
			p_Blocks_0->SetInitScaleRate(Vec3(5, 20, 5));
		}
		// 柱3
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(-0.8, 10, 129));
			p_Blocks_0->SetInitScaleRate(Vec3(5, 20, 5));
		}
		// 最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 2.5, 165));
			p_Blocks_0->SetInitScaleRate(Vec3(5, 5, 65));
		}
		// ゴール
		*ret_goalpos = Vec3(0, 6.5, 140);
		*ret_itgoal = false;
	}
	else if (midnum == 2)
	{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 6.5, 140);

		// 前回の最後
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 2.5, 165));
			p_Blocks_0->SetInitScaleRate(Vec3(5, 5, 65));
		}
		// 動く足場1~10
		{
			for (auto i : step(10))
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-40, 8 + i * 4, 200));
				p_Blocks_0->SetInitScaleRate(Vec3(30, 4, 30));
				p_Blocks_0->SetMoveState(Vec3(40, 8 + i * 4, 200), 10, 2.5, i * 1.0);
			}
		}
		// 最後
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 41, 220));
			p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
		}
		
		// ゴール
		*ret_goalpos = Vec3(0, 47.5, 220);
		*ret_itgoal = true;
	}
	}
	else if (stagenum == 3)
	{
	if (midnum == 0)
	{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 1, 0);

		// スタート地点
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, -5, 0));
			p_Blocks_0->SetInitScaleRate(Vec3(20, 10, 20));
		}
		// 壁1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(-13, 13, 25));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 30, 30));
		}
		// 壁2
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(13, 13, 55));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 30, 30));
		}
		// 動く足場1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(5, -5, 70));
			p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
			p_Blocks_0->SetMoveState(Vec3(5, -5, 180), 10, 2.5);
		}
		// 動く足場2
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(-5, -5, 180));
			p_Blocks_0->SetInitScaleRate(Vec3(10, 10, 10));
			p_Blocks_0->SetMoveState(Vec3(-5, -5, 70), 10, 2.5);
		}
		// 壁1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 25, 90));
			p_Blocks_0->SetInitScaleRate(Vec3(50, 50, 6));
		}
		// 壁2
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 25, 120));
			p_Blocks_0->SetInitScaleRate(Vec3(50, 50, 6));
		}
		// 壁3
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 25, 150));
			p_Blocks_0->SetInitScaleRate(Vec3(50, 50, 6));
		}
		// 最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 17, 199));
			p_Blocks_0->SetInitScaleRate(Vec3(30, 10, 28));
		}
		// ゴール
		*ret_goalpos = Vec3(0, 22.5, 199);
		*ret_itgoal = false;
	}
	else 	if (midnum == 1)
	{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 22.5, 199);

		// 前回最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 17, 199));
			p_Blocks_0->SetInitScaleRate(Vec3(30, 10, 28));
		}
		// 回転親子足場1
		{
			// 子供1
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 32, 240));
			p_Blocks_0->SetInitScaleRate(Vec3(30, 20, 4));
			// 子供2
			Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_1->SetInitPosition(Vec3(0, 2, 240));
			p_Blocks_1->SetInitScaleRate(Vec3(30, 20, 4));
			// 子供3
			Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_2->SetInitPosition(Vec3(0, 17, 255));
			p_Blocks_2->SetInitScaleRate(Vec3(30, 4, 20));
			// 子供4
			Blocks* p_Blocks_3 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_3->SetInitPosition(Vec3(0, 17, 225));
			p_Blocks_3->SetInitScaleRate(Vec3(30, 4, 20));
			// 親
			Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_4->SetInitPosition(Vec3(0, 17, 240));
			p_Blocks_4->SetInitScaleRate(Vec3(30, 10, 10));
			p_Blocks_4->SetRotationSpeed(Vec3(0.003, 0.0, 0.0));
			p_Blocks_4->AddChild(p_Blocks_0);
			p_Blocks_4->AddChild(p_Blocks_1);
			p_Blocks_4->AddChild(p_Blocks_2);
			p_Blocks_4->AddChild(p_Blocks_3);
		}
		//// 回転親子足場2
		//{
		//	double zurez = 35.0;
		//	double zurey = 18.0;
		//	// 子供1
		//	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		//	p_Blocks_0->SetInitPosition(Vec3(0, 42 + zurey, 240 + zurez));
		//	p_Blocks_0->SetInitScaleRate(Vec3(30, 20, 4));
		//	// 子供2
		//	Blocks* p_Blocks_1 = getData().GameObjectListData.AddGameObject<Blocks>();
		//	p_Blocks_1->SetInitPosition(Vec3(0, 12 + zurey, 240 + zurez));
		//	p_Blocks_1->SetInitScaleRate(Vec3(30, 20, 4));
		//	// 子供3
		//	Blocks* p_Blocks_2 = getData().GameObjectListData.AddGameObject<Blocks>();
		//	p_Blocks_2->SetInitPosition(Vec3(0, 27 + zurey, 255 + zurez));
		//	p_Blocks_2->SetInitScaleRate(Vec3(30, 4, 20));
		//	// 子供4
		//	Blocks* p_Blocks_3 = getData().GameObjectListData.AddGameObject<Blocks>();
		//	p_Blocks_3->SetInitPosition(Vec3(0, 27 + zurey, 225 + zurez));
		//	p_Blocks_3->SetInitScaleRate(Vec3(30, 4, 20));
		//	// 親
		//	Blocks* p_Blocks_4 = getData().GameObjectListData.AddGameObject<Blocks>();
		//	p_Blocks_4->SetInitPosition(Vec3(0, 27 + zurey, 240 + zurez));
		//	p_Blocks_4->SetInitScaleRate(Vec3(30, 10, 10));
		//	p_Blocks_4->SetRotationSpeed(Vec3(-0.005, 0.0, 0.0));
		//	p_Blocks_4->AddChild(p_Blocks_0);
		//	p_Blocks_4->AddChild(p_Blocks_1);
		//	p_Blocks_4->AddChild(p_Blocks_2);
		//	p_Blocks_4->AddChild(p_Blocks_3);
		//}
		// 最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 43.8, 259));
			p_Blocks_0->SetInitScaleRate(Vec3(30, 2, 20));
		}
		// ゴール
		*ret_goalpos = Vec3(0, 46.3, 259);
		*ret_itgoal = false;
	}
	else 	if (midnum == 2)
	{
	// プレイヤー
	*ret_spawnpos = Vec3(0, 46.3, 259);
	// 前回最後の足場
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(0, 43.8, 259));
		p_Blocks_0->SetInitScaleRate(Vec3(30, 2, 20));
	}
	// 動く足場1
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(0, 44, 272));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
		p_Blocks_0->SetMoveState(Vec3(0, 20, 320), 10, 2.5, 4.0);
	}
	// 動く足場2
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(-5, 27, 300));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
		p_Blocks_0->SetMoveState(Vec3(-27, 17, 300), 10, 2.5, 9.0);
	}
	// 柱1
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(0, 54, 306));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱2
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(-21.3, 45.5, 300));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱3
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(-19, 42, 327));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱4
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(-5.8, 39, 354));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱5
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(27.7, 36, 340));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱6
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(49.5, 33, 366));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 柱7
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(32.2, 31, 396));
		p_Blocks_0->SetInitScaleRate(Vec3(6, 50, 6));
	}
	// 最後の足場
	{
		Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
		p_Blocks_0->SetInitPosition(Vec3(20, 0, 418));
		p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 20));
	}
	// ゴール
	*ret_goalpos = Vec3(20, 4.5, 418);
	*ret_itgoal = true;
	}
	}
	else if (stagenum == 4)
	{
		if (midnum == 0)
		{
			// プレイヤー
			*ret_spawnpos = Vec3(0, 1, 0);

			// スタート地点
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -5, 0));
				p_Blocks_0->SetInitScaleRate(Vec3(20, 10, 20));
			}
			// 動く足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -3, 13));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				p_Blocks_0->SetMoveState(Vec3(0, 0, 197), 20, 5.0, 5.0);
			}
			// 動く壁達。重たいのでプレイヤーとの当たり判定消しとく
			{
				for (auto i : step(8))
				{
					double xoff = 30.0;
					double xofffin = 300.0;
					if (IsEven(i))
					{
						xoff *= -1;
						xofffin *= -1;
					}
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(Vec3(0 + xoff, 15, 90 + i * 4));
					p_Blocks_0->SetInitScaleRate(Vec3(80, 50, 4));
					p_Blocks_0->SetMoveState(Vec3(0 - xofffin, 0, 90 + i * 4), 20, 5.0, 0.0 + i * 1.0);
					Collision* col = p_Blocks_0->GetCollisionComponent();
					col->SetResponseTableOneItem(ResponseObject::BlocksPawn, ResponseType::Ignore);
					col->SetResponseTableOneItem(ResponseObject::EnemysPawn, ResponseType::Ignore);
					col->SetResponseTableOneItem(ResponseObject::ItemsPawn, ResponseType::Ignore);
					col->SetResponseTableOneItem(ResponseObject::PlayersPawn, ResponseType::Ignore);
					col->SetResponseTableOneItem(ResponseObject::PlayerBullet, ResponseType::Ignore);
					col->SetResponseTableOneItem(ResponseObject::PlayerGround, ResponseType::Ignore);
				}
			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -3, 211));
				p_Blocks_0->SetInitScaleRate(Vec3(24, 6, 24));
			}
			// ゴール
			*ret_goalpos = Vec3(0, 1.5, 211);
			*ret_itgoal = false;
		}
		else if (midnum == 1)
		{
			// プレイヤー
			*ret_spawnpos = Vec3(0, 1.5, 211);
			// 前回の最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, -3, 211));
				p_Blocks_0->SetInitScaleRate(Vec3(24, 6, 24));
			}
			// 動く足場達
			{
				//int max = 5;
				int size = 6;
				Vec3 base = Vec3(-15, 3, 196);

				int y = 0;
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 0 * size;
					Vec3 endpos = base;
					endpos.x += 5 * size;
					endpos.y = initpos.y;
					endpos.z += 0 * size;
					double delayt = 1.2;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				{
					Vec3 initpos = base;
					initpos.x += 5 * size;
					initpos.y += y * size;
					initpos.z += 5 * size;
					Vec3 endpos = base;
					endpos.x += 5 * size;
					endpos.y = initpos.y;
					endpos.z += 0 * size;
					double delayt = 3.1;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				y++;
				// 2段目
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 4 * size;
					Vec3 endpos = base;
					endpos.x += 5 * size;
					endpos.y = initpos.y;
					endpos.z += 4 * size;
					double delayt = 1.5;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				{
					Vec3 initpos = base;
					initpos.x += 5 * size;
					initpos.y += y * size;
					initpos.z += 1 * size;
					Vec3 endpos = base;
					endpos.x += 0 * size;
					endpos.y = initpos.y;
					endpos.z += 1 * size;
					double delayt = 2.6;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				y++;
				// 3段目
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 5 * size;
					Vec3 endpos = base;
					endpos.x += 0 * size;
					endpos.y = initpos.y;
					endpos.z += 0 * size;
					double delayt = 0.5;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 1 * size;
					Vec3 endpos = base;
					endpos.x += 1 * size;
					endpos.y = initpos.y;
					endpos.z += 1 * size;
					double delayt = 5.6;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				y++;
				// 4段目
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 2 * size;
					Vec3 endpos = base;
					endpos.x += 5 * size;
					endpos.y = initpos.y;
					endpos.z += 2 * size;
					double delayt = 2.1;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				{
					Vec3 initpos = base;
					initpos.x += 0 * size;
					initpos.y += y * size;
					initpos.z += 4 * size;
					Vec3 endpos = base;
					endpos.x += 5 * size;
					endpos.y = initpos.y;
					endpos.z += 4 * size;
					double delayt = 0.6;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				y++;
				// 5段目
				{
					Vec3 initpos = base;
					initpos.x += 1 * size;
					initpos.y += y * size;
					initpos.z += 0 * size;
					Vec3 endpos = base;
					endpos.x += 1 * size;
					endpos.y = initpos.y;
					endpos.z += 5 * size;
					double delayt = 1.1;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				{
					Vec3 initpos = base;
					initpos.x += 5 * size;
					initpos.y += y * size;
					initpos.z += 5 * size;
					Vec3 endpos = base;
					endpos.x += 0 * size;
					endpos.y = initpos.y;
					endpos.z += 5 * size;
					double delayt = 5.2;
					Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
					p_Blocks_0->SetInitPosition(initpos);
					p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
					p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				}
				y++;
				//// 6段目
				//{
				//	Vec3 initpos = base;
				//	initpos.x += 0 * size;
				//	initpos.y += y * size;
				//	initpos.z += 1 * size;
				//	Vec3 endpos = base;
				//	endpos.x += 5 * size;
				//	endpos.y = initpos.y;
				//	endpos.z += 1 * size;
				//	double delayt = 4.1;
				//	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				//	p_Blocks_0->SetInitPosition(initpos);
				//	p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				//	p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				//}
				//{
				//	Vec3 initpos = base;
				//	initpos.x += 0 * size;
				//	initpos.y += y * size;
				//	initpos.z += 2 * size;
				//	Vec3 endpos = base;
				//	endpos.x += 5 * size;
				//	endpos.y = initpos.y;
				//	endpos.z += 2 * size;
				//	double delayt = 0.7;
				//	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				//	p_Blocks_0->SetInitPosition(initpos);
				//	p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				//	p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				//}
				//y++;
				//// 7段目
				//{
				//	Vec3 initpos = base;
				//	initpos.x += 3 * size;
				//	initpos.y += y * size;
				//	initpos.z += 0 * size;
				//	Vec3 endpos = base;
				//	endpos.x += 3 * size;
				//	endpos.y = initpos.y;
				//	endpos.z += 5 * size;
				//	double delayt = 1.7;
				//	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				//	p_Blocks_0->SetInitPosition(initpos);
				//	p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				//	p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				//}
				//{
				//	Vec3 initpos = base;
				//	initpos.x += 1 * size;
				//	initpos.y += y * size;
				//	initpos.z += 5 * size;
				//	Vec3 endpos = base;
				//	endpos.x += 1 * size;
				//	endpos.y = initpos.y;
				//	endpos.z += 0 * size;
				//	double delayt = 2.9;
				//	Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				//	p_Blocks_0->SetInitPosition(initpos);
				//	p_Blocks_0->SetInitScaleRate(Vec3(6, 6, 6));
				//	p_Blocks_0->SetMoveState(endpos, 10, 2.5, delayt);
				//}
				//y++;

			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 31, 246));
				p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 20));
			}

			// ゴール
			*ret_goalpos = Vec3(0, 35.5, 246);
			*ret_itgoal = false;
		}
		else if (midnum == 2)
		{
			// プレイヤー
			*ret_spawnpos = Vec3(0, 35.5, 246);
			// 前回の最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 31, 246));
				p_Blocks_0->SetInitScaleRate(Vec3(20, 6, 20));
			}
			// 下がる柱
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 20, 285));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 30, 6));
				p_Blocks_0->SetMoveState(Vec3(0, 5, 285), 10, 2.5, 4.0);
			}
			// 足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 10, 313));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 6, 10));
			}
			// ゴール
			*ret_goalpos = Vec3(0, 14.5, 313);
			*ret_itgoal = false;
		}
		else if (midnum == 3)
		{
			// プレイヤー
			*ret_spawnpos = Vec3(0, 14.5, 313);
			// 前回の最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 10, 313));
				p_Blocks_0->SetInitScaleRate(Vec3(10, 6, 10));
			}
			// 回転する柱1
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(10, 30, 333));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, 0.004, 0));
			}
			// 回転する柱2
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(10.5, 30, 351));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, 0.004, 0));
			}
			// 回転する柱3
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-2.1, 30, 368));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, -0.004, 0));
			}
			// 回転する柱4
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-12.8, 30, 390));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, -0.004, 0));
			}
			// 回転する柱5
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0.9, 30, 401));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, -0.004, 0));
			}
			// 回転する柱6
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(-12.1, 30, 413));
				p_Blocks_0->SetInitScaleRate(Vec3(6, 60, 6));
				p_Blocks_0->SetRotationSpeed(Vec3(0, -0.004, 0));
			}
			// 最後の足場
			{
				Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
				p_Blocks_0->SetInitPosition(Vec3(0, 0, 438));
				p_Blocks_0->SetInitScaleRate(Vec3(15, 6, 15));
			}
			*ret_goalpos = Vec3(0, 4.5, 438);
			*ret_itgoal = false;
		}
		else if (midnum == 4)
		{
		// プレイヤー
		*ret_spawnpos = Vec3(0, 4.5, 438);
		// 前回の最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 0, 438));
			p_Blocks_0->SetInitScaleRate(Vec3(15, 6, 15));
		}
		// 上がる足場1
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 2, 448.5));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
			p_Blocks_0->SetMoveState(Vec3(0, 30, 448.5), 18, 4.5, 6.0);
		}
		// 上がる足場2
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0 + 6, 2, 448.5));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
			p_Blocks_0->SetMoveState(Vec3(0 + 6, 30, 448.5), 18, 4.5, 6.0 + 0.2);
		}
		// 上がる足場3
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0 - 6, 2, 448.5));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
			p_Blocks_0->SetMoveState(Vec3(0 - 6, 30, 448.5), 18, 4.5, 6.0 + 0.2);
		}
		// 上がる足場4
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0 + 12, 2, 448.5));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
			p_Blocks_0->SetMoveState(Vec3(0 + 12, 30, 448.5), 18, 4.5, 6.0 + 0.4);
		}
		// 上がる足場5
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0 - 12, 2, 448.5));
			p_Blocks_0->SetInitScaleRate(Vec3(6, 2, 6));
			p_Blocks_0->SetMoveState(Vec3(0 - 12, 30, 448.5), 18, 4.5, 6.0 + 0.4);
		}
		// 最後の足場
		{
			Blocks* p_Blocks_0 = getData().GameObjectListData.AddGameObject<Blocks>();
			p_Blocks_0->SetInitPosition(Vec3(0, 30, 466.5));
			p_Blocks_0->SetInitScaleRate(Vec3(30, 2, 30));
		}
		*ret_goalpos = Vec3(0, 36.7, 466.5);
		*ret_itgoal = true;
		}
	}




}





