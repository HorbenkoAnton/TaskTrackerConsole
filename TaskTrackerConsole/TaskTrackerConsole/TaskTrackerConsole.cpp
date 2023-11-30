#include <iostream>
#include <vector>
#include <iomanip> 
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <limits>
using namespace std;


#define INPROGRESS "In progress"
#define COMPLETED "Completed"
#define CANCELED "Canceled"
#define COLUMN1 20
#define COLUMN2 20
#define COLUMN3 150
#define COLUMN4 
#define CANCELTASK 0
#define COMPLETETASK 1

struct Task {
    string name;
    string text;
    string status;
};

void showMenu() {
    cout << "________________________________________________________________________________________________" << endl;
    cout << "Choose command:" << endl;
    cout << "1 - Add task." << endl;
    cout << "2 - Complete task." << endl;
    cout << "3 - Cancel task." << endl;
    cout << "4 - Show completed tasks." << endl;
    cout << "5 - Show canceled tasks." << endl;
    cout << "6 - Exit application." << endl;
    cout << "Type number:";
}

class TaskMananger
{

private:
    vector<Task> tasks;
public:
    TaskMananger();
    ~TaskMananger();
    void addTask() {
        string taskName, taskText;
        cout << "Enter task name:"; cin.ignore(); getline(cin, taskName); cout << endl;
        cout << "Enter task text:";  getline(cin, taskText); cout << endl;
        Task task = { taskName , taskText , INPROGRESS };
        this->tasks.push_back(task);
    }
    int statusChanger(int action) {
        if (this->tasks.empty()) {
            cout << "There is no tasks right now ,add one if you need!" << endl;
            Sleep(3000);
            return 0;
        }

        string taskName;
        if (action == COMPLETETASK) {
            cout << "Enter task name to complete:"; cin.ignore(); getline(cin, taskName);
        }
        else if (action == CANCELTASK) {
            cout << "Enter task name to cancel:"; cin.ignore(); getline(cin, taskName);
        }
        else cout << "Error1 in status changer" << endl;

        for (auto itr = this->tasks.begin(); itr != this->tasks.end(); ++itr) {
            if ((*itr).name == taskName) {
                switch (action)
                {
                case COMPLETETASK:
                    (*itr).status = COMPLETED;
                    break;
                case CANCELTASK:
                    (*itr).status = CANCELED;
                    break;

                default:
                    cout << "Error2 in status changer" << endl;
                    break;
                }
            }
        }

    }
    void showTasks(string status) {
        if (this->tasks.empty())cout << "There is no tasks right now ,add one if you need!" << endl;
        else {
            cout << left << "Here is tasks with " << status << " status: " << endl;
            cout << left << setw(COLUMN1) << "Name";
            cout << left << setw(COLUMN2) << "Status";
            cout << left << setw(COLUMN3) << "Text";
            cout << endl;
            for (auto itr = this->tasks.begin(); itr != this->tasks.end(); ++itr)
            {
                if ((*itr).status == status) {
                    cout << left << setw(COLUMN1) << (*itr).name;

                    cout << left << setw(COLUMN2) << (*itr).status;

                    cout << left << setw(COLUMN3) << (*itr).text;

                    cout << endl;
                }
            }
        }
    }

};

TaskMananger::TaskMananger()
{
}

TaskMananger::~TaskMananger()
{
}


int main()
{
    TaskMananger TaskMananger;
    int userAnswer;
    while (true) {
        system("CLS");
        TaskMananger.showTasks(INPROGRESS);
        showMenu();
        if (cin >> userAnswer)
        {
            switch (userAnswer)
            {
            case 1:
                system("CLS");
                TaskMananger.addTask();
                break;
            case 2:
                system("CLS");
                TaskMananger.statusChanger(COMPLETETASK);
                break;
            case 3:
                system("CLS");
                TaskMananger.statusChanger(CANCELTASK);
                break;
            case 4:
                system("CLS");
                TaskMananger.showTasks(COMPLETED);
                Sleep(3000);
                break;
            case 5:
                system("CLS");
                TaskMananger.showTasks(CANCELED);
                Sleep(3000);
                break;
            case 6:
                return 0;
            default:
                cout << "Uknown command!" << endl;
                Sleep(3000);
                system("CLS");
                break;
            }
        }
        else
        {
            cout << "I said enter number!" << endl;
            Sleep(3000);
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    return 0;
}
