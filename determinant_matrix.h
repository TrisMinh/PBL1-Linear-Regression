#ifndef MATRIX_DETERMIANT_H
#define MATRIX_DETERMINANT_H
#include <iostream>
#include <vector> 
#include "get_submatrix.h"
namespace MatrixDetermiant{
    double determinant(std::vector<std::vector<double>>& matrix) {
    if (matrix.size() == 1) {
        return matrix[0][0];
    }
    if (matrix.size() == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        std::vector<std::vector<double>> subMatrix = SubMatrix::getSubMatrix(matrix, 0, i);
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(subMatrix);
    }
    return det;
}
}
#endif 
