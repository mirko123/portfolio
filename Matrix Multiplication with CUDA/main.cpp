#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <cuda_runtime.h>

int	m = 16;
int	n = 16;
int	k = 16;

int _calc_dimm = 1; // c

int _block_x = 1; // v
int _block_y = 1; // w

int _thread_x = 1; // x
int _thread_y = 1; // y

int _dump_file = 0; // d
int _load_file = 0; // l
const char* _dump_file_name = "";
const char* _load_file_name = "";

int _dump_m3x_data = 0; // z

int _host_cpu = 0; // h
int _analiz_format = 0;
int _info = 0; // i
int _options = 0; // p

int _testCount = 100; //t
int _testStep = 1; //s

// directly from CUDA toolkit ...
inline int _ConvertSMVer2Cores(int major, int minor)
{
    // Defines for GPU Architecture types (using the SM version to determine the # of cores per SM
    typedef struct
    {
        int SM; // 0xMm (hexidecimal notation), M = SM Major version, and m = SM minor version
        int Cores;
    } sSMtoCores;

    sSMtoCores nGpuArchCoresPerSM[] = {

    	{ 0x10,  8 }, // Tesla Generation (SM 1.0) G80 class
        { 0x11,  8 }, // Tesla Generation (SM 1.1) G8x class
        { 0x12,  8 }, // Tesla Generation (SM 1.2) G9x class
        { 0x13,  8 }, // Tesla Generation (SM 1.3) GT200 class

        { 0x20, 32 }, // Fermi Generation (SM 2.0) GF100 class
        { 0x21, 48 }, // Fermi Generation (SM 2.1) GF10x class

        { 0x30, 192}, // Kepler Generation (SM 3.0) GK10x class
        { 0x32, 192}, // Kepler Generation (SM 3.2) GK10x class
        { 0x35, 192}, // Kepler Generation (SM 3.5) GK11x class
        { 0x37, 192}, // Kepler Generation (SM 3.7) GK21x class

        { 0x50, 128}, // Maxwell Generation (SM 5.0) GM10x class
        { 0x52, 128}, // Maxwell Generation (SM 5.2) GM20x class
        { 0x53, 128}, // Maxwell Generation (SM 5.3) GM20x class

        { 0x60, 64 }, // Pascal Generation (SM 6.0) GP100 class
        { 0x61, 128}, // Pascal Generation (SM 6.1) GP10x class
        { 0x62, 128}, // Pascal Generation (SM 6.2) GP10x class

        {   -1, -1 }
    };

    int index = 0;

    while (nGpuArchCoresPerSM[index].SM != -1)
    {
        if (nGpuArchCoresPerSM[index].SM == ((major << 4) + minor))
        {
            return nGpuArchCoresPerSM[index].Cores;
        }

        index++;
    }

    // If we don't find the values, we default use the previous one to run properly
    printf("MapSMtoCores for SM %d.%d is undefined.  Default to use %d Cores/SM\n", major, minor, nGpuArchCoresPerSM[index-1].Cores);
    return nGpuArchCoresPerSM[index-1].Cores;
}

