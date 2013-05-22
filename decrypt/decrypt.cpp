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

bool decrypt(istream& cipherstream, const char crib_const[]) {
    
    if (strlen(crib_const) > 80) {
        return false;
    }
    
    char crib[80];
    /* parse the input into one continuous cstring */
    for (int i = 0; i < 80; i++) {
        crib[i] = crib_const[i];
    }
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
    while(1) {
        cipherstream.getline(line, MAXCOL);
        if (line[0] == '\0') {
            break;
        }
        for (int j = 0; line[j] != '\0'; j++) {
            if (isprint(line[j])) {
                message[write_head] = line[j];
                write_head++;
            } else if (write_head > 0 && message[write_head-1] == ' ') {
                ; //prevents multiple consecutive spaces from being written
            } else {
                message[write_head] = ' ';
                write_head++;
            }
        }
        if (message[write_head-1] != ' ') { //prevents multiple consecutive spaces from being written
            message[write_head] = '\n';
            write_head++;
        }
    }
    
    toLowerCase(message);
    
    /* test output
    for (int i = 0; message[i] != '\0'; i++) {
        cout << message[i];
    }
    */
    
    /* clean crib */
    int MAXCOL_CRIB = 80;
    char crib_clean[MAXCOL_CRIB];
    int crib_clean_head = 0;
    for (int i = 0; i < MAXCOL_CRIB; i++) {
        crib_clean[i] = '\0'; //visit every character in the array and set it to the null byte
    }
    for (int i = 0; crib[i] != '\0'; i++) {
        if (isalpha(crib[i])) {
            crib_clean[crib_clean_head] = crib[i];
            crib_clean_head++;
        } else if (crib_clean_head > 0 && crib_clean[crib_clean_head-1] == ' ') {
            ; //prevents multiple consecutive spaces from being written
        } else {
            crib_clean[crib_clean_head] = ' ';
            crib_clean_head++;
        }
    }
    
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
    for (int head = 0; crib_clean[head] != '\0'; head++) {
        if (crib_clean[head] == ' ') {
            crib_word_number++;
            crib_char_number = 0;
        } else {
            crib_separate[crib_word_number][crib_char_number] = crib_clean[head];
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
        if (strlen(separate[i]) == strlen(crib_separate[0])) { //check if each word is equal to the length of the first word of the crib
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
    
    /* test output
    for (int i = 0; i < match_beginning_word_head; i++) {
        cout << "\n" << match_beginning_word[i] << "\n";
    }
    */
    
    /* match_beginning_word is an array of integers that stores
     * the positions of the first WORD in each phrase which fully matches the crib's length heuristic */
    
    /* construct a simple letter-to-letter key */
    char key[MAXCHAR/2][2];
    for (int i = 0; i < match_beginning_word_head; i++) { //for each match
        int key_head = 0;
        //cout << "ITERATION: " << i << "\n"; //test output
        for (int j = 0; j <= crib_word_number; j++) { //for each word in each match
            for (int k = 0; k < strlen(crib_separate[j]); k++) { //for each character in each word
                key[key_head][0] = separate[(match_beginning_word[i]+j)][k];
                key[key_head][1] = crib_separate[j][k];
                key_head++;
            }
        }
        
        /* test output
        for (int j = 0; j < key_head; j++) {
            cout << key[j][0] << " : " << key[j][1] << "\n";
        }
        */
        
        /* check if the key is valid (has unique letter assignments) */
        int message_match = 0;
        int crib_match = 0;
        for (int j = 0; j < key_head; j++) { //for each letter...
            for (int k = 0; k < key_head; k++) { //...compare to each other letter
                if (key[j][0] == key[k][0]) {
                    message_match++;
                    if (key[j][1] != key[k][1]) {
                        //cout << "invalid key\n";
                        goto checkMatch; //NOPE, they don't match, this key is not valid
                    }
                    crib_match++;
                }
            }
        }
        if (crib_match == message_match) {
            //cout << "valid key found!\n"; //for each letter that has a match, cout the uppercase version, otherwise cout the original w/o transforming case, and return true
            for (int j = 0; j < write_head; j++) { //for each character in message
                for (int k = 0; k < key_head; k++) { //for each key/value pair in key
                    if (key[k][0] == message[j]) {
                        message[j] = toupper(key[k][1]);
                    }
                }
            }
            
            
            for (int j = 0; j < write_head; j++) {
                cout << message[j];
            }
            
            return true;
        }
        checkMatch: ; //placed here so i auto-incremented
    }
    return false; //if the function gets here, no valid matches were found
}

void runtest(const char filename[], const char crib[])
{
    cout << "====== " << crib << endl;
    ifstream cfile(filename);
    if (!cfile)
    {
        cout << "Cannot open " << filename << endl;
        return;
    }
    bool result = decrypt(cfile, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"

    runtest("test_input.txt", "my secret");
    runtest("test_input.txt", "shadow");
}