#include <cstdio>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define N 100000
using namespace std;
int map[N][N] = {{0}};

int main() {
    printf("Run main.\n");
    printf("available threads: %d\n", omp_get_max_threads());


    printf("%lu\n", sizeof(map));

    unsigned long sum = 0;
    //omp_lock_t myLock;
    //omp_init_lock(&myLock);
    #pragma omp parallel
    #pragma omp for
    for (int i = 0; i < N; ++i) {
        //omp_set_lock(&myLock);
        for (int j = 0; j < N; ++j) {
            //printf("i: %d\tj: %d\n",i,j);
            map[i][j] = sqrt(i * i + j * j) <= (float)N ? 1 : 0;
            //omp_unset_lock(&myLock);
        }
    }
    printf("step1\n");

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += map[i][j];
        }
    }
    printf("sum: %ld\n",sum );
    printf("(int)sum: %ld\n",(int)sum );


    printf("pi: %f\n", ( (int)sum / (float)(N*N) ) * 4);
    return 0;

}

int test (){
    long sum = 1714196441;
    printf("pi: %f\n", ( (int)sum / (float)(N*N) ) * 4);
    return 0;
}