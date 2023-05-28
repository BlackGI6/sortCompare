#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;


void mergeSortWrapper(int arr[], int n);
void quickSortWrapper(int arr[], int n); //! vezi comm implementare mai jos
void heapSort(int arr[], int n);
void radixSort(int arr[], int n);

// Funcția care sortează un set de date folosind funcția de sortare specificată ca parametru
void sortData(int arr[], int n, void (*sortFunc)(int[], int)){
    sortFunc(arr, n);
}

// Funcția care măsoară timpul de executare pentru un set de date și afișează rezultatul
void measureExecutionTime(int arr[], int n, void (*sortFunc)(int[], int), const string& sortName) {
    auto start = high_resolution_clock::now();

    sortData(arr, n, sortFunc);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Timpul de executare pentru " << sortName << ": " << duration.count() << " microsecunde" << endl;
}

// Implementarea Merge Sort
// Sursa: "Introduction to Algorithms" de Thomas H. Cormen et al.

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

// Implementarea Heap Sort
// Sursa: "Introduction to Algorithms" de Thomas H. Cormen et al.

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Implementarea Quick Sort
// Sursa: "Introduction to Algorithms" de Thomas H. Cormen et al.

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Implementarea Radix Sort
// Sursa: "Introduction to Algorithms" de Thomas H. Cormen et al.
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
void countSort(int arr[], int n, int exp)
{
    int output[n];
    int i, count[10] = { 0 };
 
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
void radixSort(int arr[], int n)
{
    int m = getMax(arr, n);
 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}



/*
 Am adaugat cele 2 functii wrapper de mai jos pt a adapta
 mergeSort si quickSort la semnatura de parametrii necesara pt.
 measureExecutionTime.
 */
void mergedSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n-1);
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n-1);
}

// Funcția pentru generarea unui set de date ordonat
void generateSortedData(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
}

// Funcția pentru generarea unui set de date dezordonat complet
void generateRandomData(int arr[], int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; i++) {
        arr[i] = std::rand() % 100;
    }
}

// Funcția pentru generarea unui set de date parțial ordonat
void generatePartiallySortedData(int arr[], int n) {
    generateSortedData(arr, n);

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> distribution(0, n - 1);

    for (int i = 0; i < n / 10; i++) {
        int index1 = distribution(generator);
        int index2 = distribution(generator);

        swap(arr[index1], arr[index2]);
    }
}

// Funcția pentru generarea unui set de date cu valori duplicate
void generateDuplicateData(int arr[], int n) {
    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> distribution(1, n / 10);

    for (int i = 0; i < n; i++) {
        arr[i] = distribution(generator);
    }
}

int main() {
    const int n = 1000; // Numărul de elemente în setul de date

    // Setul de date ordonat
    int sortedData[n];
    generateSortedData(sortedData, n);
    measureExecutionTime(sortedData, n, mergedSortWrapper, "Merge Sort");
    measureExecutionTime(sortedData, n, heapSort, "Heap Sort");
    measureExecutionTime(sortedData, n, quickSortWrapper, "Quick Sort");
    measureExecutionTime(sortedData, n, radixSort, "Radix Sort");

    // Setul de date dezordonat complet
    int randomData[n];
    generateRandomData(randomData, n);
    measureExecutionTime(randomData, n, mergedSortWrapper, "Merge Sort");
    measureExecutionTime(randomData, n, heapSort, "Heap Sort");
    measureExecutionTime(randomData, n, quickSortWrapper, "Quick Sort");
    measureExecutionTime(randomData, n, radixSort, "Radix Sort");

    // Setul de date parțial ordonat
    int partiallySortedData[n];
    generatePartiallySortedData(partiallySortedData, n);
    measureExecutionTime(partiallySortedData, n, mergedSortWrapper, "Merge Sort");
    measureExecutionTime(partiallySortedData, n, heapSort, "Heap Sort");
    measureExecutionTime(partiallySortedData, n, quickSortWrapper, "Quick Sort");
    measureExecutionTime(partiallySortedData, n, radixSort, "Radix Sort");

    // Setul de date cu valori duplicate
    int duplicateData[n];
    generateDuplicateData(duplicateData, n);
    measureExecutionTime(duplicateData, n, mergedSortWrapper, "Merge Sort");
    measureExecutionTime(duplicateData, n, heapSort, "Heap Sort");
    measureExecutionTime(duplicateData, n, quickSortWrapper, "Quick Sort");
    measureExecutionTime(duplicateData, n, radixSort, "Radix Sort");

    return 0;
}
