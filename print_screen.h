#ifndef PRINT_SCREEN_H
#define PRINT_SCREEN_H
#include <iostream>
#include <vector> 
#include <iomanip> 
namespace print {
    void print_matrix(std::vector<std::vector<double>> &matrix){
        for(const auto& row : matrix){
            for(const auto& num : row){
                std::cout << std::fixed << std::setprecision(4) << num;
                std::cout << " ";
            }
            std::cout << '\n';
        }
    }
}
#endif 
