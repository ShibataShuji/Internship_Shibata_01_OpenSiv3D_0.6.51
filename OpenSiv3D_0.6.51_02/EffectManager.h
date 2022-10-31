#pragma once


class EffectManager
{
private:
	EffectManager();
	~EffectManager() { delete this; }

	// 宣言
	static Effect* m_effect;
	static float m_ElapsedTime;


public:
	static void Init()
	{

		if (m_effect != nullptr)
		{
			m_effect->clear();

			delete m_effect;
		}

		m_effect = new Effect;
		
	}
	static void DrawAndUpdate()
	{
		m_effect->update();
	}

	static void Draw2DAndUpdate()
	{
		m_effect->update();
	}

	static Effect* GetEffect()
	{
		return m_effect;
	}

};



struct BubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	Vec2 m_pos;

	Array<Bubble> m_bubbles;

	BubbleEffect(const Vec2& pos, double baseHue)
		: m_pos{ pos }
	{
		for (int32 i = 0; i < 8; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{30}),
				.startTime = Random(-0.3, 0.1), // 登場の時間差
				.scale = Random(0.1, 1.2),
				.color = HSV{ baseHue + Random(-30.0, 30.0) }
			};
			m_bubbles << bubble;
		}
	}

	bool update(double t) override
	{
		for (const auto& bubble : m_bubbles)
		{
			const double t2 = (bubble.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Circle{ (m_pos + bubble.offset + (bubble.offset * 4 * t)), (e * 40 * bubble.scale) }
				.draw(ColorF{ bubble.color, 0.15 })
				.drawFrame((30.0 * (1.0 - e) * bubble.scale), bubble.color);
		}

		return (t < 1.3);
	}
};



struct BulletEffect_Hit : IEffect
{
	struct Bullet
	{
		Vec3 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	Vec3 m_pos;

	Array<Bullet> m_bullets;

	BulletEffect_Hit(const Vec3& pos, double baseHue)
		: m_pos{ pos }
	{
		for (int32 i = 0; i < 32; ++i)
		{
			Bullet bullet{
				.offset = RandomVec3insideUnitSphere() * 0.8,
				.startTime = Random(-0.3, 0.1), // 登場の時間差
				.scale = Random(0.1, 0.3),
				.color = HSV{ baseHue + Random(-30.0, 30.0) }
			};
			m_bullets << bullet; 
		}
	}

	bool update(double t) override
	{
		for (const auto& bullet : m_bullets)
		{
			const double t2 = (bullet.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			//// 時間を割合にする
			//double t3;
			//if (t2 != 0.0)
			//	t3 = 1.0 / t2;
			//else
			//	t3 = 0.0;

			const double e = EaseOutExpo(t2);

			Sphere{ (m_pos + bullet.offset + (bullet.offset * 4 * t)), (e * 1 * bullet.scale) }
			.draw(ColorF{ bullet.color, 0.15 });
		}

		// ここで消えるまでの時間を設定
		return (t < 0.7);
	}
};


struct BulletEffect_WithBullet : IEffect
{
	struct Bullet
	{
		Vec3 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	Vec3 m_pos;

	Array<Bullet> m_bullets;

	BulletEffect_WithBullet(const Vec3& pos, double baseHue)
		: m_pos{ pos }
	{
		for (int32 i = 0; i < 4; ++i)
		{
			Bullet bullet{
				.offset = RandomVec3insideUnitSphere() * 0.15,
				.startTime = Random(-0.25, 0.07), // 登場の時間差
				.scale = Random(0.05, 0.10),
				.color = HSV{ baseHue + Random(-30.0, 30.0) }
			};
			m_bullets << bullet;
		}
	}

	bool update(double t) override
	{
		for (const auto& bullet : m_bullets)
		{
			const double t2 = (bullet.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			//// 時間を割合にする
			//double t3;
			//if (t2 != 0.0)
			//	t3 = 1.0 / t2;
			//else
			//	t3 = 0.0;

			const double e = EaseOutExpo(t2);

			Sphere{ (m_pos + bullet.offset + (bullet.offset * 4 * t)), (e * 1 * bullet.scale) }
			.draw(ColorF{ bullet.color, 0.15 });
		}

		// ここで消えるまでの時間を設定
		return (t < 0.3);
	}
};


struct UIEffect_DisplayString : IEffect
{
	struct DisplayString
	{
		Vec2 offset;
		double startTime;
		double scale;
		ColorF color;
		String displaystring;
	};

