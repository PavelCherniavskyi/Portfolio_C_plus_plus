#pragma once
#ifndef PERSONAL_PLANER_TASK_H_
#define PERSONAL_PLANER_TASK_H_
#include "MyTools.h"

class Task sealed
{
public:
	Task() : Task("empty", "2099-00-00 00:00:00"){}
	Task(const char * event_name, const char * deadline);
	std::string GetMyEvent() const { return event_name_; }
	std::string GetDeadLine() const { return deadline_; }
	time_t GetDeadLineTime() const { return system_time_; }
	bool operator < (const Task other) const { return system_time_ < other.system_time_; }
	bool operator > (const Task other) const { return other.system_time_ < system_time_; }
	bool operator == (const Task other) const { return !(system_time_ < other.system_time_ || other.system_time_ < system_time_); }
private:

	std::string event_name_;
	std::string deadline_;
	time_t system_time_;
};


inline Task::Task(const char* event_name, const char* deadline)
{
	event_name_ = event_name;
	deadline_ = deadline;
	system_time_ = MyTools::ConvertStrToTime(deadline_.c_str());
}


#endif // PERSONAL_PLANER_TASK_H_

