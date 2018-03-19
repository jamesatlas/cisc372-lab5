#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
int is_prime(int num) {
     if (num <= 1) return 0;
     if (num % 2 == 0 && num > 2) return 0;
     int end = sqrt(num);
     int i;
     for(i = 3; i <= end; i+= 2) {
         if (num % i == 0)
             return 0;
     }
     return 1;
}

int count_primes_seq(int start, int end) {
    int i;
    int count = 0;
    for (i = start; i <= end; i++) {
        count += is_prime(i);
    }
    return count;
}

void test_correctness(int start, int end, int result) {
    int actualCount = count_primes_seq(start, end);
    if (actualCount != result) {
        printf("Correctness test found %d primes and incorrect result found %d primes.\n", actualCount, result);
    }
}

int count_primes(int start, int end, int threadcount) {
  int i;
  int count = 0;
  for (i = start; i <= end; i++) {
    count += is_prime(i);
  }
  return count;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        // () means optional
        printf("usage: %s start end (threads)\n", argv[0]);
        return;
    }
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int threadcount = 1;
    if (argc >= 4) {
        threadcount = atoi(argv[3]);
    }

    double t_start = omp_get_wtime();
    int count = count_primes(start, end, threadcount);
    double t_end = omp_get_wtime();
    printf("Found %d primes between %d and %d in %f seconds\n", count, start, end,
           (t_end-t_start));

    // always test for correctness if end is small
    if (end < 1000) {
        test_correctness(start, end, count);
    }

    return 0;
}
