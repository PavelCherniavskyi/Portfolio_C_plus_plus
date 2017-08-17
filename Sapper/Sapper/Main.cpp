//////////////////////////////////////////////////////////////////////
// CreateMyThreads.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

struct BestPlayer{
	int junior = 0;
	int middle = 0;
	int senior = 0;
} bestPlayer;

struct GameState{
	bool junior = false;
	bool middle = false;
	bool senior = false;
}gameState;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setNumbersAndBombs(HWND);
void clearEmpty(HWND, int y = 0, int x = 0);
void gameRestart(HWND);
void initializeImages(HINSTANCE);
void checkImages(HWND);
void createTimers(HWND);
void checkIfWin(HWND);
int loadSave(HWND);
void GetDesktopResolution(long&, long&);
void saveBestTime(int);


int bestTime;
int timerCount = 0;
const int ButtNumberX = 10;
const int ButtNumberY = 10;
HWND buttonsArr[ButtNumberY][ButtNumberX];
HWND timer[4], bombsCount[3];
HWND smile_button;
HBITMAP hbFlag, hbQuest, hbBomb, hbBlank, hbBlankStatic;
HBITMAP one, two, three, four, five, six, seven, eight;
HBITMAP time_0, time_1, time_2, time_3, time_4, time_5, time_6, time_7, time_8, time_9;
HBITMAP smile_good, smile_bad, smile_oops, smile_win;
HWND hStaticArr[ButtNumberY][ButtNumberX];
RECT rectWindow = { 0, 0, 400, 475 };
CHAR szClassWindow[] = TEXT("MineSwapper");
vector<int> bombs;
int flags;

#define BOMB (WM_USER+1)
#define EMPTY (WM_USER+2)
#define FLAG (WM_USER+3)
#define NUMBER (WM_USER+4)
#define SMILE (WM_USER+5)
#define TIMER_1 (WM_USER+6)
#define TIMER_2 (WM_USER+7)

