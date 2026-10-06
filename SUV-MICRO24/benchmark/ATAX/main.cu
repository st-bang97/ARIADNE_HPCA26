/**
 * atax.cu: This file is part of the PolyBench/GPU 1.0 test suite.
 *
 *
 * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <cuda.h>

#include "penguin.h"

#include "../common/polybenchUtilFuncts.h"

//define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.5

#define MiB 21212
#define RESERVATION ((MiB*1024ULL*1024))

#define GPU_DEVICE 0

/* Problem size. */
#define NX 256 * 128
#define NY 256 * 128

/* Thread block dimensions */
#define DIM_THREAD_BLOCK_X 256
#define DIM_THREAD_BLOCK_Y 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *x_gpu, DATA_TYPE *A_gpu)
{
	long long int i, j;

	for (i = 0; i < NX; i++)
	{
		x_gpu[i] = i * M_PI;
		for (j = 0; j < NY; j++)
		{
			A_gpu[i*NY + j] = ((DATA_TYPE) i*(j)) / NX;
		}
	}
}


void init_array(DATA_TYPE *x, DATA_TYPE *A, DATA_TYPE *x_gpu, DATA_TYPE *A_gpu)
{
	long long int i, j;

	for (i = 0; i < NX; i++)
	{
		x[i] = i * M_PI;
		x_gpu[i] = i * M_PI;
		for (j = 0; j < NY; j++)
		{
			A[i*NY + j] = ((DATA_TYPE) i*(j)) / NX;
			A_gpu[i*NY + j] = ((DATA_TYPE) i*(j)) / NX;
		}
	}
}

void printResults(DATA_TYPE *z)
{
	long long int i;

	for (i=0; i<NY; i++)
	{
        	printf("%lf\n", z[i]);
	}
}


void compareResults(DATA_TYPE *z, DATA_TYPE *z_outputFromGpu)
{
	long long int i, fail;

	fail = 0;

	for (i=0; i<NY; i++)
	{
		if (percentDiff(z[i], z_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD)
		{
			fail++;		           
			//printf("%f, %f\n", z[i], z_outputFromGpu[i]);
		}
	}
	
	// print results
	printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}


void GPU_argv_init()
{
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, GPU_DEVICE);
	printf("setting device %d with name %s\n",GPU_DEVICE,deviceProp.name);
	cudaSetDevice( GPU_DEVICE );
}


__global__ void atax_kernel1(DATA_TYPE *A, DATA_TYPE *x, DATA_TYPE *tmp)
{
	long long int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i < NX)
	{
		long long int j;
		tmp[i] = 0;
		for(j=0; j < NY; j++)
		{
			tmp[i] += A[i * NY + j] * x[j];
		}
	}
}

__global__ void atax_kernel2(DATA_TYPE *A, DATA_TYPE *y, DATA_TYPE *tmp)
{
	long long int j = blockIdx.x * blockDim.x + threadIdx.x;
	
	if (j < NY)
	{
		y[j] = 0;
		long long int i;
		for(i=0; i < NX; i++)
		{
			y[j] += A[i * NY + j] * tmp[i];
		}
	}
}


void atax_cpu(DATA_TYPE* A, DATA_TYPE* x, DATA_TYPE* y, DATA_TYPE* tmp)
{
	long long int i,j;
	
	for (i= 0; i < NY; i++)
	{
    	y[i] = 0;
	}
  
	for (i = 0; i < NX; i++)
 	{
      	tmp[i] = 0;

      	for (j = 0; j < NY; j++)
		{
			tmp[i] = tmp[i] + A[i*NY + j] * x[j];
		}
		
      	for (j = 0; j < NY; j++)
		{
			y[j] = y[j] + A[i*NY + j] * tmp[i];
		}
    }
}


void ataxGpu(DATA_TYPE* A_gpu, DATA_TYPE* x_gpu, DATA_TYPE* y_gpu, DATA_TYPE* tmp_gpu)
{
	double t_start, t_end;

	
	dim3 block(DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y);
	dim3 grid1((size_t)(ceil( ((float)NX) / ((float)block.x) )), 1);
	dim3 grid2((size_t)(ceil( ((float)NY) / ((float)block.x) )), 1);

	t_start = rtclock();
	atax_kernel1<<< grid1, block >>>(A_gpu,x_gpu,tmp_gpu);
	cudaDeviceSynchronize();
	atax_kernel2<<< grid2, block >>>(A_gpu,y_gpu,tmp_gpu);
	cudaDeviceSynchronize();
	t_end = rtclock();
	printf("\nGPU Runtime: %0.6lfs\n", t_end - t_start);

}


int main(int argc, char** argv)
{
	double t_start, t_end;
	int* reservation;
        cudaMalloc((void**) &reservation, RESERVATION);

	DATA_TYPE* A;
	DATA_TYPE* x;
	DATA_TYPE* y;
	DATA_TYPE* tmp;

	DATA_TYPE *A_gpu;
	DATA_TYPE *x_gpu;
	DATA_TYPE *y_gpu;
	DATA_TYPE *tmp_gpu;

	// DATA_TYPE* tmp;
	A = (DATA_TYPE*)malloc((size_t)NX*NY*sizeof(DATA_TYPE));
	x = (DATA_TYPE*)malloc((size_t)NY*sizeof(DATA_TYPE));
	y = (DATA_TYPE*)malloc((size_t)NY*sizeof(DATA_TYPE));
	tmp = (DATA_TYPE*)malloc((size_t)NX*sizeof(DATA_TYPE));

	cudaMallocManaged(&A_gpu, (size_t)sizeof(DATA_TYPE) * NX * NY);
	cudaMallocManaged(&x_gpu, (size_t)sizeof(DATA_TYPE) * NY);
	cudaMallocManaged(&y_gpu, (size_t)sizeof(DATA_TYPE) * NY);
	cudaMallocManaged(&tmp_gpu, (size_t)sizeof(DATA_TYPE) * NX);


	init_array(x, A, x_gpu, A_gpu);

	GPU_argv_init();

	penguinStartStatCollection();
	nvml_start();
	ataxGpu(A_gpu, x_gpu, y_gpu, tmp_gpu);
	nvml_stop();
	penguinStopStatCollection();

	atax_cpu(A,x,y,tmp);
	compareResults(tmp, tmp_gpu);

        //printResults(tmp_gpu);
	free(A);
	free(x);
	free(y);
	free(tmp);

	cudaFree(A_gpu);
	cudaFree(x_gpu);
	cudaFree(y_gpu);
	cudaFree(tmp_gpu);
    
  	return 0;
}

