#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool decrypt(istream& cipherstream, const char crib[]) {

}

int main () {
    ifstream infile("test_input.txt");
    if (!infile) {
        cerr << "opening file failed.";
    } else {
        cout << "opening file successful.";
    }
    const int MAX = 200;
	char line[MAX];
	infile.getline(line, MAX);
    cout << line;
}