//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WndProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInstance;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;

	if (!RegisterClassEx(&wcl))
		return 0;

	initializeImages(hInstance);
	GetDesktopResolution(rectWindow.left, rectWindow.top);
	
	hWnd = CreateWindowExW(0, TEXT(L"MineSwapper"), TEXT(L"MineSwapper"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom, NULL, NULL, hInstance, NULL);

	checkImages(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

VOID CALLBACK TimerProcTime(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	int thousandths, hundredth, tenths, wholes;
	HBITMAP hthousandths = NULL, hhundredth = NULL, htenths = NULL, hwholes = NULL;
	thousandths = timerCount / 1000;
	hundredth = (timerCount / 100) % 10;
	tenths = (timerCount / 10) % 10;
	wholes = timerCount % 10;

	switch (wholes){
	case 0:	hwholes = time_0; break;
	case 1: hwholes = time_1; break;
	case 2: hwholes = time_2; break;
	case 3: hwholes = time_3; break;
	case 4: hwholes = time_4; break;
	case 5: hwholes = time_5; break;
	case 6: hwholes = time_6; break;
	case 7: hwholes = time_7; break;
	case 8: hwholes = time_8; break;
	case 9: hwholes = time_9; break;
	}
	switch (tenths){
	case 0:	htenths = time_0; break;
	case 1: htenths = time_1; break;
	case 2: htenths = time_2; break;
	case 3: htenths = time_3; break;
	case 4: htenths = time_4; break;
	case 5: htenths = time_5; break;
	case 6: htenths = time_6; break;
	case 7: htenths = time_7; break;
	case 8: htenths = time_8; break;
	case 9: htenths = time_9; break;
	}
	switch (hundredth){
	case 0:	hhundredth = time_0; break;
	case 1: hhundredth = time_1; break;
	case 2: hhundredth = time_2; break;
	case 3: hhundredth = time_3; break;
	case 4: hhundredth = time_4; break;
	case 5: hhundredth = time_5; break;
	case 6: hhundredth = time_6; break;
	case 7: hhundredth = time_7; break;
	case 8: hhundredth = time_8; break;
	case 9: hhundredth = time_9; break;
	}
	switch (thousandths){
	case 0:	hthousandths = time_0; break;
	case 1: hthousandths = time_1; break;
	case 2: hthousandths = time_2; break;
	case 3: hthousandths = time_3; break;
	case 4: hthousandths = time_4; break;
	case 5: hthousandths = time_5; break;
	case 6: hthousandths = time_6; break;
	case 7: hthousandths = time_7; break;
	case 8: hthousandths = time_8; break;
	case 9: hthousandths = time_9; break;
	}

	SendMessage(timer[3], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hwholes);
	SendMessage(timer[2], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)htenths);
	SendMessage(timer[1], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hhundredth);
	SendMessage(timer[0], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hthousandths);

	timerCount++;
}

VOID CALLBACK TimerProcBomb(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	int thousandths, hundredth, tenths, wholes;
	HBITMAP hhundredth = NULL, htenths = NULL, hwholes = NULL;
	hundredth = (flags / 100) % 10;
	tenths = (flags / 10) % 10;
	wholes = flags % 10;

	switch (wholes){
	case 0:	hwholes = time_0; break;
	case 1: hwholes = time_1; break;
	case 2: hwholes = time_2; break;
	case 3: hwholes = time_3; break;
	case 4: hwholes = time_4; break;
	case 5: hwholes = time_5; break;
	case 6: hwholes = time_6; break;
	case 7: hwholes = time_7; break;
	case 8: hwholes = time_8; break;
	case 9: hwholes = time_9; break;
	}
	switch (tenths){
	case 0:	htenths = time_0; break;
	case 1: htenths = time_1; break;
	case 2: htenths = time_2; break;
	case 3: htenths = time_3; break;
	case 4: htenths = time_4; break;
	case 5: htenths = time_5; break;
	case 6: htenths = time_6; break;
	case 7: htenths = time_7; break;
	case 8: htenths = time_8; break;
	case 9: htenths = time_9; break;
	}
	switch (hundredth){
	case 0:	hhundredth = time_0; break;
	case 1: hhundredth = time_1; break;
	case 2: hhundredth = time_2; break;
	case 3: hhundredth = time_3; break;
	case 4: hhundredth = time_4; break;
	case 5: hhundredth = time_5; break;
	case 6: hhundredth = time_6; break;
	case 7: hhundredth = time_7; break;
	case 8: hhundredth = time_8; break;
	case 9: hhundredth = time_9; break;
	}

	SendMessage(bombsCount[2], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hwholes);
	SendMessage(bombsCount[1], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)htenths);
	SendMessage(bombsCount[0], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hhundredth);
}

