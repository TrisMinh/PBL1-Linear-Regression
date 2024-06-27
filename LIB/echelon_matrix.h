#ifndef MATRIX_ECHELON_H
#define MATRIX_ECHELON_H
#include <iostream>
#include <vector>

namespace EchelonMatrix { // biến đổi ma trận bậc thang
    std::vector<std::vector<double>> toRowEchelonForm(std::vector<std::vector<double>>& matrix1) {
        std::vector<std::vector<double>> matrix = matrix1;
        int lead = 0; // chỉ số chạy
        int rowCount = matrix.size(); // hàng
        int colCount = matrix[0].size(); // cột
        for (int r = 0; r < rowCount; ++r) { // duyệt rowCount lần 
            if (lead >= colCount) { // duyệt hết rowCount lần thì thoát
                return matrix;
            }
            int i = r;
            while (matrix[i][lead] == 0) {
                ++i;
                if (i == rowCount) {
                    i = r;
                    ++lead;
                    if (lead == colCount) { // duyệt hết rowCount lần thì thoát
                        return matrix;
                    }
                }
            }
            std::swap(matrix[i], matrix[r]);
            double lv = matrix[r][lead]; // lưu giá trị của phần tử tại lead xét
            for (int j = 0; j < colCount; ++j) {
                matrix[r][j] /= lv; // chia phần tử r j cho phần tử lead xét
            }
            for (int i = 0; i < rowCount; ++i) {
                if (i != r) {
                    double lv = matrix[i][lead];
                    for (int j = 0; j < colCount; ++j) {
                        matrix[i][j] -= lv * matrix[r][j]; // biến đổi tuyến tính đưa về 
                    }
                }
            }
            ++lead;
        }
        return matrix;
    }
}
#endif
