#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
	int pid = fork();
	
	if (pid < 0){
		cout << "Fork failed to execute\n";
		exit(1);
	} else if (pid == 0){
		cout << "This is the child process\n"; 
		cout << "My Child ID is: " << (int)getpid() << "\n"; //Returns process ID for new process
	} else {
		int waiting = waitpid(pid, NULL, 0); //Waits for the child process to finish. NULL could be replaced with a pointer variable, which would be assigned the returned value of the child process
		cout << "This is the parent process\n";
		cout << "Child ID is: " << pid << "\n";
		cout << "My Parent ID is: " << (int)getpid() << "\n";
	}

	//Question code goes here
	cout << (int)getpid() << " Finished.\n";
}