#pragma once
#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

#include <chrono>

class ThreadPool
{
	bool active;
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks_queue;

	std::mutex mutex;
	std::condition_variable cv;
public:
	explicit ThreadPool(size_t poolSize) : active(true) 
	{
		for (size_t i = 0; i < poolSize; ++i) 
		{
			workers.emplace_back([this]() 
			{
				while(true)
				{
					std::unique_lock<std::mutex> lock(this->mutex);
					this->cv.wait(lock, [this](){ return !(this->active && this->tasks_queue.empty());});
					if (!this->active && this->tasks_queue.empty()) return;
					auto task = std::move(this->tasks_queue.front());
					this->tasks_queue.pop();
					task();
				}
			});
		}
	}

	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> 
	{
		using return_type = typename std::result_of<Func(Args...)>::type;
		auto task = std::make_shared<std::packaged_task<return_type()> >( std::bind(func, args...) );
		{
			std::unique_lock<std::mutex> lock(mutex);

			if(!active) throw std::runtime_error("ThreadPool is stopped");

			tasks_queue.emplace([task](){ (*task)(); });
		}
		cv.notify_one();
		return task->get_future();
	}

	 ~ThreadPool()
	{
		active = false;
		cv.notify_all();
		for (auto & worker : workers) 
		{
			worker.join();
		}
	}
};
