#pragma once
#ifndef PERSONAL_PLANER_TASK_MANAGER_H_
#define PERSONAL_PLANER_TASK_MANAGER_H_
#include <Windows.h>
#include "DBManager.h"
#include "Task.h"
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include "MyMutex.h"

class TaskManager sealed
{
public:
	TaskManager(DBManager * db_manager);
	static bool AddTask(Task task);
	static bool RemoveTask(Task task);
	static void AddDBLoadinDoneNotification(void(*notify)()) { db_loaded_done_notify_ = notify; }
	static void AddDBLoadinCallback(void(*notify)()) { db_loading_callback_ = notify; }
	static void Initialize();
	static bool IsOperationWasOK() { return is_ok_; }
	static void JoinDBThread() { db_thread_.join(); }
	static std::vector<Task> & GetTasks() { return tasks_; }
	static wchar_t * GetLastErrMsg() { return err_msg_; }
	static Task GetNextTaskToExecute() { return next_task_to_exec_; }
	static size_t GetDBSizeOfElements() { return db_elements_size_; }
	static size_t GetSizeOfTasks() { MyMutex mutex; return tasks_.size(); }
private:
	static int callbackLoadData(void *NotUsed, int argc, char **argv, char **azColName);
	static void createTaskTable();
	static void loadFromDB();
	static void findClosestTask();
	static void getDBSize();
	

	static DBManager * db_manager_;
	static std::vector<Task> tasks_;
	static Task next_task_to_exec_;
	static void(*db_loaded_done_notify_)();
	static void(*db_loading_callback_)();
	static std::thread db_thread_;
	static bool is_ok_;
	static wchar_t * err_msg_;
	static size_t db_elements_size_;
};

#endif //PERSONAL_PLANER_TASK_MANAGER_H_

