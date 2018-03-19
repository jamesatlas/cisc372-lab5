#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * Prints a vector of int values...
 */
void print_vector(int n, int vector[]) {
    int i;
    printf("[%d", vector[0]);
    for (i = 1; i < n; i++) {
        printf(", %d", vector[i]);
    }
    printf("]\n");
}

void compute_histogram_seq(int n, int b, int vector[], int histogram[]) {
  int i;
  for(i = 0; i < b; i++) {
    histogram[i] = 0;
  }
  int range = RAND_MAX / b;
  for(i = 0; i < n; i++) {
    histogram[vector[i]/range]++;
  }
}

/**
 * reference implementation that does the computation in sequence
 */
void test_correctness(int n, int b, int vector[], int histogram[]) {
    int i;
    int * test = malloc(sizeof(int)*n);
    compute_histogram_seq(n, b, vector, test);

    // now see if there is a difference in results
    int differences = 0;
    for (i = 0; i < b; i++) {
        if (histogram[i] != test[i]) {
            differences++;
        }
    }
    if (differences>0) {
        printf("Correctness test found %d differences.\n", differences);
        printf("Vector:\n");
        print_vector(n, vector);
        printf("Incorrect Result:\n");
        print_vector(b, histogram);
        printf("Test Reference Result:\n");
        print_vector(b, test);
    }

    free(test);
}

void compute_histogram(int threadcount, int n, int b, int vector[], int histogram[]) {
  // note this is the same as the seq version as it was copied
  // you must edit this code to parallelize it correctly
  int i;
  for(i = 0; i < b; i++) {
    histogram[i] = 0;
  }
  int range = RAND_MAX / b;
  for(i = 0; i < n; i++) {
    histogram[vector[i]/range]++;
  }
}

/**
 * Initialize random matrix and input vector values
 */
void init_random_vector(int n, int vector[]) {
    int i;
    for (i = 0; i < n; i++) {
        vector[i] = rand();
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        // () means optional
        printf("usage: %s n buckets (threads) (seed)\n", argv[0]);
        return;
    }
    int n = atoi(argv[1]);
    int b = atoi(argv[2]);
    int n_sq = n*n;
    int seed = 0;
    int threadcount = 1;
    if (argc >= 4) {
        threadcount = atoi(argv[3]);
    }
    if (argc >= 5) {
        seed = atoi(argv[4]);
    }
    srand(seed);

    int *vector = malloc(sizeof(int)*n);
    int *histogram = malloc(sizeof(int)*b);
    init_random_vector(n, vector);

    double t_start = omp_get_wtime();
    compute_histogram(threadcount, n, b, vector, histogram);
    double t_end = omp_get_wtime();
    printf("Computed histogram result in %f seconds\n",
           (t_end-t_start));

    //    printf("Result histogram:\n");
    //    print_vector(b, histogram);

    // always test for correctness if vector size is small
    if (n <= 100) {
        test_correctness(n, b, vector, histogram);
    }

    free(vector);
    free(histogram);
    return 0;
}
