#include <iostream>
using namespace std;

    // return true if two C strings are equal
bool match(const char str1[], const char str2[])
{
    const char *p1 = str1;
    const char *p2 = str2;
    while (*p1 != 0  &&  *p2 != 0)  // zero bytes at ends
    {
        if (*p1 != *p2)  // compare corresponding characters
            return false;
        p1++;            // advance to the next character
        p2++;
    }
    return *p1 == *p2;   // both ended at same time?
}

int main()
{
    char a[10] = "pointy";
    char b[10] = "pointless";

    if (match(a,b))
        cout << "They're the same!\n";
}