//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, TIMER_1, 1000, TimerProcTime);
		SetTimer(hWnd, TIMER_2, 100, TimerProcBomb);
		timerCount = 0;
		setNumbersAndBombs(hWnd);
		createTimers(hWnd);
		gameState.junior = true;
		bestTime = loadSave(hWnd);
		
		break;
	case WM_PAINT:
		 hDC = BeginPaint(hWnd, &ps);
		 EndPaint(hWnd, &ps);
		break;
	case WM_PARENTNOTIFY:
			if (LOWORD(wParam) == WM_LBUTTONDOWN)
				SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_oops);
			else if (LOWORD(wParam) == WM_DESTROY)
				SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_good);
				
		break;
	case WM_COMMAND:
	{
					  DWORD id = LOWORD(wParam);
					   if (id == SMILE){
						   gameRestart(hWnd);
					   }
					   HBITMAP h = (HBITMAP)SendMessageW((HWND)lParam, BM_GETIMAGE, IMAGE_BITMAP, 0);
					   if (h == hbFlag){
						   SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_good);
						   break;
					   }

					   if (id == BOMB){
						   SendMessageW((HWND)lParam, WM_CLOSE, NULL, NULL);
						   SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_bad);
						   KillTimer(hWnd, TIMER_1);
						   KillTimer(hWnd, TIMER_2);
						   int answer = MessageBoxW(hWnd, L"\nWould you like to play again?", 
							   L"GAME OVER!", MB_YESNO | MB_ICONINFORMATION);
						   switch (answer){
						   case IDYES:
							   SetTimer(hWnd, TIMER_1, 1000, TimerProcTime);
							   SetTimer(hWnd, TIMER_2, 100, TimerProcBomb);
							   timerCount = 0;
							   gameRestart(hWnd);
							   break;
						   case IDNO:
							   SendMessageW(hWnd, WM_CLOSE, NULL, NULL);
							   if (timerCount - 1 < bestTime || bestTime == 0){
								   saveBestTime(timerCount - 1);
								   bestTime = timerCount - 1;
							   }
							   break;
						   }
					   }
					   else if (id == EMPTY){
						   clearEmpty((HWND)lParam);
					   }
					   else if (id == FLAG){
						   MessageBoxW(hWnd, L"Flag", L"", NULL);
						   break;
					   }
					   else if (id == NUMBER){
						   SendMessageW((HWND)lParam, WM_CLOSE, NULL, NULL);
					   }

					   checkIfWin(hWnd);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CONTEXTMENU:
		for (int i = 0; i < ButtNumberY; i++){
			for (int j = 0; j < ButtNumberX; j++){
				if (wParam == (WPARAM)buttonsArr[i][j]){
					HBITMAP h = (HBITMAP)SendMessageW(buttonsArr[i][j], BM_GETIMAGE, IMAGE_BITMAP, 0);
					if (h == hbBlank){
						SendMessageW(buttonsArr[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbFlag);
						flags--;
					}
					else{
						flags++;
						SendMessageW(buttonsArr[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbBlank);
					}
				}
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

void setNumbersAndBombs(HWND hWnd)
{
	//int bombNumber = (ButtNumberY * ButtNumberX) * 0.1;
	int bombNumber = 5;
	srand((unsigned int)time(NULL));
	if (!bombs.empty())
		bombs.clear();
	smile_button = CreateWindowExW(0, L"BUTTON", L"", SS_CENTER | WS_CHILD | WS_VISIBLE | BS_BITMAP,
		166, 30, 50, 50, hWnd, (HMENU)SMILE, GetModuleHandle(0), 0);
	SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_good);

	for (int i = 0; i < bombNumber; i++){
		bombs.push_back(rand() % (ButtNumberY * ButtNumberX));
	}

	flags = bombs.size();

	int count = 0;
	for (int i = 0; i < ButtNumberY; i++){
		for (int j = 0; j < ButtNumberX; j++){
			if (find(bombs.begin(), bombs.end(), count) != bombs.end()){
				hStaticArr[i][j] = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_BITMAP,
					(j * 30) + 42, (i * 30) + 100, 30, 30, hWnd, (HMENU)BOMB, GetModuleHandle(0), 0);
				SendMessage(hStaticArr[i][j], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)hbBomb);

				buttonsArr[i][j] = CreateWindowExW(0, L"BUTTON", L"", SS_CENTER | WS_CHILD | WS_VISIBLE | BS_BITMAP,
					(j * 30) + 42, (i * 30) + 100, 30, 30, hWnd, (HMENU)BOMB, GetModuleHandle(0), 0);
				SendMessageW(buttonsArr[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbBlank);
			}
			count++;
		}
	}

	for (int i = 0; i < ButtNumberY; i++){
		for (int j = 0; j < ButtNumberX; j++){
			int bombCount = 0;
			if (GetDlgCtrlID(hStaticArr[i][j]) != BOMB){
				if (GetDlgCtrlID(hStaticArr[i][j + 1]) == BOMB){
					if (j + 1 <= 9)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i + 1][j + 1]) == BOMB){
					if (i + 1 <= 9 && j + 1 <= 9)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i + 1][j]) == BOMB){
					if (i + 1 <= 9)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i + 1][j - 1]) == BOMB){
					if (i + 1 <= 9 && j - 1 >= 0)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i][j - 1]) == BOMB){
					if (j - 1 >= 0)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i - 1][j - 1]) == BOMB){
					if (i - 1 >= 0 && j - 1 >= 0)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i - 1][j]) == BOMB){
					if (i - 1 >= 0)
						bombCount++;
				}
				if (GetDlgCtrlID(hStaticArr[i - 1][j + 1]) == BOMB){
					if (i - 1 >= 0 && j + 1 <= 9)
						bombCount++;
				}

				HBITMAP temp = NULL;
				int ID;
				switch (bombCount)
				{
				case 0: temp = hbBlankStatic; ID = EMPTY; break;
				case 1: temp = one; ID = NUMBER; break;
				case 2: temp = two; ID = NUMBER; break;
				case 3: temp = three; ID = NUMBER; break;
				case 4: temp = four; ID = NUMBER; break;
				case 5: temp = five; ID = NUMBER; break;
				case 6: temp = six; ID = NUMBER; break;
				case 7: temp = seven; ID = NUMBER; break;
				case 8: temp = eight; ID = NUMBER; break;
				}
				hStaticArr[i][j] = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_BITMAP,
					(j * 30) + 42, (i * 30) + 100, 30, 30, hWnd, (HMENU)NUMBER, GetModuleHandle(0), 0);
				SendMessage(hStaticArr[i][j], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)temp);

				buttonsArr[i][j] = CreateWindowExW(0, L"BUTTON", L"", SS_CENTER | WS_CHILD | WS_VISIBLE | BS_BITMAP,
					(j * 30) + 42, (i * 30) + 100, 30, 30, hWnd, (HMENU)ID, GetModuleHandle(0), 0);
				SendMessageW(buttonsArr[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbBlank);
			}
		}
	}
}

