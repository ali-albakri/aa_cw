//Fake Coin Finder Algorithm
//
// USING O(N) TIME COMPLEXITY
// N IS NOT PREDEFINED; IT IS USER INPUT


#include <iostream>
#include <vector>
using namespace std;

int balancescale(int leftcoin, int rightcoin) {
	if (leftcoin == rightcoin) {
		return 0;
	}
	if (leftcoin > rightcoin) {
		return 1;
	}
	if (leftcoin < rightcoin) {
		return -1;
	}
}

int main() {
	cout << "Fake Coin Finder O(N)" << endl;

	int n;
	int genuineweight;
	int fakecoinindex;
	int fakecoinweight;

	cout << "Enter number of coins (has to be greater than 2): ";
	cin >> n;

	//Error Handling 1: Coins > 2
	if (n <= 2) {
		cout << "ERROR: Number of coins has to be greater than 2." << endl;
		return 0;
	}

	cout << "Enter the weight (g) for all genuine coins: ";
	cin >> genuineweight;

	cout << "From (1 to " << n << ") Choose the fake coin: ";
	cin >> fakecoinindex;

	// Error Handling 2: Fake Coin Selection Out of Bounds
	if (fakecoinindex < 1 or fakecoinindex > n) {
		cout << "ERROR: Index out of bounds." << endl;
		return 0;
	}

	cout << "How much does the fake coin weigh? (Has to be lighter or heavier): ";
	cin >> fakecoinweight;

	// Error Handling 3: Fake Coin equals same weight as Genuine Coin
	if (fakecoinweight == genuineweight) {
		cout << "ERROR: Fake coin weight cannot be equal to genuine coin weight." << endl;
		return 0;
	}

	vector<int> coins(n, genuineweight);
	coins[fakecoinindex-1] = fakecoinweight;

	cout << endl << "- Coin Weights -" << endl;
	for (int i = 0; i < n; i++) {
		cout << "Coin " << (i + 1) << " : " << coins[i] << " grams (g)" << endl;
	}
	cout << endl;

	int scaleresults;
	int referenceCoin = coins[0];
	int detectedFakeindex = -1; 

	for (int i = 1; i < n; i++) {
		scaleresults = balancescale(coins[i], referenceCoin);
		if (scaleresults != 0) {
			detectedFakeindex = i; //stores fake coin index
			break;
		}
	}

	//if referenceCoin was the fake coin
	if (detectedFakeindex == -1) {
		detectedFakeindex = 0;
		scaleresults = balancescale(coins[0], coins[1]);
	}

	//Error Handling 4: No fake coin spotted
	if (scaleresults == 0) {
		cout << "ERROR: No fake coins were spotted." << endl;
		return 0;
	}

	cout << endl << "The fake coin was detected!" << endl;
	if (scaleresults < 0) {
		cout << "Coin " << (detectedFakeindex + 1) << " is lighter than the genuine coins." << endl;
	}
	else {
		cout << "Coin " << (detectedFakeindex + 1) << " is heavier than the genuine coins." << endl;
	}

}