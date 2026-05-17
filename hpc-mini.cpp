#include <mpi.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

void quicksort(int arr[], int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quicksort(arr, left, j);

    if (i < right)
        quicksort(arr, i, right);
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 16;

    int data[N] = {45, 12, 89, 33, 21, 67, 90, 11,
                   56, 78, 34, 9, 1, 99, 54, 23};

    int local_n = N / size;

    int* local_data = new int[local_n];

    MPI_Scatter(data, local_n, MPI_INT,
                local_data, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    quicksort(local_data, 0, local_n - 1);

    int* gathered = nullptr;

    if (rank == 0) {
        gathered = new int[N];
    }

    MPI_Gather(local_data, local_n, MPI_INT,
               gathered, local_n, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {

        quicksort(gathered, 0, N - 1);

        cout << "Sorted Array: ";

        for (int i = 0; i < N; i++) {
            cout << gathered[i] << " ";
        }

        cout << endl;
    }

    delete[] local_data;

    MPI_Finalize();

    return 0;
}
