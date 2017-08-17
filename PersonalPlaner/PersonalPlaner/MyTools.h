#pragma once
#include <codecvt>
#include <regex>
#include <chrono>
#include <sstream>
#include <iomanip>

//Just my help toolbox of functins that are handy
class MyTools sealed
{
public:
	static std::wstring CharsToWchar_t(std::string str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str).c_str();
	}
	static std::string Wchar_tToChars(std::wstring str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(str).c_str();
	}

	static time_t ConvertStrToTime(const char * str)
	{
		std::regex pattern("\\s*[2][0-9][0-9][0-9]-([1][0-2]|[0][0-9])-([3][0-1]|[0-2][0-9])\\s*" \
			"([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])\\s*"
		);
		if (!std::regex_match(str, pattern)) {
			return -1;
		}

		std::tm tm = {};
		std::stringstream ss1(str);
		ss1 >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		tm.tm_isdst = 1;
		return std::mktime(&tm);
	}

	static time_t ConvertWStrToTime(const wchar_t * str)
	{
		std::wstring w_str(str);
		std::string s_str(Wchar_tToChars(w_str));
		return ConvertStrToTime(s_str.c_str());
	}

	static time_t CurrentLocalTime()
	{
		auto time_now = std::chrono::system_clock::now();
		time_t to_time_t = std::chrono::system_clock::to_time_t(time_now);
		std::tm tm = {};
		localtime_s(&tm, &to_time_t);
		return std::mktime(&tm);
	}

};
