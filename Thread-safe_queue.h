#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>

// Thread-safe queue
template <class T>
class TSQueue
{
public:
	
	void push(T item)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(item);
		_cond.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock,
			[this]() { return !_queue.empty(); });
		T item = _queue.front();
		_queue.pop();

		return item;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lg(_mutex);
		return _queue.empty();
	}

private:
	std::queue<T> _queue;
	mutable std::mutex _mutex;
	std::condition_variable _cond;
};