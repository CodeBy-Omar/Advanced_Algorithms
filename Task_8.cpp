#include <iostream>  
#include <pthread.h> 
#include <cstdlib>   

// Constants for matrix dimensions
const int rowsA = 3;  // Number of rows in matrix A
const int colsA = 4;  // Number of columns in matrix A (and rows in matrix B)
const int colsB = 3;  // Number of columns in matrix B

// Matrix definitions using static storage
int matA[rowsA][colsA] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };  // Initial values for matrix A
int matB[colsA][colsB] = { {16, 12, 8}, {15, 11, 7}, {14, 10, 6}, {13, 9, 5} };  // Initial values for matrix B
int matC[rowsA][colsB] = { 0 };  // Result matrix, initialized to zero

// Struct to hold thread data
struct ThreadData {
    int row;  // Stores the specific row index each thread will process
};

// Thread function to multiply one row of matA with matB
// The void* pointer is used in pthreads as a way to pass any type of data to threads. It is a generic pointer type that can point to any data type
// The pthread_create() function is designed to be extremely flexible and capable of running any function, regardless of the data it needs.
//  By accepting a void* for the thread function's parameter, it allows me to pass any type of data to the thread.
void* multi(void* arg) {
    ThreadData* data = (ThreadData*)arg;  // Cast void* back to ThreadData* to access the row data, so we are casting the arg back to the datatype we want
    int row = data->row;  // Extract the row index from the struct

    // Iterate over each column of matB
    for (int j = 0; j < colsB; j++) {
        matC[row][j] = 0;  // Initialize the result cell to zero
        // Perform the dot product of the row from matA and column from matB
        for (int k = 0; k < colsA; k++) {
            matC[row][j] += matA[row][k] * matB[k][j];
        }
    }
    return NULL;  // Return NULL as required by the pthreads function signature
}

int main() {
    pthread_t threads[rowsA];  // Array to store thread identifiers
    ThreadData threadData[rowsA];  // Array of struct to hold data for each thread

    // Create one thread for each row of matrix A
    for (int i = 0; i < rowsA; i++) {
        threadData[i].row = i;  // Set the row index for each struct
        pthread_create(&threads[i], NULL, multi, (void*)&threadData[i]);  // Start a new thread
    }

    // Wait for all threads to finish
    for (int i = 0; i < rowsA; i++) {
        pthread_join(threads[i], NULL);  // Block until thread[i] completes
    }

    // Output the matrices and the result
    std::cout << "Matrix A:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            std::cout << matA[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < colsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matB[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult Matrix:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matC[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
