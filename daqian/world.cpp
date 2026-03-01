/*
	world.cpp 世界的实现
*/

#include "world.h"

#include <chrono>
#include <thread>

namespace Nirvana
{
	BigWorld::BigWorld():m_bRunning(false),m_bLiveTime(0)
	{
		// 构造时不启动线程
	}

	BigWorld::~BigWorld()
	{
		// 确保析构时线程已停止并已 join
		Shutdown();
	}


	bool BigWorld::StartUp()
	{
		// 如果已经运行，直接返回
		bool expected = false;
		if (!m_bRunning.compare_exchange_strong(expected, true))
		{
			return true;
		}

		m_bLiveTime = 0;

		// 启动线程循环
		m_thread = std::thread(&BigWorld::RunLoop, this);
		return true;
	}

	bool BigWorld::Shutdown()
	{
		// 如果未运行，直接返回
		bool expected = true;
		if (!m_bRunning.compare_exchange_strong(expected, false))
		{
			// 保证线程不处于 joinable 状态或者已被 join
			if (m_thread.joinable())
			{
				m_thread.join();
			}
			m_bLiveTime = 0;
			return true;
		}

		// 通知（如果将来使用条件变量）
		{
			std::lock_guard<std::mutex> lk(m_mutex);
			m_cv.notify_all();
		}

		// 等待线程退出
		if (m_thread.joinable())
		{
			m_thread.join();
		}

		m_bLiveTime = 0;
		return true;
	}

	void BigWorld::RunLoop()
	{
		using namespace std::chrono_literals;

		// 简单节拍：每 ~16ms 执行一次 tick（大约 60Hz）
		while (m_bRunning.load())
		{
			// 执行一次世界更新（这里只做示例：累加生存时间）
			++m_bLiveTime;

			// 等待或睡眠，允许通过条件变量更快退出（目前仅使用 sleep）
			std::this_thread::sleep_for(16ms);


		}
	}
}