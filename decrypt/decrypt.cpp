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
    
    /* use length-comparing heuristic */
    int match_beginning_word[MAXCHAR];
    int match_beginning_word_head = 0;
    for (int i = 0; i < MAXCHAR; i++) {
        match_beginning_word[i] = '\0'; //visit every character in the array and set it to the null byte
    }
    for (int i = 0; i <= word_number; i++) {
        if (strlen(separate[i]) == strlen(crib_separate[0])) {
            for (int j = 1; j <= crib_word_number; j++) {
                if (strlen(separate[i+j]) != strlen(crib_separate[j])) {
                    break;
                } else if (j == crib_word_number) {
                    match_beginning_word[match_beginning_word_head] = i;
                    match_beginning_word_head++;
                }
            }
        }
    }
    
    /* test output */
    for (int i = 0; i < match_beginning_word_head; i++) {
        cout << match_beginning_word[i] << "\n";
    }
    
    /* match_beginning_word is an array of integers that stores
     * the positions of the first WORD in each phrase which fully matches the crib's length heuristic */
    
    /* construct a simple letter-to-letter key */
    char key[MAXCHAR/2][2];
    for (int i = 0; i < match_beginning_word_head; i++) { //for each match
        int key_head = 0;
        cout << "***" << i << "***" << "\n"; //test output
        for (int j = 0; j <= crib_word_number; j++) { //for each word in each match
            for (int k = 0; k < strlen(crib_separate[j]); k++) { //for each character in each word
                key[key_head][0] = separate[(match_beginning_word[i]+j)][k];
                key[key_head][1] = crib_separate[j][k];
                key_head++;
            }
        }
        
        /* test output */
        for (int j = 0; j < key_head; j++) {
            cout << key[j][0] << " : " << key[j][1] << "\n";
        }
        
        /* check if the key is valid (has unique letter assignments) */
        int message_match = 0;
        int crib_match = 0;
        for (int j = 0; j < key_head; j++) { //for each letter...
            for (int k = 0; k < key_head; k++) { //...compare to each other letter
                if (key[j][0] == key[k][0]) {
                    message_match++;
                    if (key[j][1] != key[k][1]) {
                        cout << "invalid key";
                        goto checkMatch; //ruh-roh, they don't match, this key is not valid
                    }
                    crib_match++;
                }
            }
        }
        if (crib_match == message_match) {
            cout << "valid key found!"; //for each letter that has a match, cout the uppercase version, otherwise cout the original w/o transforming case, and return true
            for (int j = 0; j < write_head; j++) { //for each character in message
                for (int k = 0; k < key_head; k++) { //for each key/value pair in key
                    if (key[k][0] == message[j]) {
                        message[j] = toupper(key[k][1]);
                    }
                }
            }
            
            /* test output */
            for (int j = 0; j < write_head; j++) {
                cout << message[j];
            }
            return true;
        }
        checkMatch: ; //placed here so i auto-incremented
    }
    return false; //if the function gets here, no valid matches were found
}

int main () {
    /* open the input file */
    ifstream infile("test_input.txt");
    if (!infile) {
        cerr << "opening file failed.";
        return -1;
    }
    
    char test_crib[10] = "Heleo son";
    
    decrypt(infile, test_crib);
    
}