# COMPSCI 377 LAB #2: Fork and Exec

## Purpose

This lab is designed to introduce you to processes. Using various system calls in C++, we can create and modify processes to further help our code. Please make sure that all of your answers to questions in these labs come from work done on the Edlab environment – otherwise, they may be inconsistent results and will not receive points.

Please submit your answers to this lab on Gradescope in the assignment marked “Lab #2’. All answers are due by the end of discussion, approximately 50 minutes after it has started. The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by yourself. Please raise your hand if you have any questions during the lab section. Questions and Parts have a number of points marked next to them to signify their weight in this lab’s final grade.

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-lab-fork-exec.git
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-lab-fork-exec
```

This repo includes a Makefile that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.

## Part 1: Pointers (15 Points)

When programming in C++, we will frequently make use of pointers. Every variable that we make use of in this class has a memory location, which we can access through the ‘&’ operator. When we have such a memory location, we can then access its stored value through the ‘*’ operator. We use this same operator when declaring our pointers in the code. As an example, take the following code:

pointer.cpp
```c++
#include <string>
#include <iostream>

using namespace std;

int main() {
	int original = 1; //variable that stores an integer value of 1
	int *pointer = &original; //variable that stores the memory address of ‘original’

	cout << original << "\n"; //prints out the stored value of original: “1”
	cout << pointer << "\n"; //prints out the stored value of pointer (some memory address)
	cout << *pointer << "\n"; //prints out the stored value of the variable at the location of pointer (original): "1"

	//Code goes here

	return 1;
}
```

As can be seen in the code, pointers allow for a lot of memory reference to be carried out in C++. We can also combine multiple operators together. This means that ‘&(*pointer)’ will result in just ‘pointer’, but there could be problems if ‘*(*pointer)’ is called, since that would be looking at the data stored with memory address of ‘*pointer’. In general, using '(*variable)' for something such as 'variable = 1' will throw an error.

## Part 2: Fork (10 Points)

The fork() command makes a complete copy of the currently running program, running from the same state in which the function was called. For these two copies, we are able to determine which process is the original through the value returned by the fork() command, called the process ID. Process IDs are used by operating systems to identify active processes – when a process runs, the process ID of the next process to start will increment by 1. This means that if we run one process with process ID 22100, and then run 999 more processes on the system, the next process will have a process ID of 23100 instead. As we will see, these IDs allow us to manipulate processes to help us with new actions in our code. Within C++ code, we can use the getpid() command to get the current process id of the process. As an example, take the following code:

fork.cpp
```c++
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
```

When you run this code, the parent process should print out its child’s process ID and its own. The child process should just print out its own process ID. A good  point to note is that without any code to prevent it, the parent process can potentially finish before the child process and vice versa. In part 4 in this lab we will go over how to order the parent and child code accurately.

## Part 3: Exec (10 Points)

The exec family of functions allows for us to run system commands from C++ code. In general, it is useful for running programs different than the one currently being run. By giving the command the name of an executable and some arguments, it can cause the OS to replace its current process with the loaded code, and simultaneously can pass arguments into the new process. No matter the arguments, the final arguments must always be NULL as to provide an endpoint to the code. Additionally, we can also run system commands such as ‘ls’ and ‘mkdir’ using the exec family of functions. As an example, take the two following pieces of code:

print.cpp
```c++
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Printing arguments...\n";
	for (int i = 0; i < argc-1; i++){ //Iterates through the arguments given
		cout << "Got argument " << argv[i+1] << "\n"; //Prints out each argument it receives
	}
}
```

exec.cpp
```c++
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char *arguments[4];
	arguments[0] = (char*)"./print";
	arguments[1] = (char*)"one";
	arguments[2] = (char*)"two";
	arguments[3] = NULL;

	char *other_arguments[2];
	other_arguments[0] = (char*)"ls";
	other_arguments[1] = NULL;

	//Question code goes here
	
	execvp(arguments[0], arguments);
	
	execvp(other_arguments[0], other_arguments);
}
```

When ./exec is run after being created from exec.cpp with the ‘make’ command, it will run print.cpp with the ./print command. In doing this, it also passes the arguments of “one” and “two”. The code in print.cpp will then run, printing each of the arguments passed to it. However, if you see the output, you might be wondering why the ‘ls’ command doesn’t work. This is because, as mentioned earlier, the OS replaces the code of ./exec with the code for ./print once execvp in this case is called. Thus, the second execvp will never run. If it did, it would simply run the ls command on the machine.

## Part 4: Processes (15 Points)

There are other useful commands we can run when creating and modifying processes. First, we have the wait() and waitpid() commands, which are used to make a process wait until a different process has finished. The wait() function is fairly simply, and makes the process wait until its children finish first. The waitpid() command is slightly more complicated. For this lab and class, we won’t fully go over the options for waitpid(), though it is interesting reading here: https://linux.die.net/man/2/waitpid. For waitpid(), the first parameter is a process ID. If this is a valid process ID (such as the one returned by fork()), then the process will wait until that child process has finished. This will also work if the process ID is negative (for example, pid -1234 will be treated as pid 1234). If the process ID is -1, then the program will wait for any child process to finish, effectively becoming identical to the wait() command. If the process ID is 0, it will wait for any child process with a process group ID equal to that of the parent. As an example of how waitpid() can work with code, take the following example:

wait.cpp
```c++
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
		cout << "My Child ID is: " << (int)getpid() << "\n";
	} else {
		int waiting = waitpid(pid, NULL, 0); //Waits for the child process to finish. NULL could be replaced with a pointer variable, which would be assigned the returned value of the child process
		cout << "This is the parent process\n";
		cout << "Child ID is: " << pid << "\n";
		cout << "My Parent ID is: " << (int)getpid() << "\n";
	}

	cout << (int)getpid() << " Finished.\n";
}
```

While it is only slightly different than fork.cpp, running it will show that the program always has the child program finish before the parent program. This is because when the parent process gets to the line with waitpid(), it stops entirely until the child process finishes. In operating systems, this is commonly used to make sure processes execute in the correct order that they need to for many applications.
