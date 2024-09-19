#include <stdio.h>
#include <stdlib.h>
#include <openblas/cblas.h>
#include <time.h>
#include <omp.h>
typedef struct {
    int rows;
    int columns;
    double* data;
} Matrix;

// Function to create a matrix
Matrix create_matrix(int rows, int columns) {
    Matrix mat;
    mat.rows = rows;
    mat.columns = columns;
    mat.data = (double*)malloc(rows * columns * sizeof(double));
    return mat;
}

// Function to free matrix memory
void free_matrix(Matrix* mat) {
    free(mat->data);
    mat->data = NULL;
}

Matrix randomMatrix(int rows, int columns) {
    Matrix mat;
    mat.rows = rows;
    mat.columns = columns;
    mat.data = (double*)malloc(rows * columns * sizeof(double));

    // Check if memory allocation was successful
    if (mat.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Fill the matrix with random float values
    #pragma omp parallel for
    for (int i = 0; i < rows * columns; i++) {
        mat.data[i] = (float)rand() / RAND_MAX;  // Random float between 0 and 1
    }

    return mat;
}

// Function to perform matrix multiplication using OpenBLAS
void multiply_matrices(const Matrix* A, const Matrix* B, Matrix* C) {
    if (A->columns != B->rows) {
        printf("Matrix dimensions do not match for multiplication!\n");
        return;
    }
    
    // Perform matrix multiplication C = A * B using OpenBLAS (cblas_dgemm)
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                A->rows, B->columns, A->columns,
                1.0, A->data, A->columns, B->data, B->columns, 
                0.0, C->data, C->columns);
}



int main() {
    clock_t begin= clock();
    Matrix mat = randomMatrix(10000,10000);

    // Print the random matrix
    // for (int i = 0; i < mat.rows; i++) {
    //     for (int j = 0; j < mat.columns; j++) {
    //         printf("%f ", mat.data[i * mat.columns + j]);
    //     }
    //     printf("\n");
    // }

    // Free the allocated memory
    free(mat.data);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f",time_spent);
    return 0;
}
