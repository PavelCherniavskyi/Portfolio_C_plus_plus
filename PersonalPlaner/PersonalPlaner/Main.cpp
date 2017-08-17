#include <windows.h> 
#include "resource.h"
#include "UserInterface.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DBManager db_manager;
	if(db_manager.GetLastErrorCheck().Check != SQLITE_OK){
		MessageBox(nullptr, L"Can't open database", L"Error", MB_ICONERROR | MB_OK);
		return 1;
	}

	TaskManager task_manager(&db_manager);
		
	UserInterface mainWnd(&task_manager);
		
	return mainWnd.Run();
}