	Vec2 m_pos;

	Array<DisplayString> m_strings;


	UIEffect_DisplayString(const Vec2& pos, double baseHue, const String& string)
		: m_pos{ pos }
	{
		for (int32 i = 0; i < 1; ++i)
		{
			DisplayString strings{
				.offset = Vec2(0,0), // RandomVec2(Circle{30}),
				.startTime = 0.0,
				.scale = 0.30,  //Random(0.05, 0.10),
				.color = HSV{ baseHue + Random(-30.0, 30.0) },
				.displaystring = string
			};
			m_strings << strings;
		}
	}

	bool update(double t) override
	{

		for (const auto& strings : m_strings)
		{
			const double t2 = (strings.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			//const double e = EaseOutExpo(t2);


			////double t3 = (strings.startTime + t);
			//double t3 = t;

			//float alfa = 0.0f;
			//// aの計算
			//{
			//	float P1 = 0.3;
			//	float EndP = 1.1;

			//	if (t3 <= 0)
			//	{
			//		alfa = 0.0;
			//	}
			//	else if (t3 < P1)
			//	{
			//		double wariai = t3 / P1;
			//		alfa = EaseOutExpo(wariai);
			//	}
			//	else if (t3 < EndP)
			//	{
			//		double sectiontime = t3 - P1;
			//		double sectionlength = EndP - P1;

			//		double wariai = sectiontime / sectionlength;
			//		alfa = EaseOutExpo(wariai);
			//	}
			//	else
			//	{
			//		alfa = 0.0f;
			//		// 終了
			//	}
			//	alfa = 1.0f;

			//}

			float size = 250;
			//Vec2 center = (m_pos + strings.offset + (strings.offset * 4 * t));
			Vec2 center = Scene::Center();
			ColorF color = Linear::Palette::White;
			//color.a = alfa;

			FontAsset(U"TitleFont")(strings.displaystring)
				.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), size, center, color);



		}

		// ここで全部が消えるまでの時間を設定。それぞれが消えるのよりちょっと時間多めにしておくとOK
		return (t < 1.3);
	}
};




// バレットブロックが消えるときに、見た目だけの偽物を出す
struct Effect_DeleteBulletBlock : IEffect
{
	struct BulletBlock
	{
		Vec3 offset;
		double startTime;
		double scale;
		ColorF color;
		OrientedBox m_Orientedbox;
		ColorF m_Color;
		double m_deletetime;
	};

	double deletetime = 0.3;

	Array<BulletBlock> m_bulletblocks;

	Effect_DeleteBulletBlock(OrientedBox* orientedbox, ColorF color, double &deletetime)
	{

		for (int32 i = 0; i < 1; ++i)
		{
			BulletBlock bulletblock{
				.offset = Vec3(0,0,0),//RandomVec3insideUnitSphere() * 0.15,
				.startTime = 0, //Random(-0.25, 0.07), // 登場の時間差
				.scale = Random(0.05, 0.10),
				.color = Linear::Palette::White,//HSV{ baseHue + Random(-30.0, 30.0) }
				.m_Orientedbox = *orientedbox,
				.m_Color = color,
				.m_deletetime = deletetime,
			};
			m_bulletblocks << bulletblock;
		}
	}

	bool update(double t) override
	{
		for (const auto& bulletblock : m_bulletblocks)
		{
			const double t2 = (bulletblock.startTime + t);

			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			//// 時間を割合にする
			//double t3;
			//if (t2 != 0.0)
			//	t3 = 1.0 / t2;
			//else
			//	t3 = 0.0;

			const double e = EaseOutExpo(t2);

			// OrientedBoxを表示する
			bulletblock.m_Orientedbox.draw(bulletblock.m_Color);

			deletetime = bulletblock.m_deletetime;
		}

		// ここで消えるまでの時間を設定
		return (t < deletetime);
	}
};
