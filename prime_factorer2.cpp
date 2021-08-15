//
// Created by tomokazu on 2021/08/10.
//
#include <iostream>
#include <omp.h>

using namespace std;
unsigned long long is_prime(unsigned long long num );

int main(){
    unsigned long long is_prime_num = 323422341272342234;
    if (is_prime_num > (unsigned long long)1844674407370955161) return 1;
    while (is_prime_num != 1){
        printf("is_prime_num: %lld\n",is_prime_num);
        unsigned long long tmp = is_prime(is_prime_num);
        printf("tmp: %lld\n",tmp);
        if (tmp == 0){
            break;
        }
        if (is_prime_num % tmp == 0){
            is_prime_num = is_prime_num / tmp;
            printf("(is_prime_num // tmp == 1)tmp: %lld\n",tmp);
        }
        cout << is_prime_num << endl;
    }
    return 0;
}

unsigned long long is_prime(unsigned long long num ){

    unsigned long long dividable = 0;
    bool flag = false;

#pragma omp parallel
#pragma omp for
    for (unsigned long long i = 2; i < num; ++i) {
        if (num % i == 0){
            printf("num: %llu\ti: %llu\n",num,i);
            flag = true;
            printf("flag: %d\n",flag);
            dividable = i;
#pragma omp flush(dividable)
            printf("***************\ndividable: %lld\n************\n",dividable);
        }
#pragma omp cancel for if(dividable)

    }
    return dividable;
}