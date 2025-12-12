#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <cctype> 
using namespace std;
using namespace std::chrono;

// data type for item each must have name and price
struct item {
    string name;
    int price;
};

// comparison for item i and i+1 prices
bool compareItems(const item& item1, const item& item2) {
    return item1.price < item2.price;
}


// greedy algorithm implementation
vector<item> greedyknapsack(vector<item> list, int budget) {
    
    // sorting items from cheapest to expensive
    sort(list.begin(), list.end(), compareItems);

    vector<item> selected;
    int total = 0;

    for (int i = 0; i < list.size(); i++) {
        item current = list[i];  // gets the current item
        if (total + current.price <= budget) {
            selected.push_back(current);  // add to shopping bag
            total += current.price;     // updates total spent
        }
    }

    return selected;
}

// dynamic programming knapsack
vector<item> dynamicknapsack(vector<item>& list, int budget) {
    int size = list.size();

    vector<vector<int>> dp;

    for (int i = 0; i <= size; i++) {
        vector<int> row;
        for (int j = 0; j <= budget; j++) { //columns
            row.push_back(0);
        }
        dp.push_back(row);
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 0; j <= budget; j++) {
            if (list[i - 1].price <= j) {
                // take or skip item
                dp[i][j] = max(
                    1 + dp[i - 1][j - list[i - 1].price], dp[i - 1][j]
                );

            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // backtracking
    vector<item> selected;
    int j = budget;

    for (int i = size; i > 0; i--) {
        if (dp[i][j] != dp[i - 1][j]) {
            item current = list[i - 1];
            selected.push_back(current);
            j -= current.price; 
        }
    }
    return selected;
}

int main() {
    cout << "- Shopping Optimizer - " << endl;
    
    // ensures budget is greater than 0 and is a positive integer.
    int budget;

    while (true) {
        cout << "Enter your shopping budget: " << endl;
        string budgetstr;
        getline(cin, budgetstr);
        try {
            budget = stoi(budgetstr);
            if (budget <= 0) {
                cout << "Budget must be greater than 0." << endl;
                continue;
            }
            cout << "Budget Confirmed: " << budget << " EGP" << endl;
            break;
        }
        catch (...) {
            cout << "Error: Must be a positive number." << endl;
        }
    }

    vector<item> list;
    cout << "Welcome User!" << endl << "Start by entering the items you like. Type 'confirm' to end the process!" << endl;

    // Item Name Retrieval
    while (true) {
        string itemname;
        cout << endl << "Item Name: ";
        getline(cin, itemname);

        if (itemname == "") {
            cout << "Please enter a valid name for the item." << endl;
            continue;
        }

        string lowercasename = itemname;
        for (int i = 0; i < lowercasename.size(); i++) {
            lowercasename[i] = tolower(lowercasename[i]);
        }
        // Case Break: confirm (not case sensitive)
        if (lowercasename == "confirm") {
            break;
        }

        // Item Price Retrieval
        int itemprice;
        while (true) {
            cout << "Item Price: ";
            string pricestr;
            getline(cin, pricestr);
            try {
                itemprice = stoi(pricestr);
                if (itemprice <= 0) {
                    cout << "Price must be greater than 0." << endl;
                    continue;
                }
                break;
            }
            catch (...) {
                cout << "Error: Must be a positive number." << endl;
            }
        }
        
        list.push_back({ itemname, itemprice });

    }

    // recording times for both greedy and dynamic.
    auto greedystart = high_resolution_clock::now();
    vector<item> greedy = greedyknapsack(list, budget);
    auto greedyend = high_resolution_clock::now();
    auto greedytime = duration_cast<microseconds>(greedyend - greedystart).count();

    auto dynamicstart = high_resolution_clock::now();
    vector<item> dynamic = dynamicknapsack(list, budget);
    auto dynamicend = high_resolution_clock::now();
    auto dynamictime = duration_cast<microseconds>(dynamicend - dynamicstart).count();

    // calculating and outputting results
    cout << endl << "- Results -" << endl;

    cout << "Greedy Knapsack Results: " << endl;
    int totalgreedy = 0;

    for (int i = 0; i < greedy.size(); i++) {
        item current = greedy[i];
        cout << current.name << " - " << current.price << " EGP" << endl;
        totalgreedy += current.price;
    }
    cout << "Total Cost: " << totalgreedy << " EGP" << endl;
    cout << "Remaining Budget: " << (budget - totalgreedy) << " EGP" << endl;
    cout << "Time Elapsed: " << greedytime << " microseconds" << endl;
    cout << "Time Complexity: O(n log n)" << endl;


    cout << endl << "Dynamic Programming Knapsack Results: " << endl;
    int totaldynamic = 0;
    for (int i = 0; i < dynamic.size(); i++) {
        item current = dynamic[i];
        cout << current.name << " - " << current.price << " EGP" << endl;
        totaldynamic += current.price;
    }

    cout << "Total Cost: " << totaldynamic << " EGP" << endl;
    cout << "Remaining Budget: " << (budget - totaldynamic) << " EGP" << endl;
    cout << "Time Elapsed: " << dynamictime << " microseconds" << endl;
    cout << "Time Complexity: O(n * " << budget << ")" << endl;
}