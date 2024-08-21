# To-Do CLI Application

## Overview

This project is a command-line interface (CLI) application that allows you to manage tasks efficiently written `C++`. It provides features to add, edit, delete, and mark tasks as complete. The tasks are saved to and loaded from a `.csv` file, ensuring data persistence between sessions. Additionally, tasks are displayed in a table format with text wrapping for better readability.

## Features

- **Add Task**: Create a new task with a unique ID, title, description, due date, and status.
- **Mark Task as Complete**: Update the status of a task to "COMPLETED" by searching for its ID or title.
- **Edit Task**: Modify the title, description, and due date of an existing task.
- **Delete Task**: Remove a task by searching for its ID or title.
- **List All Tasks**: Display all tasks in a table format with wrapped text to fit the columns.
- **Save Tasks to CSV**: Save the current list of tasks to a `.csv` file.
- **Load Tasks from CSV**: Load tasks from a `.csv` file at the start of the application.

## File Structure

- `main.cpp`: The main source file containing the implementation of the application.
- `tasks.csv`: The CSV file where tasks are stored. This file is created automatically if it doesn't exist.

## Getting Started

### Prerequisites

To compile and run this program, you'll need:

- A C++ compiler (e.g., `clang++`, `g++`)
- A terminal or command prompt

### Compilation

1. Clone or download the repository to your local machine.
2. Open your terminal or command prompt and navigate to the directory containing `main.cpp`.
3. Compile the code using a C++ compiler. For example, using `clang++`:

```bash
# With clang++ compiler
clang++ -std=c++20 main.cpp -o main
# or with g++ compiler
g++ main.cpp -o main
```

## How to Use

Upon running the application, you'll be presented with a menu:

1. Add Task: Follow the prompts to enter the task's title, description, and due date.
2. Mark Task as Complete: Enter the task ID or title to mark it as "COMPLETED".
3. Edit Task: Search for a task by ID or title, then update its details.
4. Delete Task: Remove a task by entering its ID or title.
5. List All Tasks: Display a table of all tasks with wrapped text in the description.
6. Save the Tasks: Save the current tasks to tasks.csv.
7. Save and Exit: Save the tasks to tasks.csv and exit the application.

### Example

```bash
$ ./main
Menu
1. Add task
2. Mark task as complete
3. Edit task
4. Delete task
5. List all tasks
6. Save and Exit
Enter your choice: 1
Enter title: task2
Enter description: task2
Enter due date: 2010-10-10
Successfully added new task

Menu
1. Add task
2. Mark task as complete
3. Edit task
4. Delete task
5. List all tasks
6. Save the tasks
7. Save and Exit
Enter your choice: 5
+-------------------------------------------------------------------+
| Id      | Title     | Description    | Due Date       | Status    |
+-------------------------------------------------------------------+
| FZXC0w  | task1     | task1 desc     | 2024/10/10     | PENDING   |
+-------------------------------------------------------------------+
| gYdxsJ  | task2     | task2          | 2010-10-10     | PENDING   |
+-------------------------------------------------------------------+
```
