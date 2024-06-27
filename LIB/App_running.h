#ifndef APP_RUNNING.H
#define APP_RUNNING.H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map> // ánh xạ || để lưu thứ tự ma trận bằng tên 
namespace App {
    void loadVariables(const std::string &filename, std::map<std::string, double> &variables) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        // Bỏ qua dòng đầu tiên
        std::getline(file, line);

        // Đọc dòng thứ hai để lấy tên biến
        std::getline(file, line);
        std::stringstream ss(line);
        std::string variableName;
        while (std::getline(ss, variableName, ',')) { // lặp lấy phần tử cho đến khi gặp dấu phẩy
            // Nếu gặp dấu chấm phẩy thì dừng lại
            if (variableName.find(';') != std::string::npos) {  // không phải ; thì tiếp tục
                variableName = variableName.substr(0, variableName.find(';'));
                variables[variableName] = 0.0; // Khởi tạo giá trị mặc định
                break;
            }
            variables[variableName] = 0.0; // Khởi tạo giá trị mặc định
        }

        file.close();
    } else {
        std::cerr << "Khong the mo file: " << filename << std::endl;
    }
}
void inputVariables(std::map<std::string, double> &variables) {
    for (auto &var : variables) {
        std::cout << "Nhap gia tri cho " << var.first << ": ";
        std::cin >> var.second; // nhập giá trị cho các biến
    }
}
void saveVariablesToVector(const std::map<std::string, double> &variables, std::vector<double> &values) {
        values.clear();
        values.push_back(1.0);
        for (const auto &var : variables) {
            values.push_back(var.second); // Lưu giá trị vào vector
        }
    }
}
#endif



