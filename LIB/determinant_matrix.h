#ifndef MATRIX_DETERMIANT_H
#define MATRIX_DETERMINANT_H
#include <iostream>
#include <vector> 
#include "echelon_matrix.h"
namespace MatrixDetermiant{ // tinh định thức ma trận

    double determinantFromRowEchelonForm(std::vector<std::vector<double>>& matrix) {
        std::vector<std::vector<double>> tmp = EchelonMatrix::toRowEchelonForm(matrix);
        double det = 1.0;
        for (int i = 0; i < tmp.size(); ++i) {
            det *= tmp[i][i]; // nhân đường chéo của ma trận từ ma trận bậc thang đã biến đổi
        }
        return det;
    }
}
#endif 
