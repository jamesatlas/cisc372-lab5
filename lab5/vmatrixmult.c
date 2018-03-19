#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * Prints a vector without decimal places...
 */
void print_vector(int n, double vector[]) {
    int i;
    printf("[%.0f", vector[0]);
    for (i = 1; i < n; i++) {
        printf(", %.0f", vector[i]);
    }
    printf("]\n");
}

/**
 * Prints a matrix without decimal places...
 */
void print_matrix(int n, double matrix[]) {
    int i;
    for (i = 0; i < n; i++) {
        print_vector(n, matrix+n*i);
    }
}

/**
 * reference implementation that does the computation in sequence by row
 */
void test_correctness(int n, double matrix[], double vector[], double result[]) {
    double * test = (double*)malloc(sizeof(double)*n);
    int i, j;
    double sum;
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum += vector[j] * matrix[i*n+j];
        }
        test[i] = sum;
    }

    // now see if there is a difference in results
    int differences = 0;
    for (i = 0; i < n; i++) {
        if (result[i] != test[i]) {
            differences++;
        }
    }
    if (differences>0) {
        printf("Correctness test found %d differences.\n", differences);
        printf("Vector:\n");
        print_vector(n, vector);
        printf("Matrix:\n");
        print_matrix(n, matrix);
        printf("Incorrect Result:\n");
        print_vector(n, result);
        printf("Test Reference Result:\n");
        print_vector(n, test);
    }

    free(test);
}

/**
 * Initially the same as the reference implementation. You will parallelize this
 * version.
 */
void matrix_vector_multiply_by_row(int threadcount, int n, double matrix[],
  double vector[], double result[]) {
    int i, j;
    double sum;
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum += vector[j] * matrix[i*n+j];
        }
        result[i] = sum;
    }
}

/**
 * Initialize random matrix and input vector values
 */
void init_random_matrix(int n, double matrix[], double vector[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        vector[i] = rand() % n;
        for (j = 0; j < n; j++) {
            matrix[i*n+j]=rand() % n;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        // () means optional
        printf("usage: %s n (threads) (seed)\n", argv[0]);
        return;
    }
    int n = atoi(argv[1]);
    int n_sq = n*n;
    int seed = 0;
    int threadcount = 1;
    if (argc >= 3) {
        threadcount = atoi(argv[2]);
    }
    if (argc >= 4) {
        seed = atoi(argv[3]);
    }
    srand(seed);

    double *matrix = (double*)malloc(sizeof(double)*n*n);
    double *vector = (double*)malloc(sizeof(double)*n);
    double *result = (double*)malloc(sizeof(double)*n);
    init_random_matrix(n, matrix, vector);

    // print the matrix and vector
    //    printf("Vector:\n");
    //    print_vector(n, vector);
    //    printf("Matrix:\n");
    //    print_matrix(n, matrix);

    double t_start = omp_get_wtime();
    matrix_vector_multiply_by_row(threadcount, n, matrix, vector, result);
    double t_end = omp_get_wtime();
    printf("Computed matrix-vector multiplication result in %f seconds\n",
           (t_end-t_start));

    //    printf("Result:\n");
    //    print_vector(n, result);

    // always test for correctness if matrix size is small
    if (n <= 100) {
        test_correctness(n, matrix, vector, result);
    }

    free(matrix);
    free(vector);
    free(result);
    return 0;
}
