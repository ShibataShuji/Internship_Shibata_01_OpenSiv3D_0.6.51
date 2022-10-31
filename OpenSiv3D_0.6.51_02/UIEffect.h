//
//// ボツ
//
//#pragma once
//
//
//// エフェクトは、時間なくて汎用性は低い設計になっている。
//// どのタイミングでどのエフェクトを出すかで使おう。
//
//// エフェクトごとに分けるの大変だったので、下の方に
//
//class UIEffect
//{
//private:
//
//protected:
//	// deleteの予約。
//	bool m_Destroy = false;
//
//	//double m_StartTime = 0.0;
//	double m_ElapsedTime = 0.0;
//
//	Vec2 m_Center = Vec2( 0, 0);
//	String m_String = U"null";
//
//
//public:
//
//	// デフォルトは消して、引数でタイプ指定しないとだめにしておく
//	UIEffect() = delete;
//	UIEffect(Vec2 center, String displaystring = U"null")
//	{
//		m_Center = center;
//		m_String = displaystring;
//	}
//
//	~UIEffect() {}
//
//
//	virtual void Init()
//	{
//		//m_StartTime = 0.0;
//		m_ElapsedTime = 0.0;
//	}
//	//void Uninit();
//	virtual void Update()
//	{
//		m_ElapsedTime += Scene::DeltaTime();
//	}
//	virtual void Draw()
//	{
//
//	}
//
//	void SetDestroy() { m_Destroy = true; }
//	bool GetDestroy() { return m_Destroy; }
//
//	// 現在のm_Destroyの状態によってdeleteする。
//	bool Destroy()
//	{
//		if (m_Destroy)
//		{
//			delete this;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//};
//
//
//// ここから先は継承したクラス
//
//class DisplayString : UIEffect
//{
//private:
//	float alfa = 1.0f;
//public:
//
//	// 親クラスのコンストラクタをやってくれる。
//	using UIEffect::UIEffect;
//
//
//	void Init()override
//	{
//		UIEffect::Init();
//
//
//	}
//
//	void Update() override
//	{
//		UIEffect::Update();
//		float P1 = 0.2;
//		float EndP = 1.0;
//
//		if (m_ElapsedTime < P1)
//		{
//			double wariai = m_ElapsedTime / P1;
//			alfa = EaseOutExpo(wariai);
//		}
//		else if (m_ElapsedTime < EndP)
//		{
//			double sectiontime = m_ElapsedTime - P1;
//			double sectionlength = EndP - P1;
//
//			double wariai = sectiontime / sectionlength;
//			alfa = EaseOutExpo(wariai);
//		}
//		else
//		{
//			alfa = 0.0f;
//			// 終了
//			SetDestroy();
//		}
//
//	}
//
//	void Draw()override
//	{
//		UIEffect::Draw();
//
//		FontAsset(U"TitleFont")(U"BREAKOUT")
//			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });
//
//	}
//};
//
//
//
//
//
//
//
//
//
//// コピペ用
//class kopipeyou : UIEffect
//{
//private:
//
//public:
//
//	// 親クラスのコンストラクタをやってくれる。
//	using UIEffect::UIEffect;
//
//
//	void Init()
//	{
//		UIEffect::Init();
//
//
//	}
//
//	void Update()
//	{
//		UIEffect::Update();
//
//
//	}
//
//	void Draw()
//	{
//		UIEffect::Draw();
//
//
//	}
//};
