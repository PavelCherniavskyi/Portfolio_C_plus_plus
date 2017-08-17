#pragma once
#ifndef PERSONAL_PLANER_DBMANAGER_H_
#define PERSONAL_PLANER_DBMANAGER_H_
#include "sqlite3.h"
#include "ErrorCheck.h"

class DBManager sealed
{
public:
	explicit DBManager();

	~DBManager(){ sqlite3_close(db_); }

	ErrorCheck GetLastErrorCheck() const { return error_check_; }
	bool IsDBExistedBefore() const { return is_existed_before; }
	ErrorCheck ExecSQLRequest(const char *sql, int(*callback)(void*, int, char**, char**));
private:
	sqlite3 * db_;
	bool is_existed_before;
	ErrorCheck error_check_;
};

#endif // PERSONAL_PLANER_DBMANAGER_H_
