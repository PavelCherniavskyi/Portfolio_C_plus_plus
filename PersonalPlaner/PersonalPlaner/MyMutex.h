#pragma once
#include <mutex>

class MyMutex
{
public:
	MyMutex() { mutex_.lock(); }
	~MyMutex() { mutex_.unlock(); }
private:
	static std::mutex mutex_;
};



