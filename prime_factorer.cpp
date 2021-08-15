//
// Created by tomokazu on 2021/08/09.
//

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <omp.h>

unsigned long long check_prime(unsigned long long num);

int main() {
    if (omp_get_cancellation() != true) {
        return 1;
    }
    unsigned long long num;
    num = (unsigned long long) 256 * 256 * 256 * 256 * 256 * 256;
    int flag = 0;
    unsigned long long test = 1;
    unsigned long long *arr;
    arr = (unsigned long long *) malloc(sizeof(unsigned long long) * (long) sqrt((double) num));
    bool cancel = false;
#pragma omp parallel for  shared(cancel)
    for (unsigned long long i = 2; i < (unsigned long long) sqrt((double) num) + 1; ++i) {
        if (num % i == 0) {
            arr[flag] = i;
            flag++;
            printf("dividable: ");
            test = test * i;
            printf("%lld\n", test);
            if (test > num / i || cancel) {
                printf("test: %lld\n", test);
                printf("i: %lld\n", i);
                printf("canceling loop...\n");
                cancel = true;
#pragma omp cancel  for
            }
        }
#pragma omp cancel  for if(cancel)
    }
    printf("\n\n素因数分解: %lld\n", num);
    //        num = num / arr[flag];
    //    }
    int i = 0;
    while (arr[i] != 0) {
        printf("%lld * %lld\n", arr[i], num / arr[i]);
        i++;
    }

    printf("\n\n");
    i = 0;
    unsigned long long all_nums = 1;
    while (arr[i] != 0) {
        for (int loop = 0; loop < i; loop++) {
            if (arr[i] % arr[loop] == 0) {
                arr[i] = arr[i] / arr[loop];
            }
        }
        if (arr[i] != 1) {
            printf("%lld ", arr[i]);
            all_nums = all_nums * arr[i];
        }
        i++;
    }
    printf("\n");
    unsigned long long *last_list;
    last_list = (unsigned long long *) malloc(sizeof(unsigned long long) * i);
    for (int count = 0; count < i; count++) {
        last_list[count] = arr[count];
    }

    last_list[i] = num / all_nums;

    printf("num/all_num;%lld\n", num / all_nums);
    printf("i:%d", i);

    printf("\n\nline73\n\n");
    for (int count = 0; count < i + 1; count++) {
        if (last_list[count] != 0 && last_list[count] != 1) {
            printf("%lld ", last_list[count]);
        }
    }

    return 0;
}

unsigned long long check_prime(unsigned long long num){
    num = (unsigned long long) 256 * 256 * 256 * 256 * 256 * 256;
    int flag = 0;
    unsigned long long test = 1;
    unsigned long long *arr;
    arr = (unsigned long long *) malloc(sizeof(unsigned long long) * (long) sqrt((double) num));
    bool cancel = false;
#pragma omp parallel for  shared(cancel)
    for (unsigned long long i = 2; i < (unsigned long long) sqrt((double) num) + 1; ++i) {
        if (num % i == 0) {
            arr[flag] = i;
            flag++;
            printf("dividable: ");
            test = test * i;
            printf("%lld\n", test);
            if (test > num / i || cancel) {
                printf("test: %lld\n", test);
                printf("i: %lld\n", i);
                printf("canceling loop...\n");
                cancel = true;
#pragma omp cancel  for
            }
        }
#pragma omp cancel  for if(cancel)
    }
}
