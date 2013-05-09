#include <iostream>
#include <string>
#include <cassert>
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
    if (n == 0) {
        return -1;
    }
    string smallest = a[0];
    int smallest_pos = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < smallest) {
            smallest = a[i];
            smallest_pos = i;
        }
    }
    return smallest_pos;
}
 
int moveToEnd (string a[], int n, int pos) {
   string pop = a[pos];
   for (int i = pos; i < (n-1); i++) {
       a[i] = a[i+1];
   }
   a[n-1] = pop;
   return pos;
}
 
int moveToBeginning(string a[], int n, int pos) {
    string pop = a[pos];
    for (int i = pos; i > 0; i--) {
        a[i] = a[i-1];
    }
    a[0] = pop;
    return pos;
}
 
int disagree(const string a1[], int n1, const string a2[], int n2) {
    int match;
    for (int i = 0; i < n1; i++) {
        match = i;
        if (a1[i] != a2[i]) {
           return match;
        }
    }
    if (n1 >= n2) {
        return match;
    }
    else {
        return match+1; //clarify w/ spec
    }
}
 
int removeDups(string a[], int n) {
    int removed = 0;
    int traverse = n;
   for (int i = 0; i < traverse; i++) {
       bool first_time = true;
       for (int j = 0; j < traverse; j++) {
           if ((!first_time) && (a[i] == a[j])) {
               moveToEnd(a, n, j);
                removed++;
               traverse--;
           }
           else if (a[i] == a[j]) {
               first_time = false;
           }
           else {;}
       }
   }
   return removed;
}
 
bool subsequence(const string a1[], int n1, const string a2[], int n2) {
   int substring_pos = 0;
   for (int i = 0; i < n1; i++) {
       if (a1[i] == a2[substring_pos]) {
           substring_pos++;
       }
   }
   if (substring_pos >= n2) { //technically bad coding; should be "=="
       return true;
   }
   else {
       return false;
   }
}
 
int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
    for (int i = 1; i < n1; i++) {
        if (a1[i] < a1[i-1]) {
            return -1;
        }
    }
    for (int i = 1; i < n2; i++) {        
        if (a2[i] < a2[i-1]) {
            return -1;
        }        
    }
    // if function reaches here, both arrays are non-decreasing
    int total_elements = n1+n2;
    if (total_elements > max) {
        return -1;
    }
    // if function reaches here, both arrays can fit in result
    else {
        // just get everything in the array
        for (int i = 0; i < n1; i++) {
            result[i] = a1[i];
        }
        for (int i = 0; i < n2; i++) {
            result[n1+i] = a2[i];
        }
    }
    // now sort everything
    for (int i = 0; i < total_elements; i++) {
        moveToEnd(result, total_elements, positionOfMin(result, total_elements-i)); //tricky, huh? decreases the scope the function's looking at with each iteration. ends up sorting everything alphabetically.
    }
    return (n1+n2);
}
 
int divide(string a[], int n, string divider) {
    for (int i = 0; i < n; i++) {
        moveToEnd(a, n, positionOfMin(a, n-i)); //tricky, huh? decreases the scope the function's looking at with each iteration. ends up sorting everything alphabetically.
    }
    for (int i = 0; i < n; i++) {
        if (a[i] >= divider) {
            return i;
        }
    }
}
 
int main() {
    int b = 0;
    int e = 1;
    string test_array[]  = {"beads", "bees", "buster", "sit", "zeta", "zzyzx", "zzyzx"};
    string test_array_2[]  = {"amet", "dolor", "lorem"};
    cout << divide(test_array, 7, "lucille") << "\n";
    for (int i = 0; i < 7; i++) {
        cout << test_array[i];
    }

    cout << "\n";
}