void _process_cmd_line(int argc, char **argv) {
	int c = 0;

	while ((c = getopt (argc, argv, "m:n:k:c:v:w:x:y:o:i:t:s:zhadp")) != -1) {
		switch (c) {
			case 'm':
				m = atoi(optarg);
				break;
			case 'n':
				n = atoi(optarg);
				break;
			case 'k':
				k = atoi(optarg);
				break;
			case 'c':
				c = atoi(optarg);
				break;
			case 'x':
				_thread_x = atoi(optarg);
				break;
			case 'y':
				_thread_y = atoi(optarg);
				break;
			case 'v':
				_block_x = atoi(optarg);
				break;
			case 'w':
				_block_y = atoi(optarg);
				break;

			case 't':
				_testCount = atoi(optarg);
				break;
			case 's':
				_testStep = atoi(optarg);
				break;

			case 'o':
				_dump_file = 1; //o
				_dump_file_name = optarg;
				break;
			case 'i':
				_load_file = 1; //i
				_load_file_name = optarg;
				break;
			case 'z':
				_dump_m3x_data = 1;
				break;
			case 'd': //d
				_info = 1;
				break;
			case 'a': //d
				_analiz_format = 1;
				break;
			case 'h':
				_host_cpu = 1;
				break;
			case 'p':
				_options = 1;
				break;
			case '?':
				if (
					optopt == 'm' ||
					optopt == 'n' ||
					optopt == 'k' ||

					optopt == 'c' ||

					optopt == 'x' ||
					optopt == 'y' ||

					optopt == 'v' ||
					optopt == 'w' ||

					optopt == 'l' ||

					optopt == 't' ||
					optopt == 's' ||

					optopt == 'i'

				) {
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				}
				break;
			default:
				break;
		}
	}

	if(_options == 1){
		printf("[INFO] program run with the following parameters:\n");

		printf("[INFO] -m %d\n", m);
		printf("[INFO] -n %d\n", n);
		printf("[INFO] -k %d\n", k);

		printf("[INFO] -c %d (calculation dimension)\n", _calc_dimm);

		printf("[INFO] -v %d (block.x)\n", _block_x);
		printf("[INFO] -w %d (block.y)\n", _block_y);

		printf("[INFO] -x %d (thread.x)\n", _thread_x);
		printf("[INFO] -y %d (thread.y)\n", _thread_y);

		// printf("[INFO] -o %d (dump file)\n", _dump_file);
		// printf("[INFO] -i %d (load file)\n", _load_file);

		printf("[INFO] -o %d (dump file) %s\n", _dump_file, _dump_file_name);
		printf("[INFO] -i %d (load file) %s\n", _load_file, _load_file_name);
		printf("[INFO] -z %d (dump m3x data)\n", _dump_m3x_data);

		
		printf("[INFO] -t %d (count of test)\n", _testCount);
		printf("[INFO] -s %d (test step)\n", _testStep);
		printf("[INFO] -a %d (analiz format)\n", _analiz_format);

		printf("[INFO] -h %d (run on CPU)\n", _host_cpu);
		printf("[INFO] -d %d (device info)\n", _info);
		printf("[INFO] -p %d (print opt)\n\n", _options);
	}
}

void _identify_cuda_devices(void) {

	int deviceCount = 0;
	cudaError_t error_id = cudaGetDeviceCount(&deviceCount);

	if (error_id != cudaSuccess) {

		printf("[ERR] cudaGetDeviceCount returned %d\n-> %s\n", (int) error_id, cudaGetErrorString(error_id));
	    printf("[ERR] Result = FAIL\n");
	    exit(EXIT_FAILURE);

	}

	if (deviceCount == 0) {

	    printf("[INFO] Did not find any CUDA enabled devices! Exitting...\n");
	    exit(0);

	}

    printf("[INFO] Found %d CUDA enabled devices...\n", deviceCount);

	cudaDeviceProp deviceProp;

	for (int dev = 0; dev < deviceCount; dev++) {

		cudaSetDevice(dev);
		cudaGetDeviceProperties(&deviceProp, dev);

		printf("[INFO] Device #: %d\n", dev);
		printf("[INFO] Device name: '%s'\n", deviceProp.name);
	    printf("[INFO] CUDA Capability Major/Minor version: %d.%d\n", deviceProp.major, deviceProp.minor);
	    printf("[INFO] (%2d) Multiprocessors, with (%3d) CUDA Cores (SPs/Shader Units) per MP: %d Total CUDA Cores\n",
	    	deviceProp.multiProcessorCount,
	        _ConvertSMVer2Cores(deviceProp.major, deviceProp.minor),
	        _ConvertSMVer2Cores(deviceProp.major, deviceProp.minor) * deviceProp.multiProcessorCount
		);
	    printf("[INFO] Warp size: %d\n", deviceProp.warpSize);
	    printf("[INFO] Maximum number of threads per multiprocessor: %d\n", deviceProp.maxThreadsPerMultiProcessor);
	    printf("[INFO] Maximum number of threads per block: %d\n", deviceProp.maxThreadsPerBlock);
	    printf("[INFO] Max dimension size of a thread block (x,y,z): (%d, %d, %d)\n",
	    	deviceProp.maxThreadsDim[0],
	        deviceProp.maxThreadsDim[1],
	        deviceProp.maxThreadsDim[2]
		);
	    printf("[INFO] Max dimension size of a grid size (x,y,z): (%d, %d, %d)\n\n",
	    	deviceProp.maxGridSize[0],
	    	deviceProp.maxGridSize[1],
	    	deviceProp.maxGridSize[2]
		);

	}
}

