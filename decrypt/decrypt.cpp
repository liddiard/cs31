#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

void toLowerCase(char s[]) {
    for (int i=0; s[i] != '\0'; i++) {
        s[i] = tolower(s[i]);
    }
}

void toUpperCase(char s[]) {
    for (int i=0; s[i] != '\0'; i++) {
        s[i] = toupper(s[i]);
    }
}

char separateWords(char s[]) {

}



bool decrypt(istream& cipherstream, char crib[]) {
    
    /* parse the input into one continuous cstring */
    toLowerCase(crib);
    const int MAXCOL = 81;
    const int MAXROW = 51;
    const int MAXCHAR = 4131;
    int write_head = 0;
    char message[MAXCHAR];
    char line[MAXCOL];
    for (int i = 0; i < MAXCHAR; i++) {
        message[i] = '\0'; //visit every character in the array and set it to the null byte
    }
    do {
        cipherstream.getline(line, MAXCOL);
        for (int j = 0; line[j] != '\0'; j++) {
            if (isalpha(line[j])) {
                message[write_head] = line[j];
            } else {
                message[write_head] = ' ';
            }
            write_head++;
        }
        message[write_head] = ' ';
        write_head++;
    } while (line[0] != '\0');
    
    toLowerCase(message);
    
    /* separate message words */
    const int MAXSUP = 2066;
    const int MAXSUB = 81;
    char separate[MAXSUP][MAXSUB];
    for (int i = 0; i < MAXSUP; i++) {
        for (int j = 0; j < MAXSUB; j++) {
            separate[i][j] = '\0'; //visit every character in the array and set it to the null byte
        }
    }
    int word_number = 0;
    int char_number = 0;
    for (int head = 0; message[head] != '\0'; head++) {
        if (message[head] == ' ') {
            word_number++;
            char_number = 0;
        } else {
            separate[word_number][char_number] = message[head];
            char_number++;
        }
    }
    
    /* separate crib words */
    char crib_separate[MAXSUP][MAXSUB];
    for (int i = 0; i < MAXSUP; i++) {
        for (int j = 0; j < MAXSUB; j++) {
            crib_separate[i][j] = '\0'; //visit every character in the array and set it to the null byte
        }
    }
    int crib_word_number = 0;
    int crib_char_number = 0;
    for (int head = 0; crib[head] != '\0'; head++) {
        if (crib[head] == ' ') {
            crib_word_number++;
            crib_char_number = 0;
        } else {
            crib_separate[crib_word_number][crib_char_number] = crib[head];
            crib_char_number++;
        }
    }
    
    /* test output */    
    for (int i = 0; i <= word_number; i++) {
        cout << strlen(separate[i]) << ", ";
    }
    
    cout << "\n";
    
    for (int i = 0; i <= crib_word_number; i++) {
        cout << strlen(crib_separate[i]) << ", ";
    }
}

int main () {
    /* open the input file */
    ifstream infile("test_input.txt");
    if (!infile) {
        cerr << "opening file failed.";
        return -1;
    }
    
    char test_crib[10] = "Hello son";
    
    decrypt(infile, test_crib);
    
}