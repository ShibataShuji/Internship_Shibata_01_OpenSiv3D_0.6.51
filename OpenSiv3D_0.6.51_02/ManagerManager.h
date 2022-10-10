#pragma once

// シーンの前方宣言
//enum class State;
struct GameData;
//using App = SceneManager<State, GameData>;

class ManagerManager
{
private:
	// static のメンバ変数はcpp側でもう一度宣言してあげないといけない
	// ↓class をつけてるのは前方宣言。これならヘッダーをincludeしなくてよくなる！！！
	// staticつけるとグローバル変数のように使える
	// class はポインタ変数にしか使えない。
	// includeだと循環呼び出しされちゃってエラー出るから、ポインタ変数なら classで解決してあげて、
	// それでもだめなら気を付けながらインクルードを使う

	//static class SceneManager<State, GameData>* m_Scene;
	//static enum class State*			m_State;
	static struct GameData*				m_GameData;

public:
	//static class SceneManager<State, GameData>* GetScene() { return m_Scene; }
	//static void SetScene(SceneManager<State, GameData>* scene) { m_Scene = scene; }

	//static enum class State* GetState() { return m_State; }
	//static void SetState(State* state) { m_State = state; }

	static struct GameData* GetGameData() { return m_GameData; }
	static void SetGameData(GameData* gamedata) { m_GameData = gamedata; }


};
