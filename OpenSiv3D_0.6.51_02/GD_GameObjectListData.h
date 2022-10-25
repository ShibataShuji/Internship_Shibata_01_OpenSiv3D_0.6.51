#pragma once

// ゲームデータ用
// シーンにあるゲームオブジェクトのリストと管理関数
struct GD_GameObjectListData
{
	Array<GameObject*> GameObjectList;
	int				   UpdateObjectNum;

	void UpdateGameObjectList()
	{
		if (!GameObjectList.empty())
		{
			// このフレームでの初期化
			for (auto& GameObject : GameObjectList)
			{
				// 全てアップデートが１回もされてない状態に戻す
				GameObject->SetUpdateOnece(false);
			}

			// 途中でゲームオブジェクトの数が変わる可能性があるのでautoで範囲forするのはよくなかった。
			UpdateObjectNum = GameObjectList.size();
			for (int i = 0; i < UpdateObjectNum; i++)
			{
				auto& GameObject = GameObjectList[i];
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


};