void clearEmpty(HWND hWnd, int y, int x)
{
	for (int i = 0; i < ButtNumberY; i++){
		for (int j = 0; j < ButtNumberX; j++){
			if (hWnd == buttonsArr[i][j]){
				if (GetDlgCtrlID(buttonsArr[i][j]) == EMPTY){
					SendMessageW(buttonsArr[i][j], WM_CLOSE, NULL, NULL);
					if (GetDlgCtrlID(buttonsArr[i][j + 1]) == NUMBER){

					}
					if (GetDlgCtrlID(buttonsArr[i + 1][j + 1]) == NUMBER){
						if (i + 1 <= 9 && j + 1 <= 9)
							SendMessageW(buttonsArr[i + 1][j + 1], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i + 1][j]) == NUMBER){
						if (i + 1 <= 9)
							SendMessageW(buttonsArr[i + 1][j], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i + 1][j - 1]) == NUMBER){
						if (i + 1 <= 9 && j - 1 >= 0)
							SendMessageW(buttonsArr[i + 1][j - 1], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i][j - 1]) == NUMBER){
						if (j - 1 >= 0)
							SendMessageW(buttonsArr[i][j - 1], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i - 1][j - 1]) == NUMBER){
						if (i - 1 >= 0 && j - 1 >= 0)
							SendMessageW(buttonsArr[i - 1][j - 1], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i - 1][j]) == NUMBER){
						if (i - 1 >= 0)
							SendMessageW(buttonsArr[i - 1][j], WM_CLOSE, NULL, NULL);
					}
					if (GetDlgCtrlID(buttonsArr[i - 1][j + 1]) == NUMBER){
						if (i - 1 >= 0 && j + 1 <= 9)
							SendMessageW(buttonsArr[i - 1][j + 1], WM_CLOSE, NULL, NULL);
					}
				}
				if (GetDlgCtrlID(buttonsArr[i][j + 1]) == EMPTY){
					if (j + 1 <= 9)
						clearEmpty(buttonsArr[i][j + 1]);
				}
				if (GetDlgCtrlID(buttonsArr[i + 1][j + 1]) == EMPTY){
					if (i + 1 <= 9 && j + 1 <= 9)
						clearEmpty(buttonsArr[i + 1][j + 1]);
				}
				if (GetDlgCtrlID(buttonsArr[i + 1][j]) == EMPTY){
					if (i + 1 <= 9)
						clearEmpty(buttonsArr[i + 1][j]);
				}
				if (GetDlgCtrlID(buttonsArr[i + 1][j - 1]) == EMPTY){
					if (i + 1 <= 9 && j - 1 >= 0)
						clearEmpty(buttonsArr[i + 1][j - 1]);
				}
				if (GetDlgCtrlID(buttonsArr[i][j - 1]) == EMPTY){
					if (j - 1 >= 0)
						clearEmpty(buttonsArr[i][j - 1]);
				}
				if (GetDlgCtrlID(buttonsArr[i - 1][j - 1]) == EMPTY){
					if (i - 1 >= 0 && j - 1 >= 0)
						clearEmpty(buttonsArr[i - 1][j - 1]);
				}
				if (GetDlgCtrlID(buttonsArr[i - 1][j]) == EMPTY){
					if (i - 1 >= 0)
						clearEmpty(buttonsArr[i - 1][j]);
				}
				if (GetDlgCtrlID(buttonsArr[i - 1][j + 1]) == EMPTY){
					if (i - 1 >= 0 && j + 1 <= 9)
						clearEmpty(buttonsArr[i - 1][j + 1]);
				}
			}
		}
	}
}

