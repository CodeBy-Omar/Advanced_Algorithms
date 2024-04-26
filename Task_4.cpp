#include <iostream>
using namespace std;

// Function to partition the array around a pivot element
int partition(int arr[], int low, int high) {
    // Select the last element as the pivot
    int pivot = arr[high];
    // Initialize the index of the smaller element
    int i = (low - 1);
    // Iterate through the array from low to high
    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            // Increment the index of the smaller element
            i++;
            // Swap arr[i] and arr[j]
            swap(arr[i], arr[j]);
        }
    }
    // Swap arr[i + 1] and arr[high] which is th pivot element
    swap(arr[i + 1], arr[high]);
    // Return the partitioning index
    return (i + 1);
}

// Function to perform quicksort
void quickSort(int arr[], int low, int high, int target) {
    // Swap target with the last element
    int targetIndex = -1;
    for (int i = low; i <= high; i++) {
        if (arr[i] == target) {
            targetIndex = i;
            break;
        }
    }
    // making the target choosed as the pivot basically
    if (targetIndex != -1) {
        swap(arr[targetIndex], arr[high]);

        // Recursive calls to quickSort
        if (low < high) {
            // pi is partitioning index
            int pi = partition(arr, low, high);
            // Sort elements before partition and after partition
            quickSort(arr, low, pi - 1, target);
            quickSort(arr, pi + 1, high, target);
        }
    }

}

int main() {
    // Input array
    int arr[] = { 12, 4, 6, 7, 2, 5, 8, 9, 10, 99, 8, 64, 12, 12 };
    // Calculate the size of the array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Target element to find and move to pivot position
    int target = 64;

    // Check if target is not in the array
    bool targetFound = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            targetFound = true;
            break;
        }
    }

    if (!targetFound) {
        cout << "Target element not found in the array." << endl;
        return 0;
    }

    // Check if target is the smallest or largest element
    bool isSmallest = true, isLargest = true;
    for (int i = 0; i < n; i++) {
        if (arr[i] < target) {
            isSmallest = false;
        }
        if (arr[i] > target) {
            isLargest = false;
        }
    }

    // Display appropriate messages based on target position
    if (isSmallest || isLargest) {
        cout << "Please choose another target element." << endl;
        return 0;
    }

    // Call quickSort function with target element
    quickSort(arr, 0, n - 1, target);

    // Display the sorted array
    cout << "Sorted Array\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}

