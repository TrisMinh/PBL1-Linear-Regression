#ifndef MATRIX_PRINTER_H 
#define MATRIX_PRINTER_H
#include <iostream> // Thư viện nhập xuất dữ liệu vào ra
#include <iomanip> // Thư viện điều khiển định dạng đầu ra
#include <vector> // Thư viện vector để lưu trữ ma trận
#include <fstream> // Thư viện nhập xuất file
namespace MatrixPrinter {
    void printMatrixWithBorder(std::ofstream &outputFile, const std::vector<std::vector<double>> &matrix) {
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        std::vector<std::vector<std::string>> formatted_matrix(rows, std::vector<std::string>(cols));
        int max_width = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                formatted_matrix[i][j] = std::to_string(matrix[i][j]);
                int num_width = formatted_matrix[i][j].length() + 4; // 4 extra spaces (precision, decimal point, sign)
                if (num_width > max_width) {
                    max_width = num_width;
                }
            }
        }
        outputFile << std::fixed << std::setprecision(3);
        outputFile << "        ┌";
        for (size_t col = 0; col < cols; ++col) {
            for (int k = 0; k < max_width; ++k) {
                outputFile << "─";
            }
            if (col < cols - 1) {
                outputFile << "┬";
            }
        }
        outputFile << "┐\n";
        for (size_t i = 0; i < rows; ++i) {
            outputFile << "        │";
            for (size_t j = 0; j < cols; ++j) {
                int padding = max_width - formatted_matrix[i][j].length();
                int left_padding = padding / 2;
                int right_padding = padding - left_padding;
                for (int k = 0; k < left_padding; ++k) {
                    outputFile << " ";
                }
                outputFile << formatted_matrix[i][j];
                for (int k = 0; k < right_padding; ++k) {
                    outputFile << " ";
                }
                if (j < cols - 1) {
                    outputFile << "│";
                }
            }
            outputFile << "│\n";
            if (i < rows - 1) {
                outputFile << "        ├";
                for (size_t col = 0; col < cols; ++col) {
                    for (int k = 0; k < max_width; ++k) {
                        outputFile << "─";
                    }
                    if (col < cols - 1) {
                        outputFile << "┼";
                    }
                }
                outputFile << "┤\n";
            }
        }
        outputFile << "        └";
        for (size_t col = 0; col < cols; ++col) {
            for (int k = 0; k < max_width; ++k) {
                outputFile << "─";
            }
            if (col < cols - 1) {
                outputFile << "┴";
            }
        }
        outputFile << "┘\n";
    }
}
#endif 

