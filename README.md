# CP386 Operating-Systems
Topics include operating system services, file systems, CPU scheduling, memory management, virtual memory, disk scheduling, deadlocks, concurrent processes, protection and distributed systems.

## A1
### TASK 1  
Write a C program (directory.c) to perform various operations on directories and associated system functions. Directories are frequently used in daily life to organize files in a well-structured manner. This program would use various system calls that are available in C programming to perform the operations. The program should perform the following directory operations:  

1. Creating a directory
2. Removing a directory
3. Getting the current working directory
4. Changing a directory (to one level up from the current directory)
5. Reading a directory
6. Closing a directory, the current directory
The program should present the user with a list of options to select the directory operation and keep looping until the user enters “q” on the keyboard. You can use the makefile to compile and run the program.

### TASK 2  
Create a C program (name it "filecopy.c") that copies the contents of one file to a destination file. This program will read data from one file and copy them to another. The first input that the program will need is the names of the two files: input file (“input.txt”) and output file (“output.txt”). Once the two file names have been obtained, the program must open the input file and create and open the output file. Each of these operations requires another system call. Possible error conditions for each system call must be handled. When the program tries to open the input file, it may find that there is no file of that name or that the file is protected against access. In these cases, the program should output an error message (another sequence of system calls) and then terminate abnormally (another system call).  

## A2



