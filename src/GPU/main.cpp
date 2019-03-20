#include <iostream>
#include <random>
#include <time.h>
#define N (2048*2048)
#define THREADS_PER_BLOCK 512

void add(int *a, int *b, int *c, int size){
	for(int i = 0; i < size; i++){
		c[i] = a[i] + b[i];
	}
}

void random_ints(int* b, int size){
        for(int i = 0; i < size; i++){
                b[i] = rand();
        }
}

int main(){
	
        int *a, *b, *c;

        int size = N * sizeof(int);

        a = (int *)malloc(size); random_ints(a, N);
        b = (int *)malloc(size); random_ints(b, N);
        c = (int *)malloc(size);
	
	clock_t tStart = clock();
	add(a, b, c, N);
	printf("Time Taken: %.2f\n", (double)(clock() - tStart));

        free(a);
        free(b);
        free(c);

        return 0;


}

