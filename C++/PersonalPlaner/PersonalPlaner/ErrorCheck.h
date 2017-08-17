#pragma once

struct ErrorCheck
{
	ErrorCheck() : Check(0), Err_msg(nullptr){}
	int Check;
	char * Err_msg;
};
