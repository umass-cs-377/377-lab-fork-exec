#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Printing arguments...\n";
	for (int i = 0; i < argc-1; i++){
		cout << "Got argument " << argv[i+1] << "\n";
	}
}
