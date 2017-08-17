#include "UserInterface.h"
#include <codecvt>
#include <algorithm>
#include <regex>
#include "resource.h"
#include "MyTools.h"
#include "MyMutex.h"

#define  DB_ISREADY  (WM_USER - 1)
#define  LIST_ISREADY  (WM_USER - 2)

HWND UserInterface::list_box_;
HWND UserInterface::progress_application_bar_;
HWND UserInterface::progress_db_bar_;
HWND UserInterface::add_button_;
HWND UserInterface::remove_button_;
HWND UserInterface::load_button_;
HWND UserInterface::hWnd_;
HWND UserInterface::close_;
HWND UserInterface::time_box_;
HWND UserInterface::date_box_;
HWND UserInterface::event_box_;
bool UserInterface::isApplicationIsReady_;
TaskManager * UserInterface::task_manager_;
std::thread UserInterface::list_thread_;
size_t UserInterface::db_elements_size_;
size_t UserInterface::db_elements_size_load_count_;


UserInterface::UserInterface(TaskManager * task_manager)
{
	task_manager_ = task_manager;
	task_manager_->AddDBLoadinDoneNotification(notifyBDLoaded);
	task_manager_->AddDBLoadinCallback(dBCallbackLoading);
}

//Callback function to notifyBDLoaded when database was loaded
void UserInterface::notifyBDLoaded()
{
	//sending message that DB is already loaded
	//This is asynchronous function so we just post our message in a queue of dialogbox commands and leave function
	PostMessage(hWnd_, DB_ISREADY, 0, 0);
}

//Callback function to notify us while DB is loading
void UserInterface::dBCallbackLoading()
{
	//This is also asynchronous function so we wouldn't interrupt dialogbox procedure function which is running in initial thread
	PostMessage(progress_db_bar_, PBM_SETPOS, WPARAM(++db_elements_size_load_count_), 0);
}

//At the start from getting data from database my array is already sorted so this way I layout all element by it's nearest execution right away
void UserInterface::fillList()
{
	//Setting the range of progress bar. We do that here because I need to make sure that DB is already loaded and size of container is known
	SendMessage(progress_application_bar_, PBM_SETRANGE, 0, MAKELPARAM(0, task_manager_->GetTasks().size()));

	//Locking further operations because we are working with container in TaskManager;
	MyMutex mutex;

	//For not beaking incapsulation it would be good if we send some request to a TaskManager and it will call some callback function and return here each elements
	//Though for the sake of speed (so we wouldn't jump from there to here) I dicided to get whole vector from it and do our things in one function here
	auto tasks = task_manager_->GetTasks();
	
	//filling up our UI list
	for(size_t i = 0; i < tasks.size(); ++i)
	{
		std::string str(tasks[i].GetDeadLine());
		str += "   |    ";
		str += tasks[i].GetMyEvent();
		std::wstring wide = MyTools::CharsToWchar_t(str);
		SendMessage(list_box_, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wide.c_str()));
		SendMessage(progress_application_bar_, PBM_SETPOS, WPARAM(i + 1), 0);
	}

	//Progress bar range has to be from 0 to 10 minimum so if we have less elements than 10 I manualy set it up to 10
	//We don't want to see when application ready with half filled progress bar 
	if (tasks.size() < 10) {
		SendMessage(progress_application_bar_, PBM_SETRANGE, 0, MAKELPARAM(0, 10));
		SendMessage(progress_application_bar_, PBM_SETPOS, WPARAM(10), 0);
		SendMessage(progress_db_bar_, PBM_SETRANGE, 0, MAKELPARAM(0, 10));
		SendMessage(progress_db_bar_, PBM_SETPOS, WPARAM(10), 0);
	}

	isApplicationIsReady_ = true;
	//sending asynchronous message that list is already loaded
	PostMessage(hWnd_, LIST_ISREADY, 0, 0);
}

