// Fake Coin Finder Algorithm
// 
// USING O(1) TIME COMPLEXITY
// N = 3; PREDEFINED

#include <iostream>
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
	int coin1 = 9;
	int coin2 = 11;
	int coin3 = 9;

	cout << "Fake Coin Finder O(1)" << endl;
	cout << endl << "Coin Weights:" << endl << "Coin 1 : " << coin1 << " grams (g)" << endl << "Coin 2 : " << coin2 << " grams (g)" << endl << "Coin 3 : " << coin3 << " grams (g)" << endl << endl;

	int c1_2result = balancescale(coin1, coin2);
	int c1_3result = balancescale(coin1, coin3);

	if (c1_2result == 0) {
		if (c1_3result == -1) {
			cout << "Coin 3 is the fake coin, it is heavier than the rest." << endl;
		}
		else if (c1_3result == 1) {
			cout << "Coin 3 is the fake coin, it is lighter than the rest." << endl;
		}
		else {
			cout << "There are no fake coins, all the coins are equal." << endl; //Unexpected Handler
		}
	}

	else if (c1_2result == 1) {
		if (c1_3result == 0) {
			cout << "Coin 2 is the fake coin, it is lighter than the rest." << endl;
		}
		else {
			cout << "Coin 1 is the fake coin, it is heavier than the rest." << endl;
		}
	}

	else if (c1_2result == -1) {
		if (c1_3result == 0) {
			cout << "Coin 2 is the fake coin, it is heavier than the rest." << endl;
		}
		else {
			cout << "Coin 1 is the fake coin, it is lighter than the rest." << endl;
		}
	}
}