float* _alloc_m3x(int _rows, int _cols) {
    float *p = (float *) malloc( _rows * _cols* sizeof(float) );
    return p;
}

void _free_m3x(float **p, int r, int c) {
    float *m = *p;
    free(m);
    *p = NULL;

}
void _init_m3x(float *p, int _rows, int _cols, int _val, int _use_val) {

    for(int r = 0; r < _rows; r++ )
        for (int c = 0; c < _cols; c++)
            p[c + r *_cols] = (_use_val == 1) ? _val : (float) (drand48() * 1000.0);
//            p[r + c *_cols] = r * 10 + c;

}

void _dump_m3x(float *p, int _rows, int _cols) {

    for(int r = 0; r < _rows; r++ ) {
    	printf("r: %3i - ", r);
        for (int c = 0; c < _cols; c++)
            // printf("%8.2f", p[ c + r * _cols]);
//            printf("%8d", p[ r + c * _cols]);
        	// printf("%10.3f ", p[ c + r * _cols]);
        	printf("%10.3f ", p[ c + r * _cols]);
        printf("\n");
    }
    printf("\n");

}

double _diff_millis(struct timespec* start, struct timespec* end) {

    struct timespec temp;

    if ( (end -> tv_nsec - start -> tv_nsec) < 0 ) {

        temp.tv_sec = end -> tv_sec - start -> tv_sec - 1;
        temp.tv_nsec = 1000000000 + end -> tv_nsec - start -> tv_nsec;

    } else {

        temp.tv_sec = end -> tv_sec - start -> tv_sec;
        temp.tv_nsec = end -> tv_nsec - start -> tv_nsec;

    }

    return
    	( 1.0*1e3f * ( (double) temp.tv_sec) ) +
    	( ((double) temp.tv_nsec) / (1.0 * 1e6f) );

}

void printPerformence(float _millis, float _totalMillis, const char* str) {
	float msecPerMatrixMul = _millis / 1;
    double flopsPerMatrixMul = 2.0 * (double)m * (double)n * (double)k;
    double gigaFlops = (flopsPerMatrixMul * 1.0e-9f) / (msecPerMatrixMul / 1000.0f);

	float totalMsecPerMatrixMul = _totalMillis / 1;
    double totalFlopsPerMatrixMul = 2.0 * (double)m * (double)n * (double)k;
    double totalGigaFlops = (totalFlopsPerMatrixMul * 1.0e-9f) / (totalMsecPerMatrixMul / 1000.0f);

    int threadsCount = _block_x*_block_y*_thread_x*_thread_y;
    if(_analiz_format) {
	    printf("%.6f , %.6f , %.6f , %.6f , %.0f , %i , %i , %i , %i , %i\n",
	        gigaFlops,
	        msecPerMatrixMul,
	        totalGigaFlops,
	        totalMsecPerMatrixMul,
	        totalFlopsPerMatrixMul,
	        _block_x,
	        _block_y,
	        _thread_x,
	        _thread_y,
	        threadsCount);  
	    return;
    }
	printf("[INFO] %s calc time (millis): %f and total time %f\n", str, _millis, _totalMillis);
    printf(
        "[INFO] Performance= %.6f GFlop/s, Time= %.6f msec, Size= %.0f Ops\n",
        gigaFlops,
        msecPerMatrixMul,
        flopsPerMatrixMul);
    printf(
        "[INFO] Total Performance= %.6f GFlop/s, Time= %.6f msec, Size= %.0f Ops\n\n",
        totalGigaFlops,
        totalMsecPerMatrixMul,
        totalFlopsPerMatrixMul);
}

