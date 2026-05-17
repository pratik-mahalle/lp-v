#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Print Array
void printArray(vector<int>& arr) {

    for (int i = 0; i < arr.size(); i++) {

        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n), arr2(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];

        arr2[i] = arr[i];
    }

    // Sequential Bubble Sort Timing
    double start1 = omp_get_wtime();

    sequentialBubbleSort(arr);

    double end1 = omp_get_wtime();

    // Parallel Bubble Sort Timing
    double start2 = omp_get_wtime();

    parallelBubbleSort(arr2);

    double end2 = omp_get_wtime();

    cout << "\nSequential Bubble Sort:\n";

    printArray(arr);

    cout << "Sequential Execution Time: "
         << end1 - start1 << " seconds\n";

    cout << "\nParallel Bubble Sort:\n";

    printArray(arr2);

    cout << "Parallel Execution Time: "
         << end2 - start2 << " seconds\n";

    return 0;
}


