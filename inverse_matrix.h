
#ifndef MATRIX_INVERSE_H
#define MATRIX_INVERSE_H
#include <iostream>
#include <vector> 
#include "determinant_matrix.h"
#include "trans_matrix.h"
namespace InverseMatrix {
    std::vector<std::vector<double>> inverseMatrix(std::vector<std::vector<double>>& matrix) {
        double det = MatrixDetermiant::determinant(matrix);
        std::vector<std::vector<double>> inverse(matrix.size(), std::vector<double>(matrix.size()));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                std::vector<std::vector<double>> subMatrix = SubMatrix::getSubMatrix(matrix, i, j);
                inverse[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * MatrixDetermiant::determinant(subMatrix) / det;
            }
        }
        inverse = MatrixTranspose::transposeMatrix(inverse);
        return inverse;
    }
}
#endif 
