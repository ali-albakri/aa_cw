#include <iostream>
#include <iomanip> //for setprecision()
#include <string>
#include <ctime> //access to time()
#include <cstdlib> //random functions
#include <chrono> //measuring execution time with high_resolution_clock and so on..
#include <fstream> //file handling
using namespace std;
using namespace std::chrono;

int bubble_sort_count(int arr[], int n) {
    int compareCount = 0;
    int i, j;
    bool swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = false;

        for (j = 0; j < n - i - 1; j++) {
            compareCount++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }

    return compareCount;
}

int selection_sort_count(int arr[], int n) {
    int compareCount = 0;
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < n; j++) {
            compareCount++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }

    return compareCount;
}

int insertion_sort_count(int arr[], int n) {
    int compareCount = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            compareCount++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return compareCount;
}

void fill_random(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

void fill_sorted(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void fill_reverse(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void test_comparisons() {
    srand(time(0));
    ofstream file("results.csv"); // creates a file named results.csv
    file << "n,Array Type,Bubble Comparisons,Selection Comparisons,Insertion Comparisons,"
        "Bubble Time (ms),Selection Time (ms),Insertion Time (ms)\n";

    cout << fixed << setprecision(6); // show decimals (for example 0.002345)

    for (int n = 1; n <= 30; n++) {
        int arr[100], copy1[100], copy2[100], copy3[100];
        cout << "\n=== Array size: " << n << " ===\n";

        string types[3] = { "Random", "Sorted", "Reverse" };
        for (string type : types) {
            if (type == "Random") fill_random(arr, n);
            else if (type == "Sorted") fill_sorted(arr, n);
            else fill_reverse(arr, n);

            for (int i = 0; i < n; i++)
                copy1[i] = copy2[i] = copy3[i] = arr[i];

            // bubble sort
            auto start = high_resolution_clock::now(); //precise timestamp before the sort begins
            int bCount = bubble_sort_count(copy1, n);
            auto end = high_resolution_clock::now(); //another timestamp after sorting finishes.
            double bTime = duration<double, milli>(end - start).count();

            // selection sort
            start = high_resolution_clock::now();
            int sCount = selection_sort_count(copy2, n);
            end = high_resolution_clock::now();
            double sTime = duration<double, milli>(end - start).count();

            // insertion sort
            start = high_resolution_clock::now();
            int iCount = insertion_sort_count(copy3, n);
            end = high_resolution_clock::now();
            double iTime = duration<double, milli>(end - start).count();

            cout << "\nArray Type: " << type << "\n";
            cout << "Bubble Sort:    comparisons = " << bCount << ", time = " << bTime << " ms\n";
            cout << "Selection Sort: comparisons = " << sCount << ", time = " << sTime << " ms\n";
            cout << "Insertion Sort: comparisons = " << iCount << ", time = " << iTime << " ms\n";

            // also write to the CSV file
            file << n << "," << type << ","
                << bCount << "," << sCount << "," << iCount << ","
                << bTime << "," << sTime << "," << iTime << "\n";

        }
    }

    file.close();
    cout << "\nAll results saved to results.csv\n";

}

int main() {
    test_comparisons();
    return 0;
}