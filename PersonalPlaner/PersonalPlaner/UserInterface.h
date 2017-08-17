#pragma once
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <ctime>
#include <string>
#include "TaskManager.h"
#include "resource.h"

class UserInterface sealed
{
public:	
	UserInterface(TaskManager * task_manager);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	static INT_PTR Run() { return DialogBox(nullptr, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); }
private:
	static void reset_UI();
	static void notifyBDLoaded();
	static void dBCallbackLoading();
	static void fillList();
	static void initialize(HWND hWnd);
	static void removeTask(HWND hwnd);
	static void addTask(HWND hwnd);
	static void findCellAndDelete(Task task);
	static std::wstring getStrFromEditbox(HWND hwnd);

	static bool isApplicationIsReady_;
	static TaskManager * task_manager_;
	static HWND hWnd_;
	static HWND close_, list_box_, progress_application_bar_, progress_db_bar_, add_button_, remove_button_, load_button_, time_box_, date_box_, event_box_;
	static std::thread list_thread_;
	static size_t db_elements_size_, db_elements_size_load_count_;
};
