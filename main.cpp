#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

// Task struct data structure
// This struct holds all the necessary information for a task.
struct Task
{
    std::string id;          // Unique identifier for each task
    std::string title;       // Title of the task
    std::string description; // Detailed description of the task
    std::string status;      // Status of the task (e.g., PENDING, COMPLETED)
    std::string dueDate;     // Due date for the task
};

// Function to generate random unique id
// This function generates a random string of specified length to use as a unique ID for each task.
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

// Function to add a new task
// This function prompts the user for task details and adds the new task to the list.
void addNewTask(std::vector<Task> &tasks)
{
    Task newTask;
    std::cout << "Enter title: ";
    std::getline(std::cin, newTask.title);

    std::cout << "Enter description: ";
    std::getline(std::cin, newTask.description);

    std::cout << "Enter due date: ";
    std::getline(std::cin, newTask.dueDate);

    // Generate a unique ID for the task and set the status to "PENDING"
    newTask.id = generateUniqueID(6);
    newTask.status = "PENDING";

    // Add the new task to the list of tasks
    tasks.push_back(newTask);
    std::cout << "Successfully added new task" << std::endl;
}

// Function to mark a task as complete
// This function changes the status of a task to "COMPLETED" based on the task's ID or title.
void makeTaskComplete(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to mark as completed: ";
    std::getline(std::cin, search);

    for (auto &task : tasks)
    {
        if (task.id == search || task.title == search)
        {
            // Update the task status to "COMPLETED"
            task.status = "COMPLETED";
            std::cout << "Successfully marked the task completed" << std::endl;
            return; // Exit from the loop to prevent further iterations after marking the task complete
        }
    }
    std::cout << "Task not found" << std::endl;
}

// Function to edit an existing task
// This function allows the user to modify the description and due date of a task.
void editTask(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to edit: ";
    std::getline(std::cin, search);

    for (auto &task : tasks)
    {
        if (task.id == search || task.title == search)
        {
            std::cout << "Enter new description: ";
            std::getline(std::cin, task.description);

            std::cout << "Enter new due date: ";
            std::getline(std::cin, task.dueDate);
            std::cout << "Successfully updated the task" << std::endl;
            return; // Exit from the loop after updating the task
        }
    }
    std::cout << "Task not found" << std::endl;
}

// Function to delete a task
// This function removes a task from the list based on its ID or title.
void deleteTask(std::vector<Task> &tasks)
{
    std::string search;
    std::cout << "Enter id or title of the task to delete: ";
    std::getline(std::cin, search);

    auto it = tasks.begin();
    while (it != tasks.end())
    {
        if (it->id == search || it->title == search)
        {
            tasks.erase(it); // Erase the task from the list
            std::cout << "Task deleted successfully." << std::endl;
            return; // Exit the function after deletion
        }
        else
        {
            ++it; // Move to the next task
        }
    }

    std::cout << "Task not found" << std::endl;
}

// Function to split the text into multiple lines based on the given width
// This function ensures that long text descriptions are properly wrapped when displayed in the console.
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
// This function displays all tasks in a tabular format with proper alignment and text wrapping for descriptions.
void listAllTasks(const std::vector<Task> &tasks)
{
    // Define column widths for the table
    const int idWidth = 8;
    const int titleWidth = 20;
    const int descriptionWidth = 30;
    const int dueDateWidth = 15;
    const int statusWidth = 10;

    // Calculate the total width of the table
    const int totalWidth = idWidth + titleWidth + descriptionWidth + dueDateWidth + statusWidth + 9; // 9 for separators

    // Print table header
    std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;
    std::cout << "| " << std::left << std::setw(idWidth) << "Id"
              << "| " << std::setw(titleWidth) << "Title"
              << "| " << std::setw(descriptionWidth) << "Description"
              << "| " << std::setw(dueDateWidth) << "Due Date"
              << "| " << std::setw(statusWidth) << "Status" << "|" << std::endl;
    std::cout << "+" << std::string(totalWidth, '-') << "+" << std::endl;

    // Print each task in the table
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        const auto &task = tasks[i];
        // Wrap the description text to fit within the column width
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

// Function to save tasks to a CSV file
// This function writes the list of tasks to a CSV file for persistent storage.
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

// Function to load tasks from a CSV file
// This function reads tasks from a CSV file and populates the list of tasks.
void loadTasksFromCSV(std::vector<Task> &tasks, const std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        Task task;

        // Extract each field from the CSV line
        std::getline(iss, task.id, ',');
        task.id = task.id.substr(1, task.id.size() - 2); // Remove surrounding quotes

        std::getline(iss, task.title, ',');
        task.title = task.title.substr(1, task.title.size() - 2); // Remove surrounding quotes

        std::getline(iss, task.description, ',');
        task.description = task.description.substr(1, task.description.size() - 2); // Remove surrounding quotes

        std::getline(iss, task.status, ',');
        task.status = task.status.substr(1, task.status.size() - 2); // Remove surrounding quotes

        std::getline(iss, task.dueDate, ',');
        task.dueDate = task.dueDate.substr(1, task.dueDate.size() - 2); // Remove surrounding quotes

        tasks.push_back(task); // Add the task to the list
    }
}

// Main function
// This is the entry point of the program where the menu is displayed and user choices are handled.
int main()
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    std::vector<Task> tasks;                  // Vector to store tasks
    const std::string filename = "tasks.csv"; // Filename to store tasks in CSV format

    loadTasksFromCSV(tasks, filename); // Load existing tasks from the file

    int choice;
    do
    {
        // Display the menu
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
        std::cin.ignore(); // To clear the newline from the input buffer

        // Handle user choices
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
            saveTasksToCSV(tasks, filename); // Save tasks to file before exiting
            std::cout << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            std::cout << std::endl;
        }

    } while (choice != 7); // Continue until the user chooses to exit

    return 0; // Exit the program
}
