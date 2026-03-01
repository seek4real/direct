/**
	Item 物品
*/
#pragma once
#include <string>


namespace Nirvana
{
	/// <summary>
	/// 物品
	/// </summary>
	struct Item
	{
		ItemID itemID;
		std::string name;
	};

	/// <summary>
	/// 物品ID
	/// </summary>
	struct ItemID
	{
		int id;
		int type;
	};
}