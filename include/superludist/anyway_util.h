#ifndef __ANYWAY_UTIL /* allow multiple inclusions */
#define __ANYWAY_UTIL

#ifdef __cplusplus
#define SUPPER_EXTERN_C extern "C"
#include <cstdio>
#include <string>
#else
#define XGB_EXTERN_C
#include <stdio.h>
#include <stdint.h>
#endif

#if defined(SUPERLUDIST_EXPORTS)	//defined(_MSC_VER) || defined(_WIN32)	// herman
#define SUPPER_DLL SUPPER_EXTERN_C __declspec(dllexport)
#else
#define SUPPER_DLL SUPPER_EXTERN_C 
#endif

//#include ".\SRC\slu_dcomplex.h"

typedef struct  
{
}pthread_mutex_t;
typedef pthread_mutex_t mutex_t;

#define EXIT return

typedef struct  
{
}pthread_mutexattr_t;

typedef struct  
{
}pthread_t;
typedef struct  
{
}pthread_attr_t;

SUPPER_DLL int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex); //mutex 指向要销毁的互斥锁的指针
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *start_rtn,void *arg);
int pthread_join(pthread_t thread, void **retval);

SUPPER_DLL double *doubleMalloc_pc(int n);
SUPPER_DLL long long int *intMalloc_pc(int n);
SUPPER_DLL void psgssvx_pc(int nprocs, int nrhs, int m, int n, int nnz, double *a, long long int *asub, long long int *xa, double *rhs, double* result);

int dcreate_matrix(SuperMatrix *A, int nrhs, double **rhs, int *ldb, double **x, int *ldx, FILE *fp, gridinfo_t *grid, bool isruamode);
int pdcompute_resid(int m, int n, int nrhs, SuperMatrix *A, double *x, int ldx, double *b, int ldb, gridinfo_t *grid, SOLVEstruct_t *SOLVEstruct, double *resid);
void parse_command_line(int argc, char *argv[], int *nprow, int *npcol, char *matrix_type, int *n, int *relax, int *maxsuper, \
	int *fill_ratio, int *min_gemm_gpu_offload, int *nrhs, FILE **fp, bool &isruamode, std::string &matrixfilepath);
int getopt_pc(int argc, char *const argv[], const char *optstring, char* &optarg, int &optind);
int is_end_with(const char *str1, char *str2);
void dCopy_CompRowLoc_NoAllocation(SuperMatrix *A, SuperMatrix *B);
void PrintSumm(char *type, int nfail, int nrun, int nerrs);
int cpp_defs();
#endif