/**
	shop 商店（商品）系统
**/
#pragma once

#include "item.h"

namespace Nirvana
{
	/// <summary>
	/// 商店
	/// </summary>
	struct Shop
	{

	};

	/// <summary>
	/// 商品
	/// </summary>
	struct Goods
	{
		Item item;		// 物品
		int price;		// 售价
		int cnt;		// 数量
	};
}
