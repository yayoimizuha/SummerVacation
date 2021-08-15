//
// Created by tomokazu on 2021/08/14.
//

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <omp.h>
#include <cstring>

unsigned long long dividable_num(unsigned long long num);

//bool check_array(const unsigned long long *array1, const unsigned long long *array2, int length);

int main() {
    /*Check OMP_CANCELLATION is true*/
    if (omp_get_cancellation() != true) {
        return 1;
    }
    /*set prime check integer*/
    unsigned long long num;
    //256 * 256 * 256 * 256 * 256 * 256
    num = (unsigned long long) 243 * 64;

    unsigned long long tmp_num;
    unsigned long long tmp = num;
    int array_order = 0;

    printf("log_2(num): %d\n", (int) log2((double) num));

    unsigned long long *arr, *sub_arr, *work_arr;
    arr = (unsigned long long *) calloc((int) log2((double) num) + 10, sizeof(unsigned long long));
    work_arr = (unsigned long long *) calloc((int) log2((double) num) + 10, sizeof(unsigned long long));
    sub_arr = (unsigned long long *) calloc((int) log2((double) num) + 10, sizeof(unsigned long long));

    if (arr == nullptr) {
        printf("Failed allocating memory.\n");
        return 1;
    }
    //printf("%s\n", check_array(arr, work_arr, (int) log2((double) num)) ? "true" : "false");
    printf("%d\n", true);
    printf("%d\n", memcmp(arr, work_arr, ((int) log2((double) num) + 10) * sizeof(unsigned long long)));

    printf("*****************************************************\n");

    printf("%p\n", arr);
    printf("%p\n", work_arr);
    printf("%p\n", sub_arr);

    printf("*****************************************************\n");

//    while (num != 1) {
//        printf("num: %lld\n", num);
//        tmp_num = dividable_num(num);
//        num /= tmp_num;
//        work_arr[array_order] = tmp_num;
//        array_order++;
//    }

    printf("\n*****************************************************\n");

    printf("\n");
//    for (int i = 0; i < (int) log2((double) tmp); ++i) {
//        if (work_arr[i] != 0) {
////            printf("%lld\t", work_arr[i]);
//        } else {
//            break;
//        }
//    }
    work_arr[0] = num;
    printf("\n");
    while (true) {
        array_order = 0;
        for (int i = 0; i < (int) log2((double) tmp) + 2; ++i) {
            //printf("i: %d\t", i);
            tmp_num = dividable_num(work_arr[i]);
            //printf("work_arr[i]: %lld\t", work_arr[i]);
            //printf("tmp_num: %lld\n", tmp_num);
            if (tmp_num != work_arr[i]) {
                sub_arr[array_order] = work_arr[i] / tmp_num;
                array_order++;
            }
            sub_arr[array_order] = tmp_num;
            array_order++;
        }

//        printf("\n\nsub_arr\t\t");
//        for (int i = 0; i < (int) log2((double) tmp); ++i) {
//            if (sub_arr[i] != 0) {
//                printf("%lld\t", sub_arr[i]);
//            } else {
//                printf("\n");
//                //break;
//
//            }
//        }
//
//
//        printf("\n\nwork_arr\t");
//        for (int i = 0; i < (int) log2((double) tmp); ++i) {
//            if (work_arr[i] != 0) {
//                printf("%lld\t", work_arr[i]);
//            } else {
//                printf("\n");
//                //break;
//                printf("%lld\t", work_arr[i]);
//
//            }
//        }
        printf("\n");

        if (memcmp(sub_arr, work_arr, ((int) log2((double) num) + 10) * sizeof(unsigned long long)) == 0) {
            printf("一致\n");
            break;
        }
        memmove(work_arr, sub_arr, ((int) log2((double) num) + 10) * sizeof(unsigned long long));
    }

    for (int i = 0; i < (int) log2((double) tmp); ++i) {
        if (work_arr[i] != 0) {
            printf("%lld\t", work_arr[i]);
        } else {
            printf("\n");
            //break;
            //printf("%lld\t", work_arr[i]);

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
    //printf("ans: %lld\t", ans);
    return ans;
}

//bool check_array(const unsigned long long *array1, const unsigned long long *array2, int length) {
//    bool result = true;
//    while (length == -1) {
//        if (array1[length - 1] != array2[length - 1]) {
//            result = false;
//            break;
//        }
//        length--;
//    }
//    return result;
//}