void readTextInputFile(const char* fileName, float* a, float* b, int &m, int &n, int &k){
	_free_m3x(&a, m, n);
	_free_m3x(&b, n, k);
	a = _alloc_m3x(m, n);
	b = _alloc_m3x(n, k);
	FILE *fp = fopen(fileName, "r");
    fscanf(fp, "%i", &m);
    fscanf(fp, "%i", &n);
    fscanf(fp, "%i", &k);
    unsigned int count = m*n;
    for (unsigned int i = 0; i < count; i++) {
    	fscanf(fp, "%f", a+i);
    }
	count = n*k;
    for (unsigned int i = 0; i < count; i++) {
    	fscanf(fp, "%f", b+i);
    }
    fclose(fp);
}
void readBinInputFile(const char* fileName, float* a, float* b, int &m, int &n, int &k){
	int mdimm[3] = {0, 0, 0};
	FILE *fp = fopen(_load_file_name, "r");
	fread((void *) mdimm, sizeof(int), 3, fp);
	m = mdimm[0];
	n = mdimm[1];
	k = mdimm[2];
	// NOTE: who will free our previous data ...
	_free_m3x(&a, m, n);
	_free_m3x(&b, n, k);
	// _free_m3x(&c, m, k);
	a = _alloc_m3x(m, n);
	b = _alloc_m3x(n, k);
	// c = _alloc_m3x(m, k);
	fread( (void *) a, sizeof(int), m * n, fp);
	fread( (void *) b, sizeof(int), n * k, fp);
	// fread( (void *) c, sizeof(int), m * k, fp);
	fclose(fp);
}

void dumpTextOuputInFile(const char* fileName, float* c, int &m, int &n, int &k){
	FILE *fp = fopen(_dump_file_name, "w");
    fprintf(fp, "%i ", m);
    fprintf(fp, "%i ", n);
    fprintf(fp, "%i\n", k);

    for (int row = 0; row < m; row++){
	    for (int col = 0; col < k; col++){
			fprintf(fp, "%f", c[row*m + col]);
			if(col != k - 1) fwrite(" ", sizeof(char), 1, fp);
	    }
		if(row != m - 1) fwrite("\n", sizeof(char), 1, fp);
    }


	char array[10];
	sprintf(array, "%f", 3.123);

	fclose(fp);
}
void dumpBinOutoutInFile(const char* fileName, float* a, float* b, float* c, int &m, int &n, int &k){
	int mdimm[3] = {m, n, k};
	FILE *fp = fopen(_dump_file_name, "w");
	fwrite((void *) mdimm, sizeof(float), 3, fp);
	fwrite((void *) a, sizeof(float), m * n, fp);
	fwrite((void *) b, sizeof(float), n * k, fp);
	fwrite((void *) c, sizeof(float), m * k, fp);

	fclose(fp);
}
// m = rows_a, n = cols_a, k = cols_b
// plain old single thread calculator...
void _m3x_calc_host(float *a, float *b, float *c, int m, int n, int k) {

	for (int row = 0; row < m; row++) {
		for (int col = 0; col < k; col++) {
			float _sum = 0.0f;
	    	for (int l = 0; l < n; l++)
	    	 	_sum += a[l + row * n] * b[col + l * k];
	        c[col + row * k] = _sum;
		}
	}

}

// CUDA kernel...
__global__ void _m3x_calc_device(float *a, float *b, float *c, int m, int n, int k) {
    int row = threadIdx.y + blockIdx.y * blockDim.y;
    int col = threadIdx.x + blockIdx.x * blockDim.x;

    while (row < m) {
        col = threadIdx.x + blockIdx.x * blockDim.x ;
        while (col < k) {
        	float _sum = 0;
        	for (int l = 0; l < n; l++)
        		_sum += a[l + row * n] * b[col + l * k];

            c[col + row * k] = _sum;
            col += blockDim.x * gridDim.x;
        }
        row += blockDim.y * gridDim.y;
    }
    return;
}

__global__ void _m3x_calc_device2(float *a, float *b, float *c, int m, int n, int k) {
    int row = threadIdx.y + blockIdx.y * blockDim.y;
    int col = threadIdx.x + blockIdx.x * blockDim.x;
    if(row >= m || col >= k) return;
    float cVal = 0;
    for (int i = 0; i < n; i++)
    {
    	cVal += a[row*n+i]*b[i*k+col];
    }
    c[row*k+col] = cVal;
    return;
}

