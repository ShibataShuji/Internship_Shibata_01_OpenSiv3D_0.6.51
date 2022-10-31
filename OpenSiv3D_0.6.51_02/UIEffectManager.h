

// ボツ

//#pragma once
//
//
//class UIEffectManager
//{
//private:
//	UIEffectManager();
//	~UIEffectManager() {}
//
//	// 宣言
//	static Array<UIEffect*> m_UIeffects;
//
//
//public:
//	static void Init()
//	{
//
//	}
//	static void Update()
//	{
//		for (auto UIeffect : m_UIeffects)
//		{
//			UIeffect->Update();
//		}
//
//		// ここでdeleteしている
//		m_UIeffects.remove_if([](UIEffect* UIeffect) {return UIeffect->Destroy(); });		// ラムダ式
//
//	}
//	static void Draw()
//	{
//		for (auto UIeffect : m_UIeffects)
//		{
//			UIeffect->Draw();
//		}
//	}
//
//	static Array<UIEffect*> GetUIeffects()
//	{
//		return m_UIeffects;
//	}
//
//	// エフェクトは、時間なくて汎用性は低い設計になっている。
//	// どのタイミングでどのエフェクトを出すかで使おう。
//	//static UIEffect* AddUIEffect(Vec2 const& center,  UIEffectType  const& uieffecttype, String const& displaystring = U"null")
//	//{
//	//	UIEffect* uieffect = new UIEffect(center, uieffecttype, displaystring);
//	//	uieffect->Init();
//	//	m_UIeffects.push_back(uieffect);
//
//	//	return uieffect;
//	//}
//
//
//	template <typename T>
//	static T* AddUIEffect(Vec2 center, String displaystring = U"null")
//	{
//		T* uieffect = new T(center, displaystring);
//		uieffect->Init();
//		m_UIeffects.push_back(uieffect);
//
//		return uieffect;
//	}
//
//
//
//};