//Dialog box procedure function that handle all incoming messages
BOOL CALLBACK UserInterface::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
			//Exit button (cross on a right-top) pressed
			EndDialog(hwnd, 0);
		break;
	case WM_INITDIALOG:
			//Runs befoe the start of our window
			initialize(hwnd);
		break;
	case WM_COMMAND:
		{
			//Close button pressed
			if (lParam == reinterpret_cast<LPARAM>(close_)) {
				DlgProc(hwnd, WM_CLOSE, 0, 0);
				break;
			}

			//Load button pressed
			if (lParam == reinterpret_cast<LPARAM>(load_button_)) {
				isApplicationIsReady_ = false;
				task_manager_->Initialize();
				reset_UI();
				if(!task_manager_->IsOperationWasOK())
					MessageBox(nullptr, task_manager_->GetLastErrMsg(), L"Error!", MB_OK | MB_ICONWARNING);
				break;
			}

			//Checking if application is ready to use
			//We don't want be able to press load or remove button when DB is not connected
			if(!isApplicationIsReady_){
				break;
			}
			
			//Add button pressed
			if (lParam == reinterpret_cast<LPARAM>(add_button_)){
				addTask(hwnd);
			}

			//Remove button pressed
			else if (lParam == reinterpret_cast<LPARAM>(remove_button_)){
				removeTask(hwnd);
			}
		}
		break;
		//Getting here asynchronous message what we have send above that DB is loaded 
	case DB_ISREADY:
		{
			//Joining a thead that was loading DB in container. We don't need it anymore.
			task_manager_->JoinDBThread();
			//Checking if loaded was successful and there is no errors.
			if(!task_manager_->IsOperationWasOK()){
				MessageBox(nullptr, task_manager_->GetLastErrMsg(), L"Error!", MB_OK | MB_ICONWARNING);
			}
			else{
				//Starting to fill UI list box
				//The good idea will be to fill that box in another thread as well for not blocking UI
				//The problem here is that this procedure function running always in initial thread
				//If we create a second thread and the second thread will send messages here to add a string in a list box it finaly will collapse because of two cooks in a citchen
				//The only way to do that is sending from that thread an asynchronous messages here 
				//Unfortunately MSDN doesn't provide any sutable solution for adding strings to a list box in asynchronous mode or I just didn't found it.
				//So for not I calculated it and insert in a project, but left these lines commented out.
				fillList();
				//list_thread_ = std::thread(fillList); <=========
			}
		}
		break;
	case LIST_ISREADY:
		{
			//list_thread_.join(); <==========
			MessageBox(nullptr, L"Application is ready to use!", L"Ready!", MB_OK);
		}
		break;
	default: 
		break;
	}

	return FALSE;
}

//Timer callback function
VOID CALLBACK UserInterface::TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	//Task is creating with date of "2099-00-00 00:00:00" 
	//Comparising with next task to execute I check whether list is empty and next task wasn't initialized
	Task task;
	if(task == task_manager_->GetNextTaskToExecute()){
		return;
	}
	task = task_manager_->GetNextTaskToExecute();

	//Checking is time of task <= current time
	//If it is than time to get things done
	if(task.GetDeadLineTime() <= MyTools::CurrentLocalTime())
	{
		if (!task_manager_->RemoveTask(task)) {
			MessageBox(hwnd, task_manager_->GetLastErrMsg(), L"Warning", MB_OK | MB_ICONWARNING);
			return;
		}
		findCellAndDelete(task);
		MessageBox(hwnd, MyTools::CharsToWchar_t(task.GetMyEvent()).c_str(), L"It's time do to", MB_OK | MB_ICONINFORMATION);
	}
}

//Reseting all UI elements to zero and remove all strings from list box
void UserInterface::reset_UI()
{
	int result = 1;
	while ( result != LB_ERR)
	{
		result = SendMessage(list_box_, LB_DELETESTRING, 0, 0);
	}
	db_elements_size_ = task_manager_->GetDBSizeOfElements();
	db_elements_size_load_count_ = 0;
	SendMessage(progress_db_bar_, PBM_SETPOS, 0, 0);
	SendMessage(progress_db_bar_, PBM_SETRANGE, 0, MAKELPARAM(0, db_elements_size_));
	SendMessage(progress_application_bar_, PBM_SETPOS, 0, 0);
}

//Initialize all controls handles
void UserInterface::initialize(HWND hwnd)
{
	hWnd_ = hwnd;
	list_box_ = GetDlgItem(hwnd, IDC_LIST1);
	progress_application_bar_ = GetDlgItem(hwnd, IDC_PROGRESS1);
	progress_db_bar_ = GetDlgItem(hwnd, IDC_PROGRESS2);
	add_button_ = GetDlgItem(hwnd, IDC_BUTTON1);
	remove_button_ = GetDlgItem(hwnd, IDC_BUTTON2);
	load_button_ = GetDlgItem(hwnd, IDC_BUTTON3);
	time_box_ = GetDlgItem(hwnd, IDC_EDIT1);
	date_box_ = GetDlgItem(hwnd, IDC_EDIT2);
	event_box_ = GetDlgItem(hwnd, IDC_EDIT3);
	close_ = GetDlgItem(hwnd, IDCLOSE);
	SendMessage(progress_application_bar_, PBM_SETSTEP, 2, 0);
	SendMessage(progress_application_bar_, PBM_SETPOS, 0, 0);
	SendMessage(progress_db_bar_, PBM_SETSTEP, 2, 0);
	SendMessage(progress_db_bar_, PBM_SETPOS, 0, 0);
	
	//Set timer to visit every second TimerProc
	//First I thought about adding own thread here but after desided to use a handy build in WinAPI solution for that purpose to not spam extra code lines
	SetTimer(hwnd, 0, 1000, TimerProc);
}