__global__ void matMul2(float* A, float* B, float* C, int m, int n, int K) {
	const unsigned int bx = blockDim.x, by = blockDim.y;
	// const unsigned int bx = BLOCK_X_SIZE, by = BLOCK_Y_SIZE;
	// const unsigned int bx = 16, by = 16;
	const unsigned int tx = threadIdx.x, ty = threadIdx.y;
	const unsigned int row = blockIdx.x*bx + tx, col = blockIdx.y*by + ty;
	const unsigned int gx = gridDim.x, gy = gridDim.y;
	// __shared__ int a[bx][by], b[bx][by];
	extern __shared__ float a[], b[];
	if ((row >= m) || (col >= K)) return;
	// float c = 0.0f;
	float c = 0;
	for (unsigned int k=0; k < gy; k++){
		// a[tx][ty] = A[ I*K+k*by+ty];
		// b[ty][tx] = B[J+K*(k*bx+tx)];
		// a[tx*m + ty] = A[ I*K+k*by+ty];
		// b[ty*n + tx] = B[J+K*(k*bx+tx)];
		// a[tx*gx + ty] = A[ I*K+k*by+ty];
		// b[ty*gy + tx] = B[J+K*(k*bx+tx)];

		a[tx*gx + ty] = A[ row*m+k*by+ty];
		b[ty*gy + tx] = B[ col*k+k*bx+tx];
		__syncthreads(); // Synchronizes all threads in a block
		for (unsigned int kk=0; kk< bx; kk++)
			// c += a[kk][tx]*b[kk][ty];
			// c += a[kk*m + tx]*b[kk*n + ty];
			// c += a[kk*m + tx]*b[kk*n + ty];
			// c = a[kk*m + tx]*b[kk*n + ty];
			// c = a[kk*gy + tx]*b[kk*gx + ty];
			c += a[kk*gy + tx]*b[kk*gx + ty];
		__syncthreads(); // Avoids memory hazards
	}
	C[row*K+col] = c;
} 
// m = rows_a, n = cols_a, k = cols_b
// __global__ void matrixMul(int *A_gpu, int *B_gpu, int *C_gpu, int m, int n, int K){
//     __shared__ float A_tile[blockDim.y][blockDim.x];
//     __shared__ float B_tile[blockDim.x][blockDim.y];
//     int accu = 0;
//     int i, j;
//     /* Accumulate C tile by tile. */
//     for(int tileIdx = 0;  tileIdx <= (K/blockDim.x - 1); tileIdx++){
//         /* Load one tile of A and one tile of B into shared mem */
//         // Row i of matrix A
//         i = blockIdx.y * blockDim.y + threadIdx.y;
//         // Column j of matrix A
//         j = tileIdx * blockDim.x + threadIdx.x;
//         // Load A(i,j) to shared mem
//         // A_tile[threadIdx.y][threadIdx.x] = A_gpu[i][j];  
//         A_tile[threadIdx.y][threadIdx.x] = A_gpu[i*m + j];  
//         // Load B(j,i) to shared mem
//         // B_tile[threadIdx.x][threadIdx.y] = B_gpu[j][i]; // Global Mem Not coalesced
//         B_tile[threadIdx.x][threadIdx.y] = B_gpu[i*m + j];
//         // Synchronize before computation
// 		__syncthreads();                         
//         /* Accumulate one tile of C from tiles of A and B in shared mem */
//         for(int k = 0; k < threadDim.x; k++){
//             // Accumulate for matrix C
//             accu = accu + A_tile[threadIdx.y][k] * B_tile[k][threadIdx.x];
//         }
//         // Synchronize
//         __syncthreads();
//     }
//     // Row i of matrix C
//     i = blockIdx.y * blockDim.y + threadIdx.y;
//     // Column j of matrix C
//     j = blockIdx.x * blockDim.x + threadIdx.x;
//     // Store accumulated value to C(i,j)
//     C_gpu[i][j] = accu;
// }

