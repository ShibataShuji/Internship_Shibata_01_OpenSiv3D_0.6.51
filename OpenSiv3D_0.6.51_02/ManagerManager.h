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



//クォータニオンを回転行列にする
static Mat4x4 QuaternionToMatrix(const Quaternion &q)
{
	Mat4x4 ret = Mat4x4::Identity();

	float sx = q.getX() * q.getX();
	float sy = q.getY() * q.getY();
	float sz = q.getZ() * q.getZ();
	float cx = q.getY() * q.getZ();
	float cy = q.getX() * q.getZ();
	float cz = q.getX() * q.getY();
	float wx = q.getW() * q.getX();
	float wy = q.getW() * q.getY();
	float wz = q.getW() * q.getZ();

	ret = Mat4x4::Set(
	1.0f - 2.0f * (sy + sz),
	2.0f * (cz + wz),
	2.0f * (cy - wy),
		0.0f,
	2.0f * (cz - wz),
	1.0f - 2.0f * (sx + sz),
	2.0f * (cx + wx),
		0.0f,
	2.0f * (cy + wy),
	2.0f * (cx - wx),
	1.0f - 2.0f * (sx + sy),
		0.0f,
	0.0f,
	0.0f,
	0.0f,
		1.0f
	);
	return ret;
}
