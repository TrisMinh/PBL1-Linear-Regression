#ifndef MATRIX_MULTIPLE_H
#define MATRIX_MULTIPLE_H
#include <iostream>
#include <vector> 
namespace MatrixMultiple {
    std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& mat1, const std::vector<std::vector<double>>& mat2) {
        int row1 = mat1.size();
        int col1 = mat1[0].size();
        int row2 = mat2.size();
        int col2 = mat2[0].size();
        std::vector<std::vector<double>> result(row1, std::vector<double>(col2, 0));
        for (int i = 0; i < row1; ++i) {
            for (int j = 0; j < col2; ++j) {
                for (int k = 0; k < col1; ++k) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                    // nhân hàng i ma trận này và cột i ma trận kia 
                }
            }
        }
        return result;
    }
}
#endif 
