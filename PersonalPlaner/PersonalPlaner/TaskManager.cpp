#include "TaskManager.h"
#include <algorithm>
#include "MyMutex.h"

DBManager * TaskManager::db_manager_;
std::vector<Task> TaskManager::tasks_;
void(*TaskManager::db_loaded_done_notify_)();
void(*TaskManager::db_loading_callback_)();
std::thread TaskManager::db_thread_;
Task TaskManager::next_task_to_exec_;
bool TaskManager::is_ok_;
wchar_t * TaskManager::err_msg_;
size_t TaskManager::db_elements_size_;

TaskManager::TaskManager(DBManager * db_manager)
{
	db_manager_ = db_manager;
	is_ok_ = true;
}

bool TaskManager::AddTask(Task task)
{
	//Locking function from other threads;
	MyMutex mutex;

	//Composing a request
	std::stringstream ss;
	ss << "INSERT INTO TASKS (TITLE,DEADLINE) VALUES ('" << task.GetMyEvent() << "', '" << task.GetDeadLine() << "'); ";
	std::string sql_request(ss.str());

	//In ErrorCheck there is also and err msg field available so we could make a switch by Check field and hanlde more specific errors here
	//Though studying all the errors of the SQLite3 is beyond the scope of my project, so I limited myself to a general error shown.
	ErrorCheck check = db_manager_->ExecSQLRequest(sql_request.c_str(), callbackLoadData);
	if (check.Check != SQLITE_OK) {
		is_ok_ = false;
		err_msg_ =  L"Can't add task to database";
		return false;
	}

	//adding task to array
	tasks_.push_back(task);
	findClosestTask();
	return true;
}

bool TaskManager::RemoveTask(Task task)
{
	//Locking function from other threads;
	MyMutex mutex;

	//Composing a request
	std::stringstream ss;
	ss << "DELETE FROM TASKS WHERE TITLE='" << task.GetMyEvent() << "' AND DEADLINE='" << task.GetDeadLine() << "' ;";
	std::string sql_request(ss.str());
	
	//Same comment here as in AddTask function 
	ErrorCheck check = db_manager_->ExecSQLRequest(sql_request.c_str(), callbackLoadData);
	if (check.Check != SQLITE_OK) {
		is_ok_ = false;
		err_msg_ = L"Can't remove task from database";
		return false;
	}

	//removing task from array
	//Below I need to be sure to compare task not only by deadlines (as this way it is overloaded) but by event name as well
	auto itr = std::find_if(tasks_.begin(), tasks_.end(), [task](Task task_) {return task == task_ && task.GetMyEvent() == task_.GetMyEvent(); });
	tasks_.erase(itr);
	findClosestTask();
	return true;
}

void TaskManager::Initialize()
{
	//Using flag to understand what to do
	//After that loading database in another thread for to not block UI
	if (db_manager_->IsDBExistedBefore()) {
		getDBSize();
		if(!is_ok_){
			return;
		}
		db_thread_ = std::thread(loadFromDB);
	}
	else {
		db_thread_ = std::thread(createTaskTable);
	}
}

void TaskManager::createTaskTable()
{
	//Locking function from other threads;
	MyMutex mutex;

	//If we are here that means we have a new DB and must create a table
	//Composing a request
	const char * sql = "CREATE TABLE TASKS("  \
		"ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
		"TITLE          TEXT        NOT NULL," \
		"DEADLINE       DATETIME    NOT NULL );";
	ErrorCheck check = db_manager_->ExecSQLRequest(sql, callbackLoadData);
	if (check.Check != SQLITE_OK) {
		is_ok_ = false;
		err_msg_ = L"Can't create database table";
	}

	//Notify callback function that DB is ready for using
	if (db_loaded_done_notify_ != nullptr) {
		db_loaded_done_notify_();
	}
}

void TaskManager::loadFromDB()
{
	//Locking function from other threads;
	MyMutex mutex;

	//Clearing all tasks in container if not empty
	tasks_.clear();

	// allocating space for future elements so that while adding we wouldn't reallocate memory storage and slow our programm
	tasks_.reserve(db_elements_size_);

	//Composing a request by getting all elements sorted by deadline
	//This way don't waste our resourses and store in container our tasks already sorted
	char * sql = "SELECT * FROM TASKS ORDER BY DEADLINE ASC;";
	ErrorCheck check = db_manager_->ExecSQLRequest(sql, callbackLoadData);
	if (check.Check != SQLITE_OK) {
		is_ok_ = false;
		err_msg_ = L"Can't load data from database";
	}
	
	//Setting up nearest task to be done.
	findClosestTask();

	//Notifying that DB is loaded
	if (db_loaded_done_notify_ != nullptr) {
		db_loaded_done_notify_();
	}
}

//Find and select nearest task to execute
//Class Task has overloadings for comparision by deadline
void TaskManager::findClosestTask()
{
	Task temp;
	for (size_t i = 0; i < tasks_.size(); ++i) {
		if (temp > tasks_[i]) {
			temp = tasks_[i];
		}
	}
	next_task_to_exec_ = temp;
}

//Getting DB size so we could prepare our resources to handle it
void TaskManager::getDBSize()
{
	auto * sql_request = "SELECT COUNT() FROM TASKS;";

	ErrorCheck check = db_manager_->ExecSQLRequest(sql_request, callbackLoadData);
	if (check.Check != SQLITE_OK) {
		is_ok_ = false;
		err_msg_ = L"Can't get size of database";
	}
}

//Callback function for sql request. It works for every line in database
int TaskManager::callbackLoadData(void* NotUsed, int argc, char** argv, char** azColName)
{
	if (argc <= 0) {
		return 0;
	}

	//Checking if it is COUNT() request which is just return count of elements in DB.
	//In a good way I would create another collback function for this request only but not wanted to spam code lines;
	if (strcmp(*azColName, "COUNT()") == 0) {
		db_elements_size_ = atoi(*argv);
		return 0;
	}

	//Adding a task to an array and call callback function so that UI could know what is happening here
	//Not adding mutex here for a tasks_ because it is a callback function and is already locked when we did our request above
	Task task(argv[1], argv[2]);
	tasks_.push_back(task);
	if (db_loading_callback_ != nullptr) {
		db_loading_callback_();
	}

	return 0;
}
