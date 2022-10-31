# pragma once


// シーンの名前
enum class State
{
	Title,
	Game,
};


// 共有するデータ
struct GameData
{
	GD_GameObjectListData GameObjectListData;
	int16 Title_Step = 0;

	int SelectStage = 0;
	int SelectMid = 0;
	bool itGoal = false;

	bool DebugMode = false;

	Stopwatch StopwatchData;
};









