#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void disksort(vector<char>& disk) {
	int movecount = 0;
	bool swapbool = true;
	int size = disk.size();

	while (swapbool == true) {
		swapbool = false;
		
		for (int i = 0; i < size - 1; i++) {
			if (disk[i] == 'D' and disk[i + 1] == 'L') {
				swap(disk[i], disk[i + 1]);
				movecount++;
				swapbool = true;
			}
		}
	}
	cout << "Total moves taken: " << movecount << endl;
}

void printdisks(vector<char>& disks) {
	for (char c : disks) {
		cout << c << " ";
	}
	cout << endl;
}

int main() {
	int n;
	vector<char> disk;

	cout << "Alternating Disk Sort" << endl;
	cout << endl << "Enter amount for 2n disks:";
	cin >> n;

	// For the D,L,D,L order:
	for (int i = 0; i < n; i++) {
		disk.push_back('D');
		disk.push_back('L');
	}

	cout << "Initial state: " << endl;
	printdisks(disk);

	cout << "Goal state: " << endl;
	disksort(disk);
	printdisks(disk);
}