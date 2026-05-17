#include <iostream>
#include <vector>
#include <omp.h>
#include <limits.h>

using namespace std;

// Min Reduction Function
void Min_Reduction(vector<int>& arr) {

    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < arr.size(); i++) {

        if (arr[i] < min_value) {

            min_value = arr[i];
        }
    }

    cout << "\nMinimum Value = " << min_value << endl;
}

// Max Reduction Function
void Max_Reduction(vector<int>& arr) {

    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < arr.size(); i++) {

        if (arr[i] > max_value) {

            max_value = arr[i];
        }
    }

    cout << "Maximum Value = " << max_value << endl;
}

// Sum Reduction Function
void Sum_Reduction(vector<int>& arr) {

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];
    }

    cout << "Sum = " << sum << endl;
}

// Average Reduction Function
void Average_Reduction(vector<int>& arr) {

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];
    }

    double average = (double)sum / arr.size();

    cout << "Average = " << average << endl;
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    Min_Reduction(arr);

    Max_Reduction(arr);


    Sum_Reduction(arr);

    Average_Reduction(arr);

    return 0;
}