void UserInterface::addTask(HWND hwnd)
{
	// Retrieving info from date and time box (haven't found a proper way to work with date time picker and get any info from it)
	std::wstring wide_result_date_time = getStrFromEditbox(date_box_);
	wide_result_date_time += ' ';
	std::wstring wide_time_sting = getStrFromEditbox(time_box_);
	wide_result_date_time += wide_time_sting;

	//Checking if date&time is due to date and has correct format
	if(MyTools::ConvertWStrToTime(wide_result_date_time.c_str()) < MyTools::CurrentLocalTime()){
		MessageBox(hwnd, L"Wrong formad or task is out to date", L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	//Retrieving info from event box or fill it with "empty" string
	std::wstring wide_event_name(getStrFromEditbox(event_box_));
	if(wide_event_name.size() == 0){
		wide_event_name = L"empty";
	}

	//Creating a task and store it in database
	std::string deadline = MyTools::Wchar_tToChars(wide_result_date_time);
	std::string event_name = MyTools::Wchar_tToChars(wide_event_name);
	Task task(event_name.c_str(), deadline.c_str());
	if(!task_manager_->AddTask(task)){
		MessageBox(hwnd, task_manager_->GetLastErrMsg(), L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	//Adding to UI list
	//List box is supporting sorting items only by my event names so I turned if off and and add items to the end now
	//It is good idea to sort task by it's nearest execution and but I only do that from the beginning because my vector is already sorted from the start by dead line
	//And after adding task in a run time it stores always at the end
	std::wstring string_to_list(wide_result_date_time);
	string_to_list += L"   |    ";
	string_to_list += wide_event_name;
	SendMessage(list_box_, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(string_to_list.c_str()));
	MessageBox(hwnd, wide_event_name.c_str(), L"Added", MB_OK | MB_ICONINFORMATION);
}

//Searching task in listbox by comparising stirngs
//Unfortunately I didn't find a solution how to store objects as they are (as whole objects) in listbox the way it is possible in WPF
void UserInterface::findCellAndDelete(Task task)
{
	std::string event_name(task.GetMyEvent());
	std::string dead_line(task.GetDeadLine());
	std::string string_to_list = dead_line;
	string_to_list += "   |    ";
	string_to_list += event_name;

	std::wstring wide_string_to_list(MyTools::CharsToWchar_t(string_to_list));

	auto index = SendMessage(list_box_, LB_FINDSTRING, -1, reinterpret_cast<LPARAM>(wide_string_to_list.c_str()));
	SendMessage(list_box_, LB_DELETESTRING, index, 0);
}

//Moved out this part here to rid of dublication in code
std::wstring UserInterface::getStrFromEditbox(HWND hwnd)
{
	auto length = GetWindowTextLength(hwnd);
	wchar_t * str = new wchar_t[length + 1];
	GetWindowText(hwnd, str, length + 1);
	std::wstring temp(str);
	delete[]str;
	temp.erase(std::remove_if(temp.begin(), temp.end(), isspace), temp.end());
	return temp;
}

void UserInterface::removeTask(HWND hwnd)
{
	//Good architecture try to remove item from database first and after give a greenlight to UI so that is could be also removed as well
	//In WinAPI I can't store objects in list but strings only. Thats why I have to get string first from there and make an object out of it
	//Only after that I'm able to send a request to my TaskManager

	//Checking if task is selected
	auto cell_index = SendMessage(list_box_, LB_GETCURSEL, 0, 0);
	if (cell_index == LB_ERR) {
		MessageBox(hwnd, L"no string selected", L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	//Getting text from listbox
	auto size = SendMessage(list_box_, LB_GETTEXTLEN, cell_index, 0);
	wchar_t * str = new wchar_t[size + 1];
	SendMessage(list_box_, LB_GETTEXT, cell_index, reinterpret_cast<LPARAM>(str));
	std::wstring wide_task_sting(str);
	delete[]str;

	//Trim deadline name 
	std::string task_sting = MyTools::Wchar_tToChars(wide_task_sting);
	std::string dead_line(task_sting.substr(0, task_sting.find('|')));

	//Trim it manualy because I need a space between date and time
	for (size_t i = dead_line.length() - 1; i >= 0; --i) {
		if (!isspace(dead_line[i])) {
			dead_line = dead_line.erase(i + 1);
			break;
		}
	}

	//Trim event name 
	std::string event_name(task_sting.substr(task_sting.find('|') + 1));
	event_name.erase(std::remove_if(event_name.begin(), event_name.end(), isspace), event_name.end());

	
	//Creating temp task object and remove it from database and UI
	Task task(event_name.c_str(), dead_line.c_str());
	if (!task_manager_->RemoveTask(task)){
		MessageBox(hwnd, task_manager_->GetLastErrMsg(), L"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	//Updating UI
	SendMessage(list_box_, LB_DELETESTRING, cell_index, 0);
	MessageBox(hwnd, wide_task_sting.c_str(), L"Removed", MB_OK | MB_ICONINFORMATION);
}
