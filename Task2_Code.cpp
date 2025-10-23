#include <iostream>
using namespace std;

long long moveCount = 0;

void rHanoi(int n, char source, char aux, char dest) {
    if (n == 0) {
        return; // this is the base case if no disks then do nothing
    }

    rHanoi(n - 1, source, aux, dest); // n-1 disks from source to destination
    // biggest disk from source to auxiliary
    cout << "Move disk " << n << " from " << source << " to " << aux << endl;
    moveCount++; // count increment

    rHanoi(n - 1, dest, aux, source); // n-1 disks from destination to source
    // biggest disk from auxiliary to destination
    cout << "Move disk " << n << " from " << aux << " to " << dest << endl;
    moveCount++; // count increment

    rHanoi(n - 1, source, aux, dest); // n-1 disks from source to destination again
}

int main() {
    int n;
    cout << "-- Restricted Hanoi Algorithm --\n";
    cout << "Input number of desired disks: ";
    cin >> n;

    rHanoi(n, 'A', 'B', 'C'); // disks, source, auxiliary, destination

    cout << "\nTotal moves: " << moveCount << endl;
    return 0;
}
