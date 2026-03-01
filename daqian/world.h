/*
	world.h 世界 整体的描述
*/
#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace Nirvana
{

	/// <summary>
	/// 世界：主要承担地图的承载，各种事件的调度
	/// </summary>
	class BigWorld
	{
	public:
		BigWorld();
		~BigWorld();


		bool StartUp();
		bool Shutdown();
	private:
		void RunLoop();

		std::thread m_thread;
		std::atomic<bool> m_bRunning;
		long long m_bLiveTime;

		// 预留用于将来扩展（通知/同步）
		std::mutex m_mutex;
		std::condition_variable m_cv;
	};


}
