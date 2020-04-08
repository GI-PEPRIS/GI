#ifndef __ANYWAY_UTIL /* allow multiple inclusions */
#define __ANYWAY_UTIL

#ifdef __cplusplus
#define SUPPER_EXTERN_C extern "C"
#include <cstdio>
#else
#define XGB_EXTERN_C
#include <stdio.h>
#include <stdint.h>
#endif

#if defined(SUPERLUMT_EXPORTS)	//defined(_MSC_VER) || defined(_WIN32)	// herman
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

SUPPER_DLL float *floatMalloc_pc(int n);
SUPPER_DLL long long int *intMalloc_pc(int n);
SUPPER_DLL void psgssv_pc(int nprocs, int nrhs, int m, int n, int nnz, float *a, long long int *asub, long long int *xa, float *rhs, float* result);
SUPPER_DLL void psgssvx_pc(int nprocs, int nrhs, int m, int n, int nnz, float *a, long long int *asub, long long int *xa, float *rhs, float* result);
//

#endif