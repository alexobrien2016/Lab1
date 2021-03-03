# Lab1 Containerized Mini-Shell
   * INET 4001 group assignment wrote by Team 8: \
   Omar Porte <porte657@umn.edu>, \
   Alexander O'Brien <obri0434@umn.edu>, \
   Shiwen Hou <hou00045@umn.edu>.
   * This assignment is to write a linux mini-shell in c which have functionality to run both built commands as well as other executables, manage child/parent relationship, and run in a separate Linux namespace.
# Installation & Usage 
## Requirements
   * Linux >= 2.6.25
   * Ubuntu 18.04.4 \
Those versions are the ones used during development.
## Building the program
Download the file. (must including `lab1.c`, `functions.h`) 
## Running the program
After downloading the source, run `./lab1` from the project root and get in to the shell.
# Main Project Instructions
## Mandatory
* Need to start with a C program
* Start a new environment using Linux Namespaces for shell
* Accept in a number of arguments from a command line
* Need to have standard interaction
* Need to support the "Built in" commands to set the hostname(`sethostname`), change root(`change root`) and get the current PID (`showpid`).
* The shell should exit gracefully at all conditions with proper error messages.
* Should give proper usage statements on improper commands or arguments to commands.
* Using "script" to capture the testing to a file.
## Flags arguments of clone():
* **SIGCHLD**: the child termination signal
* **CLONE_NEWUSER**: User and group changes
* **CLONE_NEWUTS**: Setup new hostname and domain
* **CLONE_NEWIPC**: New namespace for IPC
* **CLONE_NEWNET**: New network namespace
* **CLONE_NEWNS**: New mount namespace
## Commands:
* `cd`: change the current working directory
* `ls`: list directory contents of files and directories
* `sethostname`: built in comment to set the hostname 
* `showpid`: show the current process ID (PID)
* `changeroot`: change the root directory
* `pwd`: print the path of working directory
* `exit`: exit the shell where it is currently running
## Functions:
* `shell_func`: Takes no arguements. Creates the shell with a while loop and executes the the argv by using strcmp to compare the string to commands like cd or sethost.
* `execute_cmd`: Takes in a pointer to an array of pointers. Used in the shell_func to execute commands (argv).
* `parse`: Takes in a pointer to the line and a pointer to an array of pointers. Used to parse the command line in order to get the different args. 
# File Breakdown:
README.txt \
Lab1.c \
functions.h \
INET_4001_test