// m = rows_a = rows_c, n = cols_a, k = cols_b = cols_c
void callHost(float* a, float* b, float* c, int m, int n, int k){
	struct timespec _tsb;
	struct timespec _tse;
	clock_gettime(CLOCK_MONOTONIC, &_tsb);
	_m3x_calc_host(a, b, c, m, n, k);
	// sleep(1);
	clock_gettime(CLOCK_MONOTONIC, &_tse);
	printPerformence(_diff_millis(&_tsb, &_tse), _diff_millis(&_tsb, &_tse), "host cpu");

	if (_dump_m3x_data == 1) {
		printf("[INFO] dumping m3x C\n");
		_dump_m3x(c, m, k);
	}
}
void callCuda1(float* a, float* b, float* c, int m, int n, int k){ // device calcs...
	dim3 blocks(_block_x,_block_y);
	dim3 threads(_thread_x,_thread_y);

	float *dev_a;
	float *dev_b;
	float *dev_c;
	_init_m3x(c, m, k, 0, 1);

	cudaEvent_t start, stop, totalStart, totalStop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventCreate(&totalStart);
	cudaEventCreate(&totalStop);

	cudaEventRecord(totalStart);
	cudaMalloc( (void**) &dev_a, m * n * sizeof(float) );
	cudaMalloc( (void**) &dev_b, n * k * sizeof(float) );
	cudaMalloc( (void**) &dev_c, m * k * sizeof(float) );

	cudaMemcpy( dev_a, a, m * n * sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dev_b, b, n * k * sizeof(float), cudaMemcpyHostToDevice );

	cudaEventRecord(start);
	_m3x_calc_device<<<blocks,threads>>>(dev_a, dev_b, dev_c, m, n, k);
	cudaEventRecord(stop);
	cudaMemcpy( c, dev_c, m * k * sizeof(float), cudaMemcpyDeviceToHost );
	cudaEventRecord(totalStop);
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

	cudaEventSynchronize(stop);
	float _millis = 0.0;
	float _totalMillis = 0.0;
	cudaEventElapsedTime(&_millis, start, stop);
	cudaEventElapsedTime(&_totalMillis, totalStart, totalStop);
	printPerformence(_millis, _totalMillis, (const char*)("cuda kernel"));
	if (_dump_m3x_data == 1) {
		printf("[INFO] dumping m3x C\n");
		_dump_m3x(c, m, k);
	}
}
void callCuda2(float* a, float* b, float *c, int m, int n, int k){ // device calcs...
	dim3 blocks(_block_x,_block_y);
	dim3 threads(_thread_x,_thread_y);

	float *dev_a;
	float *dev_b;
	float *dev_c;
	_init_m3x(c, m, k, 0, 1);

	cudaEvent_t start, stop, totalStart, totalStop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventCreate(&totalStart);
	cudaEventCreate(&totalStop);

	cudaEventRecord(totalStart);
	cudaMalloc( (void**) &dev_a, m * n * sizeof(float) );
	cudaMalloc( (void**) &dev_b, n * k * sizeof(float) );
	cudaMalloc( (void**) &dev_c, m * k * sizeof(float) );

	cudaMemcpy( dev_a, a, m * n * sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dev_b, b, n * k * sizeof(float), cudaMemcpyHostToDevice );

	cudaEventRecord(start);
	_m3x_calc_device2<<<blocks,threads>>>(dev_a, dev_b, dev_c, m, n, k);
	cudaEventRecord(stop);
	cudaMemcpy( c, dev_c, m * k * sizeof(float), cudaMemcpyDeviceToHost );
	cudaEventRecord(totalStop);
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

	cudaEventSynchronize(stop);
	float _millis = 0.0;
	float _totalMillis = 0.0;
	cudaEventElapsedTime(&_millis, start, stop);
	cudaEventElapsedTime(&_totalMillis, totalStart, totalStop);
	printPerformence(_millis, _totalMillis, (const char*)("cuda kernel"));
	if (_dump_m3x_data == 1) {
		printf("[INFO] dumping m3x C\n");
		_dump_m3x(c, m, k);
	}
}
void getMiddleDiv(int &num, int &thRow, int&thCol, int& m, int &n, int &k){
    int sq = sqrt(num);
    while(num % sq != 0){
        sq--;
    }
    thRow = sq;
    thCol = num/sq;
    
    while(thRow > m || thCol > k)
    {
        num++;
        sq = sqrt(num);
        while(num % sq != 0){
            sq--;
        }
        thRow = sq;
        thCol = num/sq;
    }
}

