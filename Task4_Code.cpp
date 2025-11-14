#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool is_anagram(string a, string b) {
    if (a.length() != b.length())
        return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int main() {
    string w1, w2;

    cout << "< ANAGRAM CHECKER >" << endl;

    cout << "Input word one:";
    cin >> w1;
    cout << "Input word two:";
    cin >> w2;

    cout << endl << "< RESULTS >" << endl;
    if (is_anagram(w1, w2) == 1) {
        cout << "Words ARE anagrams." << endl;
    } else {
        cout << "Words AREN'T anagrams." << endl;
    }
}
