
#ifndef MATRIX_SUBMATRIX_H
#define MATRIX_SUBMATRIX_H
#include <iostream>
#include <vector> 
namespace SubMatrix {
    std::vector<std::vector<double>> getSubMatrix(std::vector<std::vector<double>>& matrix, int row, int col) {
        std::vector<std::vector<double>> subMatrix;
        for (int i = 0; i < matrix.size(); ++i) {
            if (i != row) {
                std::vector<double> temp;
                for (int j = 0; j < matrix.size(); ++j) {
                    if (j != col) {
                        temp.push_back(matrix[i][j]);
                    }
                }
                subMatrix.push_back(temp);
            }
        }
        return subMatrix;
    }
}
#endif 
