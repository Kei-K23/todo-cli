#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

// Task struct data structure
struct Task
{
    std::string id;
    std::string title;
    std::string description;
    std::string status;
    std::string dueDate;
};

// Function to generate random unique id
std::string generateUniqueID(const int length)
{
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string id;

    for (size_t i = 0; i < length; i++)
    {
        id += characters[rand() % characters.length()];
    }
    return id;
}

void addNewTask(std::vector<Task> &tasks)
{
    Task newTask;
    std::cout << "Enter title: ";
    std::getline(std::cin, newTask.title);

    std::cout << "Enter description: ";
    std::getline(std::cin, newTask.description);

    std::cout << "Enter due date: ";
    std::getline(std::cin, newTask.dueDate);
    newTask.id = generateUniqueID(6);
    newTask.status = "PENDING";

    tasks.push_back(newTask);
    std::cout << "Successfully added new task" << std::endl;
}

void makeTaskComplete(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to make as completed: ";
    std::getline(std::cin, search);

    for (auto &task : tasks)
    {
        if (task.id == search || task.title == search)
        {
            task.status = "COMPLETED";
            return; // Exit from the loop, unless it will run infinite
        }
    }
    std::cout << "Task not found" << std::endl;
}

void editTask(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to make as completed: ";
    std::getline(std::cin, search);

    for (auto &task : tasks)
    {
        if (task.id == search || task.title == search)
        {
            std::cout << "Enter description: ";
            std::getline(std::cin, task.description);

            std::cout << "Enter due date: ";
            std::getline(std::cin, task.dueDate);
            return; // Exit from the loop, unless it will run infinite
        }
    }
    std::cout << "Task not found" << std::endl;
}

void deleteTask(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to make as completed: ";
    std::getline(std::cin, search);

    auto it = tasks.begin();
    while (it != tasks.end())
    {
        if (it->id == search || it->title == search)
        {
            tasks.erase(it); // Erase the task from vector
            std::cout << "Task deleted successfully." << std::endl;
            return; // Exit the function after deletion
        }
        else
        {
            ++it; // Move to next element
        }
    }

    std::cout << "Task not found" << std::endl;
}

void listAllTasks(const std::vector<Task> &tasks)
{
    for (const auto &task : tasks)
    {
        std::cout << "Id: " << task.id << std::endl;
        std::cout << "Title: " << task.title << std::endl;
        std::cout << "Description: " << task.description << std::endl;
        std::cout << "Due Date: " << task.dueDate << std::endl;
        std::cout << "Status: " << task.status << std::endl;
        std::cout << std::endl;
    }
}

void saveTasksToCSV(const std::vector<Task> &tasks, const std::string filename)
{
    std::ofstream file(filename);
    for (const auto &task : tasks)
    {
        file << "\"" << task.id << "\","
             << "\"" << task.title << "\","
             << "\"" << task.description << "\","
             << "\"" << task.status << "\","
             << "\"" << task.dueDate << "\"\n";
    }
}

void loadTasksFromCSV(std::vector<Task> &tasks, const std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        Task task;

        std::getline(iss, task.id, ',');
        task.id = task.id.substr(1, task.id.size() - 2);

        std::getline(iss, task.title, ',');
        task.title = task.title.substr(1, task.title.size() - 2);

        std::getline(iss, task.description, ',');
        task.description = task.description.substr(1, task.description.size() - 2);

        std::getline(iss, task.status, ',');
        task.status = task.status.substr(1, task.status.size() - 2);

        std::getline(iss, task.dueDate, ',');
        task.dueDate = task.dueDate.substr(1, task.dueDate.size() - 2);

        tasks.push_back(task);
    }
}

int main()
{
    std::vector<Task> tasks;
    const std::string filename = "tasks.csv";

    loadTasksFromCSV(tasks, filename);

    int choice;
    do
    {
        std::cout << "Menu" << std::endl;
        std::cout << "1. Add task" << std::endl;
        std::cout << "2. Mark task as complete" << std::endl;
        std::cout << "3. Edit task" << std::endl;
        std::cout << "4. Delete task" << std::endl;
        std::cout << "5. List all tasks" << std::endl;
        std::cout << "6. Save and Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To clear the newline from input buffer
        switch (choice)
        {
        case 1:
            addNewTask(tasks);
            break;
        case 2:
            makeTaskComplete(tasks);
            break;
        case 3:
            editTask(tasks);
            break;
        case 4:
            deleteTask(tasks);
            break;
        case 5:
            listAllTasks(tasks);
            break;
        case 6:
            saveTasksToCSV(tasks, filename);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
        }

    } while (choice != 6);

    return 0;
}