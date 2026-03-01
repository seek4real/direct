/*
	life 生命周期定义
*/
#pragma once

namespace Nirvana
{
	typedef long Time;

	/// <summary>
	/// 生命周期
	/// </summary>
	struct LifeTime 
	{
		Time dead_time;			// 死期，截止日期
		Time progress;			// 当前值(使用的值)

		/// <summary>
		/// 是否还有效
		/// 常量成员函数：c++在函数参数列表后面加const，表示常量成员函数（只读成员变量，不会修改）
		/// </summary>
		/// <returns></returns>
		inline bool isLive() const
		{
			return this->dead_time > this->progress;
		}
	};


	class Date
	{
	public:
		Date();
		~Date();

	private:
		static long InitValue;
		long value;
	};

	Date::Date():value(0L)
	{
	}

	Date::~Date()
	{
	}
}
