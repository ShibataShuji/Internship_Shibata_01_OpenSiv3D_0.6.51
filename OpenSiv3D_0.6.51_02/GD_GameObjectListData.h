#pragma once

// ゲームデータ用
// シーンにあるゲームオブジェクトのリストと管理関数
struct GD_GameObjectListData
{
	Array<GameObject*> GameObjectList;
	int				   UpdateObjectNum;

	// ignorePlayerがtrueで、プレイヤーとプレイヤーの発射した弾は更新されないようになる
	void UpdateGameObjectList(bool ignorePlayer = false)
	{
		if (!GameObjectList.empty())
		{

			// このフレームでの初期化
			for (auto& GameObject : GameObjectList)
			{
				
				if (ignorePlayer)
				{
					if (GameObject->GetName() == U"Player")
						continue;

					if(GameObject->GetCreatedMe() != nullptr)
						if (GameObject->GetCreatedMe()->GetName() == U"Player")
							continue;
				}
				// 全てアップデートが１回もされてない状態に戻す
				GameObject->SetUpdateOnece(false);
			}

			// 途中でゲームオブジェクトの数が変わる可能性があるのでautoで範囲forするのはよくなかった。
			UpdateObjectNum = GameObjectList.size();
			for (int i = 0; i < UpdateObjectNum; i++)
			{

				auto& GameObject = GameObjectList[i];

				if (ignorePlayer)
				{
					if (GameObject->GetName() == U"Player")
						continue;

					if (GameObject->GetCreatedMe() != nullptr)
						if (GameObject->GetCreatedMe()->GetName() == U"Player")
							continue;
				}

				if(GameObject->UpdateOnceCheck())		// このフレームでのアップデートが1回目なら行う
					GameObject->Update();
			}
			/*for (auto& GameObject : GameObjectList)
			{
				auto GameObject = GameObjectList[0]
				String aaa = GameObject->GetName();
				GameObject->Update();
				count++;
			}*/
		}

		// デストロイの予約がされている場合リストから排除する。
		// また、Destroy関数の中で、deleteもしてあげる。
		GameObjectList.remove_if([](GameObject* object) {return object->Destroy(); });		// ラムダ式

	}

	void DrawGameObjectList()
	{
		if (!GameObjectList.empty())
		{
			for (auto GameObject : GameObjectList)
			{
				GameObject->Draw();
			}
		}
	}

	template <typename T>
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		GameObjectList.push_back(gameObject);

		UpdateObjectNum++;
		return gameObject;		// 生成したインスタンスのポインタが入っている
	}

	Array<GameObject*> GetGameObjectList()
	{
		return GameObjectList;
	}

	// 全てのゲームオブジェクトをデリーとする
	void DelteAllGameObjectList()
	{
		for (auto& GameObject : GameObjectList)
		{
			GameObject->SetDestroy();
		}
		GameObjectList.remove_if([](GameObject* object) {return object->Destroy(); });		// ラムダ式
	}

	// プレイヤーとゴールオブジェクト以外をデリートする
	void DelteAllGameObjectList_IgnorePlayerandGoal()
	{
		for (auto& GameObject : GameObjectList)
		{
			if (GameObject->GetName() == U"Player" || GameObject->GetName() == U"GoalObject")
				continue;
			GameObject->SetDestroy();
		}
		GameObjectList.remove_if([](GameObject* object) {return object->Destroy(); });		// ラムダ式
	}

};
