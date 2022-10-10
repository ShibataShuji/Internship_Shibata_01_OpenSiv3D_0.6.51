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

	Vec3 eyePosition{ 0, 2, -16 };
	FPSCamera fpscamera;
	BasicCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, fpscamera.GetFocusPosition(eyePosition) };

};
