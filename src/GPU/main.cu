#include <iostream>
#include <random>
#include <time.h>
#define N (2048*2048)
#define THREADS_PER_BLOCK 512


__global__ void add(int *a, int *b, int *c){
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	c[index] = a[index] + b[index];
}

void random_ints(int* b, int size){
	for(int i = 0; i < size; i++){
		b[i] = rand();
	}
}

int main(){
	clock_t tStart = clock();
	int *a, *b, *c;
	int *_a, *_b, *_c;
	
	int size = N * sizeof(int);
	tStart = clock();
	cudaMalloc((void **) &_a, size);
	cudaMalloc((void **) &_b, size);
	cudaMalloc((void **) &_c, size);
	
	printf("allocating mem device: %.2f\n", (double)(clock() - tStart));
	
	tStart = clock();
	
	a = (int *)malloc(size); random_ints(a, N);
	b = (int *)malloc(size); random_ints(b, N);
	c = (int *)malloc(size); 
	
        printf("allocating mem host: %.2f\n", (double)(clock() - tStart));
	
	tStart = clock();


	cudaMemcpy(_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(_b, b, size, cudaMemcpyHostToDevice);

	printf("allocating mem to host: %.2f\n", (double)(clock() - tStart));
	tStart = clock();


	add<<<N/THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(_a, _b, _c);
        printf("execution: %.2f\n", (double)(clock() - tStart));

	tStart = clock();
	

	cudaMemcpy(c, _c, size, cudaMemcpyDeviceToHost);
        printf("allocating mem back to host: %.2f\n", (double)(clock() - tStart));

	
	free(a);
	free(b);
	free(c);
	cudaFree(_a);
	cudaFree(_b);
	cudaFree(_c);
	
	return 0;


}
