//
// Created by tomokazu on 2021/08/12.
//

#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

unsigned long long calculate(unsigned long long num,unsigned long long *arr,int arr_num);

int main(){
    cout << "数を入力: ";
    unsigned long long num;
    cin >> num;
    cout << "素因数分解を実行:" << num << endl;
    unsigned long long *arr;
    int arr_num = 1;
    arr = (unsigned long long *) malloc(sizeof(unsigned long long) * arr_num);
    calculate(num,arr,arr_num);
}

unsigned long long calculate(unsigned long long num,unsigned long long *arr,int arr_num){
#pragma omp parallel
#pragma omp for
    for (unsigned long long i = 2; i < (unsigned long long)sqrt((double)num); ++i) {
        if (num == 1){
            printf("a1");
#pragma omp cancel for if(true)
        } else if(num == 2){
            printf("a2");
            arr[arr_num] = 2;
#pragma omp cancel for if(true)
        }
        if (num %  i == 1){
            printf("%lld\n",i);
            arr[arr_num] = i;
            arr_num++;
            calculate(num / i,arr,arr_num);
        }
    }
    return 0;
}
