#include <iostream>
#include <vector>
#include <iomanip> 
#include <string>

using namespace std;

struct Task {
    string name;
    string text;
    string status;
};


void showTasks(vector<Task>* tasks) {
    int col1 = 20;
    int col2 = 20;
    int col3 = 150;
    cout << left <<"Here is your tasks! :" << endl;
    cout << left << setw(col1) << "Name";
    cout << left << setw(col2) << "Status";
    cout << left << setw(col3) << "Text";
    cout << endl;
    for (auto itr = (*tasks).begin(); itr != (*tasks).end(); ++itr)
    {
        Task task = *itr;
        cout << left << setw(col1) << task.name;

        cout << left << setw(col2) << task.status;

        cout << left << setw(col3) << task.text;

        cout << endl;
    }
}

void addTasks(vector<Task>* tasks) {

    string name, text;
    cout << "Enter task name: "; getline(cin, name); cout << endl;
    cout << "Enter task text: "; getline(cin , text); cout << endl;
    Task newTask = { name, text, "In progress!"};
    (*tasks).push_back(newTask);
}


int main()
{
    Task emtpyTask = { "Empty" , "There is no tasks right now. Add one using command!" ,"Uknown" };
    vector<Task> tasks = { emtpyTask };

    //show tasks
    showTasks(&tasks);
    //add tasks
    addTasks(&tasks);
    showTasks(&tasks);
    //complete tasks
    //cancel tasks

    return 0;
}