void gameRestart(HWND hWnd)
{
	for (int i = 0; i < ButtNumberY; i++){
		for (int j = 0; j < ButtNumberX; j++){
			DestroyWindow(hStaticArr[i][j]);
			DestroyWindow(buttonsArr[i][j]);
		}
	}

	setNumbersAndBombs(hWnd);
}

void initializeImages(HINSTANCE hInstance)
{
	hbFlag = (HBITMAP)LoadImageW(hInstance, L"images\\flag.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	hbQuest = (HBITMAP)LoadImageW(hInstance, L"images\\question.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	hbBomb = (HBITMAP)LoadImageW(hInstance, L"images\\bomb.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	hbBlank = (HBITMAP)LoadImageW(hInstance, L"images\\blank.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	hbBlankStatic = (HBITMAP)LoadImageW(hInstance, L"images\\blank_static.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);

	one = (HBITMAP)LoadImageW(hInstance, L"images\\1.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	two = (HBITMAP)LoadImageW(hInstance, L"images\\2.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	three = (HBITMAP)LoadImageW(hInstance, L"images\\3.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	four = (HBITMAP)LoadImageW(hInstance, L"images\\4.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	five = (HBITMAP)LoadImageW(hInstance, L"images\\5.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	six = (HBITMAP)LoadImageW(hInstance, L"images\\6.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	seven = (HBITMAP)LoadImageW(hInstance, L"images\\7.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
	eight = (HBITMAP)LoadImageW(hInstance, L"images\\8.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);

	smile_good = (HBITMAP)LoadImageW(hInstance, L"images\\smile_good.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	smile_bad = (HBITMAP)LoadImageW(hInstance, L"images\\smile_bad.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	smile_oops = (HBITMAP)LoadImageW(hInstance, L"images\\smile_oops.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	smile_win = (HBITMAP)LoadImageW(hInstance, L"images\\smile_win.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);

	time_0 = (HBITMAP)LoadImageW(hInstance, L"images\\time_0.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_1 = (HBITMAP)LoadImageW(hInstance, L"images\\time_1.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_2 = (HBITMAP)LoadImageW(hInstance, L"images\\time_2.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_3 = (HBITMAP)LoadImageW(hInstance, L"images\\time_3.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_4 = (HBITMAP)LoadImageW(hInstance, L"images\\time_4.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_5 = (HBITMAP)LoadImageW(hInstance, L"images\\time_5.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_6 = (HBITMAP)LoadImageW(hInstance, L"images\\time_6.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_7 = (HBITMAP)LoadImageW(hInstance, L"images\\time_7.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_8 = (HBITMAP)LoadImageW(hInstance, L"images\\time_8.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
	time_9 = (HBITMAP)LoadImageW(hInstance, L"images\\time_9.bmp", IMAGE_BITMAP, 17, 32, LR_LOADFROMFILE);
}

void checkImages(HWND hWnd)
{
	if (!hbFlag || !hbQuest || !hbBomb || !hbBlank || !one || !two || !three || !four || !five || !six || !seven || !eight
		|| !smile_bad || !smile_good || !smile_oops || !smile_win || !time_0 || !time_1 || !time_2 || !time_3 || !time_4 
		|| !time_5 || !time_6 || !time_7 || !time_8 || !time_9 || !hbBlankStatic)
	MessageBoxW(hWnd, L"Can't load images", L"Warning", MB_OK);
}

void createTimers(HWND hWnd)
{
	for (int i = 0; i < 4; i++){
		timer[i] = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_BITMAP,
			(i * 15) + 65, 47, 15, 30, hWnd, (HMENU)NULL, GetModuleHandle(0), 0);
		SendMessage(timer[i], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)time_0);
	}
	for (int i = 0; i < 3; i++){
		bombsCount[i] = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | SS_BITMAP,
			(i * 15) + 265, 47, 15, 30, hWnd, (HMENU)NULL, GetModuleHandle(0), 0);
		SendMessage(bombsCount[i], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)time_0);
	}
	
}

void checkIfWin(HWND hWnd)
{
	int count = ButtNumberY * ButtNumberX;
	bool win = false;
	for (int i = 0; i < ButtNumberY; i++){
		for (int j = 0; j < ButtNumberX; j++){
			if (IsWindow(buttonsArr[i][j]) == NULL)
				count--;
			if (count <= bombs.size())
				win = true;
		}
	}

	if (win){
		wstring str;
		KillTimer(hWnd, TIMER_1);
		KillTimer(hWnd, TIMER_2);
		SendMessageW(smile_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)smile_win);
		if ((timerCount - 1 < bestTime || bestTime == 0)){
			saveBestTime(timerCount - 1);
			if (bestTime == 0)
				str = L"Your time is " + to_wstring(timerCount - 1) + L" seconds!\n" +
				L"You have set up a first record!!!" + L"\nWould you like to play again?";
			else 
				str = L"Your time is " + to_wstring(timerCount - 1) + L" seconds!\n" +
				L"You have beaten the previous record of " + to_wstring(bestTime) + L" seconds!!!" + L"\nWould you like to play again?";
			bestTime = timerCount - 1;
		}
		else
			str = L"Your time is " + to_wstring(timerCount - 1) + L" seconds!\n" +
			L"You haven't beaten the previous record of " + to_wstring(bestTime) + L" seconds." + L"\nWould you like to play again?";
		
		int answer = MessageBoxW(hWnd,
		str.c_str(), L"YOU WIN!!!", MB_YESNO | MB_ICONINFORMATION);
		switch (answer){
		case IDYES:
			SetTimer(hWnd, TIMER_1, 1000, TimerProcTime);
			SetTimer(hWnd, TIMER_2, 100, TimerProcBomb);
			timerCount = 0;
			gameRestart(hWnd);
			break;
		case IDNO:
			SendMessageW(hWnd, WM_CLOSE, NULL, NULL);
			break;
		}
	}
	
}

int loadSave(HWND hWnd)
{
	wifstream input("save.dat", ios::in | ios::binary);

	input.read((wchar_t *)&bestPlayer, sizeof(BestPlayer));
	if (gameState.junior){
		return bestPlayer.junior;
	}
	else if (gameState.middle){
		return bestPlayer.middle;
	}
	else if (gameState.senior){
		return bestPlayer.senior;
	}
	input.close();
}

void saveBestTime(int curentTime)
{
	if (gameState.junior){
		bestPlayer.junior = curentTime;
	}
	else if (gameState.middle){
		bestPlayer.middle = curentTime;
	}
	else if (gameState.senior){
		bestPlayer.senior = curentTime;
	}

	wofstream output("save.dat", ios::out | ios::binary);
	output.write((wchar_t*)&bestPlayer, sizeof(BestPlayer));
}

void GetDesktopResolution(long& left, long& top)
{
	RECT cord;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &cord);

	left = (cord.right / 2) - (rectWindow.right / 2);
	top = (cord.bottom / 2) - (rectWindow.bottom / 2);

}