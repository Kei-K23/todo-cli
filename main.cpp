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
            std::cout << "Successfully marked the task completed" << std::endl;
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
            std::cout << "Successfully updated the task completed" << std::endl;
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

// Function to split the text into multiple lines based on the given width
std::vector<std::string> wrapText(const std::string &text, size_t width)
{
    std::vector<std::string> lines;
    std::istringstream words(text);
    std::string word;
    std::string line;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 <= width)
        {
            if (!line.empty())
                line += " ";
            line += word;
        }
        else
        {
            lines.push_back(line);
            line = word;
        }
    }

    if (!line.empty())
        lines.push_back(line);

    return lines;
}

// Function to print all tasks in a table format with text wrapping
void listAllTasks(const std::vector<Task> &tasks)
{
    const int idWidth = 8;
    const int titleWidth = 20;
    const int descriptionWidth = 30;
    const int dueDateWidth = 15;
    const int statusWidth = 10;

    const int totalWidth = idWidth + titleWidth + descriptionWidth + dueDateWidth + statusWidth + 9; // 6 for separators

    // Print table header
    std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;
    std::cout << "| " << std::left << std::setw(idWidth) << "Id"
              << "| " << std::setw(titleWidth) << "Title"
              << "| " << std::setw(descriptionWidth) << "Description"
              << "| " << std::setw(dueDateWidth) << "Due Date"
              << "| " << std::setw(statusWidth) << "Status" << "|" << std::endl;
    std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;

    // Print each task
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        const auto &task = tasks[i];
        // Wrap the description text
        std::vector<std::string> wrappedDescription = wrapText(task.description, descriptionWidth);

        // Print the first line of the task
        std::cout << "| " << std::left << std::setw(idWidth) << task.id
                  << "| " << std::setw(titleWidth) << task.title
                  << "| " << std::setw(descriptionWidth) << wrappedDescription[0]
                  << "| " << std::setw(dueDateWidth) << task.dueDate
                  << "| " << std::setw(statusWidth) << task.status << "|" << std::endl;

        // Print the remaining lines of the wrapped description
        for (size_t j = 1; j < wrappedDescription.size(); ++j)
        {
            std::cout << "| " << std::setw(idWidth) << ""
                      << "| " << std::setw(titleWidth) << ""
                      << "| " << std::setw(descriptionWidth) << wrappedDescription[j]
                      << "| " << std::setw(dueDateWidth) << ""
                      << "| " << std::setw(statusWidth) << "" << "|" << std::endl;
        }

        // Print separator line after each task except the last one
        if (i < tasks.size() - 1)
        {
            std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;
        }
    }

    // Print table footer
    std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;
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
    std::cout << "Successfully saved the tasks." << std::endl;
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
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

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
        std::cout << "6. Save the tasks" << std::endl;
        std::cout << "7. Save and Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To clear the newline from input buffer
        switch (choice)
        {
        case 1:
            addNewTask(tasks);
            std::cout << std::endl;
            break;
        case 2:
            makeTaskComplete(tasks);
            std::cout << std::endl;
            break;
        case 3:
            editTask(tasks);
            std::cout << std::endl;
            break;
        case 4:
            deleteTask(tasks);
            std::cout << std::endl;
            break;
        case 5:
            listAllTasks(tasks);
            std::cout << std::endl;
            break;
        case 6:
        case 7:
            saveTasksToCSV(tasks, filename);
            std::cout << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            std::cout << std::endl;
        }

    } while (choice != 7);

    return 0;
}