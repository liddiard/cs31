#include <iostream>
#include <string>
using namespace std;

int tally (const string a[], int n, string target) {
    int tally = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            tally++;
        }
    }
    if (tally > 0) {
        return tally;
    }
    else {
        return -1;
    }
}

int findFirst (const string a[], int n, string target) {
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int findFirstSequence (const string a[], int n, string target, int &begin, int &end) {
    int length = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            begin = i;
            for (int j = i+1; j < n; j++) {
                if (a[j] == target) {
                    length++;
                }
                else {
                    end = begin+length;
                    return true;
                }
            }
        }
    }
    return false;
}

int positionOfMin(const string a[], int n) {
    
}

int moveToEnd (string a[], int n, int pos) {
    
}

int moveToBeginning(string a[], int n, int pos) {
    
}

int disagree(const string a1[], int n1, const string a2[], int n2) {
    
}

int removeDups(string a[], int n) {
    
}

bool subsequence(const string a1[], int n1, const string a2[], int n2) {
    
}

int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
    
}

int divide(string a[], int n, string divider) {
    
}

int main() {
    int b = 0;
    int e = 1;
    string test_array[]  = {"lorem", "lorem", "lorem", "ipsum", "dolor", "dolor", "sit", "lorem", "lorem"};
    cout << findFirstSequence(test_array, 9, "Lorem", b, e) << "\n";
    cout << b << ", " << e;
    
    cout << "\n";
}




