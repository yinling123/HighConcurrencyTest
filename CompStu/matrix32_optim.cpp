#include<iostream>
#include <chrono>

void matrix(const int n){
    int m1[n][n];
    int m2[n][n];
    int m3[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m1[i][j] = i;
            m2[i][j] = i;
            m3[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++){
        for(int k = 0; k < n; k++){
            int sum = 0;
            for(int j = 0; j < n; j++){
                //交换顺序，提高连续性
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << m1[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << m2[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << m3[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    matrix(32);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "程序运行时间: " << duration.count() << " 秒" << std::endl;
    return 0;
}