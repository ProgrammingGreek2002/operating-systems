# CP386 Operating-Systems
Topics include operating system services, file systems, CPU scheduling, memory management, virtual memory, disk scheduling, deadlocks, concurrent processes, protection and distributed systems.

## A1
TASK 1  
Write a C program (directory.c) to perform various operations on directories and associated system functions. Directories are frequently used in daily life to organize files in a well-structured manner. This program would use various system calls that are available in C programming to perform the operations. The program should perform the following directory operations:  

1. Creating a directory
2. Removing a directory
3. Getting the current working directory
4. Changing a directory (to one level up from the current directory)
5. Reading a directory
6. Closing a directory, the current directory
The program should present the user with a list of options to select the directory operation and keep looping until the user enters “q” on the keyboard. You can use the makefile to compile and run the program.

TASK 2  
Create a C program (name it "filecopy.c") that copies the contents of one file to a destination file. This program will read data from one file and copy them to another. The first input that the program will need is the names of the two files: input file (“input.txt”) and output file (“output.txt”). Once the two file names have been obtained, the program must open the input file and create and open the output file. Each of these operations requires another system call. Possible error conditions for each system call must be handled. When the program tries to open the input file, it may find that there is no file of that name or that the file is protected against access. In these cases, the program should output an error message (another sequence of system calls) and then terminate abnormally (another system call).  

## A2
TASK 1  
Create a C program (name it "assignment_average.c") that finds the average grade of the course assignments. The teacher gives two assignments for every chapter. You must calculate the average grade for each assignment in all the chapters.  

The program should have a teacher process that reads the grades ("sample_in_grades.txt" grades file is available under the Assignment 1 section on MyIs) of all assignments of all the chapters and creates a two-dimensional matrix of grades.
Teacher process then creates a "GradTA" process. Each "GradTA" process takes care of solving a chapter.
Each "GradTA" process would create "TA" processes and pass one assignment to each of them. "TA" process would calculate and print the average for that assignment.  

The input file "sample_in_grades.txt" contains data for three chapters and two assignments for each chapter (six columns). The first two columns are grades for two assignments for chapter 1, the following two columns are the grades for two assignments for chapter 2, and the last two columns are the grades for two assignments for chapter 3. The Grades file contains grades for 10 students. Make sure your program should dynamically create GTAs and TAs processes based on the number of the chapters (you can assume that each chapter will always have two assignments).  

TASK 2  
In C, write a program (name it "process_management.c") that will involve using the UNIX fork(), exec(), wait(), dup2(), and pipe() system calls and includes code to accomplish the following tasks:

A parent process uses fork system calls for creating children processes, whenever required, and collecting the output of these. The following steps must be completed:

a) Creation of a child process to read the content (A LINUX COMMAND PER LINE) of the input file. The file contents will be retrieved by the child process in the form of a string using a shared memory area.  

b) Creation of another child(s) process(es) that will execute these Linux commands one by one. The process(es) will give the output using a pipe in the form of a string.  

c) Write the output after executing the commands in a file named "output.txt" by the parent process.  

d) The command-line arguments must be used by the parent process to read the file name. The parent process would create a child process and it will read the contents of the file ("sample_in_process.txt"), (not the parent process).

## A3
TASK 1  
Write a C program to validate the solution to the Sudoku puzzle. A Sudoku puzzle uses a 9 x 9 grid in which each column and row, as well as each of the nine 3x3 sub-grids, must contain all the digits 1 ... 9. Figure below presents an example of a valid 9 x 9 Sudoku puzzle solution. This program implements a multithreaded application that reads a Sudoku puzzle solution from a file (“sample_in_sudoku.txt”) and validates it. The code is in sudoku.c

TASK 2
Write a C program to find the average waiting time and turn-around time for the pre-defined set of tasks. The program will read a predefined set of tasks from file “sample_in_schedule.txt” and will schedule the tasks based on the First Come First Served scheduling algorithm (non preemptive). The columns in “sample_in_schedule.txt” present the thread id, its arrival time, and its burst time, respectively. The code is in fsfs.c

## A4  
TASK 1  

A race condition can occur within a critical section and can generate inconsistent results. When multiple threads execute in critical sections, their results vary according to the order in which they execute. Race conditions can be avoided when critical sections are treated as atomic instructions. The prevention of race conditions can be achieved through proper thread synchronization using mutex locks.

The mutex locks represent the fundamental synchronization technique used with Pthread. A mutex lock is used to protect critical sections of code that is, a thread acquires the lock before entering a critical section and releases it upon exiting the critical section. Pthread uses the pthread_mutex_t data type for mutex locks.

The code provided in a file sample_code_skeleton_stack.c contains an implementation of a stack using a linked list. This program creates ten threads to perform Push() operation and ten threads to perform Pop() operation. This program currently has a race condition and is not appropriate for a concurrent environment. Fix the race condition by using Pthread mutex locks. The code is in stack.c  

TASK 2  

For this Question, you are provided a skeleton code in a file sample_code_skeleton_thread_synchronization.c. Some functions are completely implemented, and some are partially implemented. Additionally, you can write your own functions if required. Complete the program as per following details so that we can have functionality as described in the synopsis above. Write all the code in single C file:  

The code provided reads the content of file for you and populate the threads information in a dynamic array of type struct thread. You may some more members to this data structure. If you want to initialize those members, then you can possibly do that during the file read.
The main() function already contains the code to create and invoke threads. However, there is no synchronization logic added to it. If required, you will add some suitable code in the while loops to perform the tasks required.
The threadRun() function also contains the code that a thread must run. However, again the synchronization logic is missing. Add the suitable code before and after the critical section.
You will need to create and use POSIX semaphore(s) to implement the required logic.

## A5
In this question, you will write a multi-threaded program that implements the banker's algorithm. 
Customers request and release resources from the bank. The banker will keep track of the resources. The 
banker will grant a request if it satisfies the safety algorithm. If a request does not leave the system in a 
safe state, the banker will deny it.

























