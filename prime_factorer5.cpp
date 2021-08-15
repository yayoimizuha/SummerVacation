//
// Created by tomokazu on 2021/08/14.
//

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <omp.h>
#include <cstring>

unsigned long long dividable_num(unsigned long long num);


int main() {
    /*Check OMP_CANCELLATION is true*/
    if (omp_get_cancellation() != true) {
        return 1;
    }
    /*set prime check integer*/
    unsigned long long num;
    //256 * 256 * 256 * 256 * 256 * 256
    num = (unsigned long long) 729 * 64;
    printf("素因数分解を実行: %lld\n",num);

    unsigned long long tmp_num;
    unsigned long long tmp = num;
    int array_order;

    printf("log_2(num): %d\n", (int) log2((double) num));

    unsigned long long *sub_arr, *work_arr;
    work_arr = (unsigned long long *) calloc((int) log2((double) num) + 10, sizeof(unsigned long long));
    sub_arr = (unsigned long long *) calloc((int) log2((double) num) + 10, sizeof(unsigned long long));

    if (work_arr == nullptr && sub_arr == nullptr) {
        printf("Failed allocating memory.\n");
        return 1;
    }

    work_arr[0] = num;

    while (true) {
        array_order = 0;
        for (int i = 0; i < (int) log2((double) tmp) + 2; ++i) {
            tmp_num = dividable_num(work_arr[i]);
            if (tmp_num != work_arr[i]) {
                sub_arr[array_order] = work_arr[i] / tmp_num;
                array_order++;
            }
            sub_arr[array_order] = tmp_num;
            array_order++;
        }

        if (memcmp(sub_arr, work_arr, ((int) log2((double) num) + 10) * sizeof(unsigned long long)) == 0) {
            printf("一致\n");
            break;
        } else{
            printf("不一致\n");
        }
        memmove(work_arr, sub_arr, ((int) log2((double) num) + 10) * sizeof(unsigned long long));
    }

    for (int i = 0; i < (int) log2((double) tmp); ++i) {
        if (work_arr[i] != 0) {
            printf("%lld\t", work_arr[i]);
        } else {
        }
    }
    return 0;
}

unsigned long long dividable_num(unsigned long long num) {
    unsigned long long ans = num;
    bool cancel = false;
#pragma omp parallel for  shared(cancel)

    for (unsigned long long i = 2; i < (unsigned long long) sqrt((double) num) + 1; ++i) {
        if (num % i == 0) {
            ans = i;
            cancel = true;
#pragma omp cancel for
        }
#pragma omp cancel for if(cancel)
    }
    return ans;
}