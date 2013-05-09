#include <iostream>
#include <string>
#include <cassert>
using namespace std;
 
int tally (const string a[], int n, string target) {
    if (n<0) {
        return -1;
    }
    int tally = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            tally++;
        }
    }
    return tally;
}
 
int findFirst (const string a[], int n, string target) {
    if (n<0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}
 
bool findFirstSequence (const string a[], int n, string target, int &begin, int &end) {
    if (n < 0 || begin < 0 || end < 0) {
        return -1;
    }
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
    if (n < 0) {
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
    if (n < 0 || pos < 0) {
        return -1;
    }
    string pop = a[pos];
    for (int i = pos; i < (n-1); i++) {
        a[i] = a[i+1];
    }
    a[n-1] = pop;
    return pos;
}
 
int moveToBeginning(string a[], int n, int pos) {
    if (n < 0 || pos < 0) {
        return -1;
    }
    string pop = a[pos];
    for (int i = pos; i > 0; i--) {
        a[i] = a[i-1];
    }
    a[0] = pop;
    return pos;
}
 
int disagree(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    int match = -1;
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
    if (n < 0) {
        return -1;
    }
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
   return n-removed;
}
 
bool subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
   int substring_pos = 0;
   bool all_found = false;
   for (int i = 0; i < n1; i++) {
       if (a1[i] == a2[substring_pos] && substring_pos < (n2-1)) {
           substring_pos++;
       }
       else if (a1[i] == a2[substring_pos] && substring_pos == (n2-1)) {
           all_found = true;
       } else {}
   }
    return all_found;
}
 
int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
    if (n1 < 0 || n2 < 0 || max < 0) {
        return -1;
    }
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
    if (n < 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        moveToEnd(a, n, positionOfMin(a, n-i)); //tricky, huh? decreases the scope the function's looking at with each iteration. ends up sorting everything alphabetically.
    }
    for (int i = 0; i < n; i++) {
        if (a[i] >= divider) {
            return i;
        }
    }
    return -1; //error with the function if we reach here
}
 
int main() {
        string h[7] = { "peter", "lois", "meg", "chris", "", "stewie", "meg" };
	    assert(tally(h, 7, "meg") == 2);
	    assert(tally(h, 7, "") == 1);
	    assert(tally(h, 7, "quagmire") == 0);
	    assert(tally(h, 0, "meg") == 0);
	    assert(findFirst(h, 7, "meg") == 2);
	    assert(findFirst(h, 2, "meg") == -1);
	    int bg;
	    int en;
	    assert(findFirstSequence(h, 7, "chris", bg, en) && bg == 3 && en == 3);

	    string g[4] = { "peter", "lois", "chris", "stewie" };
	    assert(positionOfMin(g, 4) == 2);
	    assert(disagree(h, 4, g, 4) == 2);
	    assert(subsequence(h, 7, g, 4));
	    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "lois");
	
	    string f[4] = { "chris", "stewie", "meg", "lois" };
	    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "meg" && f[2] == "stewie");
	
	    string e[5] = { "chris", "chris", "chris", "meg", "meg" };
	    assert(removeDups(e, 5) == 2 && e[1] == "meg");
	
	    string x[4] = { "brian", "lois", "lois", "quagmire" };
	    string y[4] = { "chris", "lois", "meg", "stewie" };
	    string z[10];
	    assert(mingle(x, 4, y, 4, z, 10) == 8 && z[5] == "meg");
	
	    assert(divide(h, 7, "meg") == 3);
	
	    cout << "All tests succeeded" << endl;
}