#include <iostream>
#include <vector>
#include <iomanip> 
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

#define INPROGRESS "In progress!"
#define COMPLETED "Completed"
#define CANCELED "Canceled"
#define COLUMN1 20
#define COLUMN2 20
#define COLUMN3 150
#define COLUMN4 

struct Task {
    string name;
    string text;
    string status;
};


void showTasks(vector<Task>* tasks) {

    cout << left <<"Here is your tasks! :" << endl;
    cout << left << setw(COLUMN1) << "Name";
    cout << left << setw(COLUMN2) << "Status";
    cout << left << setw(COLUMN3) << "Text";
    cout << endl;
    Task task;
    for (auto itr = (*tasks).begin(); itr != (*tasks).end(); ++itr)
    {
        if ((*itr).status == INPROGRESS) {
            cout << left << setw(COLUMN1) << (*itr).name;

            cout << left << setw(COLUMN2) << (*itr).status;

            cout << left << setw(COLUMN3) << (*itr).text;

            cout << endl;
        }
    }
}

void addTask(vector<Task>* tasks) {

    string name, text;
    cout << "Enter task name: "; getline(cin, name); cout << endl;
    cout << "Enter task text: "; getline(cin , text); cout << endl;
    Task newTask = { name, text, INPROGRESS };
    (*tasks).push_back(newTask);
}

void completeTask(vector<Task>* tasks) {
    string taskName;
    cout << "Enter task name to complete:"; cin >> taskName;
    for (auto itr = (*tasks).begin(); itr != (*tasks).end(); ++itr) {

        if ((*itr).name == taskName) {
            (*itr).status = COMPLETED;
        }
    }
}

void cancelTask(vector<Task>* tasks) {
    string taskName;
    cout << "Enter task name to cancel:"; cin >> taskName;
    for (auto itr = (*tasks).begin(); itr != (*tasks).end(); ++itr) {

        if ((*itr).name == taskName) {
            (*itr).status = CANCELED;
        }
    }
}

void showMenu() {
    cout << "________________________________________________________________________________________________" << endl;
    cout << "Choose command and type it's number:" << endl;
    cout << "1 - Add task." << endl;
    cout << "2 - Cancel task." << endl;
    cout << "3 - Show completed tasks." << endl;
    cout << "4 - Show canceled tasks." << endl;
    cout << "Type number:";

}
int main()
{
    Task emtpyTask = { "Empty" , "There is no tasks right now. Add one using command!" ,INPROGRESS };
    vector<Task> tasks = { emtpyTask };
    addTask(&tasks);



    start:
    showTasks(&tasks);

    showMenu();
    int userAnswer = 0;
    cin >> userAnswer;
    switch (userAnswer)
    {
    case 1:
        system("CLS");
        addTask(&tasks);
        goto start;
    default:
        cout << "Uknown command!" << endl;
        Sleep(1000);
        system("CLS");
        goto start;
    }


    return 0;
}   
//TODO 
//emtpy name and text check
//cancelTask + completeTask + addTask = taskMananger
//showTasks = showActiveTasks + showCompletedTasks + showCanceled tasks
//saving data