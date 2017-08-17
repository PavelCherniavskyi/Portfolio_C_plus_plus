#include "DBManager.h"
#include <io.h>
#include "MyMutex.h"

DBManager::DBManager(): db_(nullptr), is_existed_before(false)
{
	//Checking if file is exist to know further behaviour 
	//whether we can try load data or create a new table with understanding it is empty a priori 
	if (_access("PersonalPlanerDB(100).db", 0) != -1){
		is_existed_before = true;
	}

	//Loading DB or creating a new one if DB is not found in folder
	error_check_.Check = sqlite3_open("PersonalPlanerDB(100).db", &db_);
}

//Wrapper for sqlite3_exec
ErrorCheck DBManager::ExecSQLRequest(const char* sql, int(* callback)(void*, int, char**, char**))
{
	error_check_.Check = sqlite3_exec(db_, sql, callback, nullptr, &error_check_.Err_msg);
	if(error_check_.Check != SQLITE_OK){
		//Frees memory previously obtained from sqlite3_exec
		sqlite3_free(error_check_.Err_msg);
	}

	return error_check_;
}
