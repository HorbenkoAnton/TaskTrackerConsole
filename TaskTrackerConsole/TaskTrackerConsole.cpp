#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include "libs/nlohmann/json.hpp"
#include <Windows.h>

using json = nlohmann::json;


#define DATAFILE "data.json"
#define INPROGRESS "In progress"
#define COMPLETED "Completed"
#define CANCELED "Canceled"
#define COLUMN1 20
#define COLUMN2 20
#define COLUMN3 150
#define CANCELTASK 0
#define COMPLETETASK 1

struct Task {
    std::string name;
    std::string text;
    std::string status;
};

void showMenu() {
    std::cout << "________________________________________________________________________________________________" << std::endl;
    std::cout << "Choose command:" << std::endl;
    std::cout << "1 - Add task." << std::endl;
    std::cout << "2 - Complete task." << std::endl;
    std::cout << "3 - Cancel task." << std::endl;
    std::cout << "4 - Show completed tasks." << std::endl;
    std::cout << "5 - Show canceled tasks." << std::endl;
    std::cout << "6 - Exit application." << std::endl;
    std::cout << "Type number:";
}

class TaskManager {

private:
    std::vector<Task> tasks;

public:
    TaskManager();
    ~TaskManager();

    void addTask() {
        std::string taskName, taskText;
        std::cout << "Enter task name:"; std::cin.ignore(); std::getline(std::cin, taskName); std::cout << std::endl;
        std::cout << "Enter task text:";  std::getline(std::cin, taskText); std::cout << std::endl;
        if (!(taskName.empty())) {
            Task task = { taskName , taskText , INPROGRESS };
            this->tasks.push_back(task);
        }
        else {
            std::cout << "Task name can't be empty!" << std::endl;
              // Clear input buffer
        }
    }

    int statusChanger(int action) {
        if (this->tasks.empty()) {
            std::cout << "There are no tasks right now. Add one if you need!" << std::endl;
             
             
            return 0;
        }

        std::string taskName;
        if (action == COMPLETETASK) {
            std::cout << "Enter task name to complete:"; std::cin.ignore(); std::getline(std::cin, taskName);
        }
        else if (action == CANCELTASK) {
            std::cout << "Enter task name to cancel:"; std::cin.ignore(); std::getline(std::cin, taskName);
        }
        else {
            std::cout << "Error1 in status changer" << std::endl;
            return 0;
        }

        auto itr = this->tasks.begin();
        while (itr != this->tasks.end()) {
            if ((*itr).name == taskName) {
                switch (action) {
                case COMPLETETASK:
                    (*itr).status = COMPLETED;
                    break;
                case CANCELTASK:
                    (*itr).status = CANCELED;
                    break;
                default:
                    std::cout << "Error2 in status changer" << std::endl;
                    break;
                }
                ++itr;
            }
            else {
                ++itr;
            }
        }
        return 1;
    }

    void showTasks(std::string status) {
        if (this->tasks.empty()) {
            std::cout << "There are no tasks right now. Add one if you need!" << std::endl;
             
        }
        else {
            std::cout << std::left << "Here are tasks with " << status << " status: " << std::endl;
            std::cout << std::left << std::setw(COLUMN1) << "Name";
            std::cout << std::left << std::setw(COLUMN2) << "Status";
            std::cout << std::left << std::setw(COLUMN3) << "Text";
            std::cout << std::endl;
            for (auto itr = this->tasks.begin(); itr != this->tasks.end(); ++itr)
            {
                if ((*itr).status == status) {
                    std::cout << std::left << std::setw(COLUMN1) << (*itr).name;
                    std::cout << std::left << std::setw(COLUMN2) << (*itr).status;
                    std::cout << std::left << std::setw(COLUMN3) << (*itr).text;
                    std::cout << std::endl;
                }
            }
        }
    }

    void saveData() {
        std::ofstream outfile(DATAFILE);
        if (!outfile.is_open()) {
            std::cerr << "Error opening file: " << DATAFILE << std::endl;
            return;
        }

        json j;
        for (const auto& task : this->tasks) {
            j.push_back({
                {"name", task.name},
                {"text", task.text},
                {"status", task.status}
                });
        }

        outfile << std::setw(4) << j; 
        outfile.close();
    }

    void loadData() {
        std::ifstream infile(DATAFILE);
        if (!infile.is_open()) {
            std::cerr << "Error opening file: " << DATAFILE << std::endl;
            return;
        }

        json j;
        infile >> j;

        for (const auto& taskJson : j) {
            Task task;
            task.name = taskJson["name"];
            task.text = taskJson["text"];
            task.status = taskJson["status"];
            this->tasks.push_back(task);
        }

        infile.close();
    }
};

TaskManager::TaskManager() {}

TaskManager::~TaskManager() {}

int main() {
    TaskManager taskManager;
    taskManager.loadData();
    int userAnswer;

    while (true) {
        system("CLS");
        taskManager.showTasks(INPROGRESS);
        showMenu();

        if (std::cin >> userAnswer) {
            switch (userAnswer) {
            case 1:
                system("CLS");
                taskManager.addTask();
                taskManager.saveData();
                break;
            case 2:
                system("CLS");
                taskManager.statusChanger(COMPLETETASK);
                taskManager.saveData();
                break;
            case 3:
                system("CLS");
                taskManager.statusChanger(CANCELTASK);
                taskManager.saveData();
                break;
            case 4:
                system("CLS");
                taskManager.showTasks(COMPLETED);
                Sleep(3000);
                break;
            case 5:
                system("CLS");
                taskManager.showTasks(CANCELED);
                Sleep(3000);
                break;
            case 6:
                taskManager.saveData();
                return 0;
            default:
                std::cout << "Unknown command!" << std::endl;
                
                break;
            }
        }
        else {
            std::cout << "Please enter a number!" << std::endl;
            std::cin.clear();
             
        }
    }

    return 0;
}
