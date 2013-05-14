#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

void makeLowerCase(char s[]) {
    for (int k=0; s[k] != '\0'; k++) {
        s[k] = tolower(s[k]);
    }
}

void makeUpperCase(char s[]) {
    for (int k=0; s[k] != '\0'; k++) {
        s[k] = toupper(s[k]);
    }
}

bool decrypt(istream& cipherstream, const char crib[]) {
    
}

int main () {
    ifstream infile("test_input.txt");
    if (!infile) {
        cerr << "opening file failed.";
    }
    const int MAXCOL = 80 +1;
    const int MAXROW = 50;
    char line[MAXCOL];
    char input_file[MAXROW][MAXCOL];
    
    int line_number = 0;
    while (line[0] != '\0') {
        infile.getline(line, MAXCOL);
        strcpy(line, input_file[line_number]);
        //cout << line << "\n";
        line_number++;
    }
    cout << input_file[1];
}