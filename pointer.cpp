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

