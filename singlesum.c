#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "factorial.h"
#define NUMBER_OF_THREADS 10
#define SUM_MEMBERS_PER_THREAD 10

double x;
double result = 0;
pthread_t threads[NUMBER_OF_THREADS];
int startingPoints[NUMBER_OF_THREADS];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* calculateSubSum(void* subSumInfo);

int main()
{
    clock_t start, end;
    double cpu_time_used;

    printf("This is a sin(x) multithreaded estimator around 0. Please enter your desired x: ");
    scanf("%lf", &x);

    start = clock();

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        startingPoints[i] = i * SUM_MEMBERS_PER_THREAD;
        int ret = pthread_create(&threads[i], NULL, &calculateSubSum, (void*) &startingPoints[i]);
        if (ret != 0)
        {
            printf("Error creating thread %d, reason: %d", i, ret);
            return -1;
        }
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(threads[i], NULL);

    end = clock();

    printf("sin(%.2lf) = %lf\n", x, result);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);
    return 0;
}

void* calculateSubSum(void* arg)
{
    int* startingPoint = (int*) arg;

    pthread_mutex_lock(&mutex);
    for (double n = *startingPoint; n < *startingPoint + SUM_MEMBERS_PER_THREAD; n++)
        result += (pow(-1.0, n) * pow(x, 2*n+1) / factorial(2*n+1));
    pthread_mutex_unlock(&mutex);

    return NULL;
}