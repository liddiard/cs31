#include <iostream>
using namespace std;

int main () {
    string *fp;
    string fish[5];
    fp = &fish[4];
    *fp = "salmon";
    *(fish + 3) = "yellowtail";
    fp -= 3;
    fp[1] = "eel";
    fp[0] = "tuna";
    bool d = fp == fish;
    bool b = *fp == *(fp+1);
    cout << b;
    
    for (int i = 0; i < 5; i++)
        cout << fish[i] << "\n";
}