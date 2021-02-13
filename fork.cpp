#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main() {
	int pid = fork();
	
	if (pid < 0){ //The value returned by fork () is less than 0 if the command fails to execute, usually an error
		cout << "Fork failed to execute\n";
		exit(1);
} else if (pid == 0){ //The value returned by fork() is 0 if the process is the new process (called the ‘child’)
		cout << "This is the child process\n"; 
		cout << "My Child ID is: " << (int)getpid() << "\n"; //Returns process ID for new process
	} else { //The value returned by fork() is some positive value if it is the original process (called the ‘parent’)
		cout << "This is the parent process\n";
		cout << "Child ID is: " << pid << "\n"; //The return value is the process ID for the created child
		cout << "My Parent ID is: " << (int)getpid() << "\n"; //Returns process ID for original process
	}

	//Question code goes here
	cout << (int)getpid() << " Finished.\n";
}
