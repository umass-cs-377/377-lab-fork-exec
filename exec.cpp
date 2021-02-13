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
