#pragma once
// 通用定义
// 底层的共用定义都放在这个文件，方便查找

namespace Nirvana
{
	constexpr int INIT_ = 100;



#pragma region 基本设定



	/// <summary>
	/// 角色种类
	/// </summary>
	enum class CharacterType
	{
		HUMAN,		// 人类
		ANIMAL,		// 动物
		PLANT,		// 植物
		SPIRIT,		// 灵体
		GHOST,		// 鬼怪
	};

	/// <summary>
	/// 职业
	/// </summary>
	enum class Career
	{
		Farmer,		// 农民
		Saler,		// 商人
		Soilder,	// 士兵
	};


	enum class Camp
	{
		Adjustice,	// 正道
		Devil,		// 魔道
	};

#pragma endregion

#pragma region 修仙设定

	/// <summary>
/// 境界划分
/// </summary>
	enum class ExprienceStep
	{
		NORMAL,		// 凡人

		LIANQI,		// 练气
		ZHUJI,		// 筑基
		JIEDAN,		// 结丹
		YUANYING,	// 元婴
		HUASHEN,	// 化神
		LIANXU,		// 练虚
		HETI,		// 合体
		DACHENG,	// 大乘

		ZHENXIAN,	// 真仙
	};

	/// <summary>
	/// 角色
	/// </summary>
	enum class Character
	{
		YeFan,		// 叶凡
		LiuRuYan,	// 柳如烟
		XiaoYan,	// 萧衍 萧炎
	};

#pragma endregion

#pragma region 经济系统

	enum class Currency
	{
		Gold,			// 金币
		GhostStone,		// 灵石
	};

#pragma endregion


#pragma region 世界设定

	/// <summary>
	/// 地表类型
	/// </summary>
	enum class MapSurfaceType
	{
		LAND,		// 陆地
		SEA,		// 海洋
		SAND,		// 沙漠
		ISLAND,		// 岛屿
	};



	/// <summary>
	/// 空间类型
	/// </summary>
	enum class SpaceType
	{
		Planes,		// 位面
		Region,		// 领域 或宇宙(例如：秘境)  是一个最大的独立空间
		Contient,	// 大陆（洲）
		State,		// 州（王国） 青州 幽州
		Moutain,	// 山川 （各宗门就属于这一级，例如：蜀山）
		Village,	// 村庄
	};

#pragma endregion

}