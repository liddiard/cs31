#include <iostream>
using namespace std;

void deleteG(char s[]) {
    char* ptr = s;
    while (*ptr != '\0') {
        if (*ptr == 'g' || *ptr == 'G') {
            while(*ptr != '\0') {
                *ptr = *(ptr+1); //move everything forward one to delete the offending 'g'/'G'
                ptr++;
            }
            ptr = s; //move the pointer back to the beginning of the array (somewhat inefficient, but I'm not a genius yet okay Smallberg)
        }
        ptr++;
    }
}

int main()
{
    char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
    deleteG(msg);
    cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
}