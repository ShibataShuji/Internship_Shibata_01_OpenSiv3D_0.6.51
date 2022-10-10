#pragma once

// ゲームデータ用
// シーンにあるゲームオブジェクトのリストと管理関数
struct GD_GameObjectListData
{
	Array<GameObject*> GameObjectList;


	void UpdateGameObjectList()
	{
		if (!GameObjectList.empty())
		{
			for (auto GameObject : GameObjectList)
			{
				GameObject->Update();
			}
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

		return gameObject;		// 生成したインスタンスのポインタが入っている
	}

	Array<GameObject*> GetGameObjectList()
	{
		return GameObjectList;
	}


};
