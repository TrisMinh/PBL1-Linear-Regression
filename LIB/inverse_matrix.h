#ifndef MATRIX_INVERSE_H
#define MATRIX_INVERSE_H

#include <iostream>
#include <vector> 

namespace GaussJordanInverseMatrix {
    std::vector<std::vector<double>> gaussJordanInverse(std::vector<std::vector<double>>& matrix) {
        int n = matrix.size(); 
        std::vector<std::vector<double>> inverse(n, std::vector<double>(n * 2, 0.0)); // khai báo ma trận mở rộng
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inverse[i][j] = matrix[i][j]; // 1 nữa bên trái là ma trận gốc
            }
            inverse[i][i + n] = 1.0; // 1 nữa bên phải ma trận đơn vị
        }     
        for (int i = 0; i < n; ++i) {
            if (inverse[i][i] == 0.0) { // 1 phần tử trên đường chéo chính ma trận gốc = 0 thì không khả nghịc
                std::cerr << "Ma tran ko kha nghich." << std::endl;
                return std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0)); 
            }

            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    double ratio = inverse[j][i] / inverse[i][i]; // hệ số trừ = phần tử đầu tiên trong vòng lặp không phải i i
                    for (int k = 0; k < 2 * n; ++k) {
                        inverse[j][k] -= ratio * inverse[i][k]; // trừ các phần tử còn lại trên hàng đó với hệ số trừ * chính nó
                        // phần tử j i sẽ = 0 
                        // dẫn đến sau vòng lặp j lần thì các phần tử đầu tiên của hàng sẽ bằng 0
                        // tiếp tục tăng i (chỉ số cột)
                    }
                }
            }
        }      
        for (int i = 0; i < n; ++i) {
            double divisor = inverse[i][i]; // các phần tử i i chia biến đổi
            for (int j = 0; j < 2 * n; ++j) {
                inverse[i][j] /= divisor; // chia hàng đó để phần tử i i = 1 -> ma trận đơn vị
            }
        }
        std::vector<std::vector<double>> result(n, std::vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = inverse[i][j + n]; // lưu ma trận bên phải vào ma trận kết quả
            }
        }
        return result;
    }
}
#endif