void getMiddleDiv2(int &num, int &thRow, int&thCol, int& m, int &n, int &k){
    int sq = sqrt(num);
    while(num % sq != 0){
        sq--;
    }
    thRow = sq;
    thCol = num/sq;
    int precision = 3;
    while(thRow > m || thCol > k || thCol > precision*thRow || thRow > precision*thCol)
    {
        num++;
        sq = sqrt(num);
        while(num % sq != 0){
            sq--;
        }
        thRow = sq;
        thCol = num/sq;
    }
}
void mult2_v1(int &RowsB, int &ColsB,int &RowsT, int &ColsT, int maxGridT, int& m, int &n, int &k){
	if(RowsT >= maxGridT && ColsT >= maxGridT) {
		if(RowsB > ColsB) ColsB*=2;
		else if(RowsB < ColsB) RowsB*=2;
		else if(RowsB == ColsB) RowsB*=2;
	}
	else {
		if(RowsT > ColsT) ColsT*=2;
		else if(RowsT < ColsT) RowsT*=2;
		else if(RowsT == ColsT) RowsT*=2;
	}
}
int main(int argc, char **argv) {

	// http://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html#Using-Getopt
	_process_cmd_line(argc, argv);

	// nvcc -o rm3x --gpu-architecture=compute_52 -m64 rm3x.cu
	if (_info == 1) _identify_cuda_devices();
	float *a = _alloc_m3x(m, n);
	float *b = _alloc_m3x(n, k);
	float *c = _alloc_m3x(m, k);
	if (_load_file == 1) {
		readTextInputFile(_load_file_name, a, b, m, n, k);
		printf("[INFO] program updated the following parameters:\n");
		printf("[INFO] -m %d\n", m);
		printf("[INFO] -n %d\n", n);
		printf("[INFO] -k %d\n", k);
		printf("\n");
	} else {
		srand48(time(NULL));
		_init_m3x(a, m, n, 1, 0);
		_init_m3x(b, n, k, 1, 0);
		_init_m3x(c, m, k, 0, 1);
	}
	if (_dump_m3x_data == 1) {
		printf("[INFO] dumping m3x A\n");
		_dump_m3x(a, m, n);
		printf("[INFO] dumping m3x B\n");
		_dump_m3x(b, n, k);
	}
	if(_host_cpu == 1){ callHost(a,b,c,m,n,k); }
	

	for (int i = _testStep; i < 32*32; /*i+=_testStep*/) {
		int sq = sqrt(i);
	    // _thread_y = sq+1;
	    // _thread_x = sq;

		if(_thread_x != sq && _thread_y != sq)
		{
		    _thread_x = sq;
		    _thread_y = sq;
			callCuda1(a,b,c,m,n,k);
		}
	    _thread_y = sq+1;
	    _thread_x = sq;

		callCuda1(a,b,c,m,n,k);
	    _thread_y = sq + 1;
	    _thread_x = sq + 1;
		callCuda1(a,b,c,m,n,k);
		i = _thread_x*_thread_y;
	}

	for (int i = 1; i < 32*32; /*i+=_testStep*/) {
		int sq = sqrt(i);
	    // _thread_y = sq+1;
	    // _thread_x = sq;

		if(_block_x != sq && _block_y != sq)
		{
		    _block_x = sq;
		    _block_y = sq;
			callCuda1(a,b,c,m,n,k);
		}
	    _block_y = sq+1;
	    _block_x = sq;

		callCuda1(a,b,c,m,n,k);
	    _block_y = sq + 1;
	    _block_x = sq + 1;
		callCuda1(a,b,c,m,n,k);
		i = _block_y*_block_x;
	}

	// for (int i = 1; i < _testCount; i+=_testStep) {
	// 	getMiddleDiv2(i,_thread_x, _thread_y, m,n,k);
	// 	callCuda1(a,b,c,m,n,k);

	// }

	// for (long long i = _testStep; i < _testCount; ) {
	// 	i = _block_x*_block_y*_thread_x*_thread_y;
	// 	// getMiddleDiv2(i,_block_x, _block_y, m,n,k);
	// 	callCuda1(a,b,c,m,n,k);
	// 	mult2_v1(_block_x, _block_y,_thread_x,_thread_y, _testStep, m,n,k);
	// }


	// for (long long i = m; i < _testCount; ) {
	// 	i = m;
	// 	m=m*1.2;
	// 	k=k*1.2;
	// 	// i = _block_x*_block_y*_thread_x*_thread_y;
	// 	// getMiddleDiv2(i,_block_x, _block_y, m,n,k);
	// 	callCuda1(a,b,c,m,n,k);
	// 	// mult2_v1(_block_x, _block_y,_thread_x,_thread_y, _testStep, m,n,k);
	// }



	// callCuda2(a,b,c,m,n,k);
	if (_dump_file == 1) {
		dumpTextOuputInFile(_dump_file_name,c,m,n,k);
	}

	return 0;

}


