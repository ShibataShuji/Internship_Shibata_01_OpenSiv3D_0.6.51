# pragma once

// ゲームシーン
class Game : public SceneManager<State, GameData>::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;

private:

	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	// メインとなるプレイヤー
	Player*		  m_Player;

	Vec3		  m_EyePosition{ 0, 2, -16 };

};
