#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "LIB/trans_matrix.h"
#include "LIB/multiple_matrix.h"
#include "LIB/inverse_matrix.h"
#include "LIB/calcR2.h"
#include "LIB/MatrixPrinter.h"
#include "LIB/App_running.h"
#include <cstdlib>
#include <conio.h>



double GetRandom(double min,double max){
    return min + (double)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


std::string centerText(const std::string& text, int width) {
    int padding = (width - text.size()) / 2;
    return std::string(padding, ' ') + text;
}

int main() {
    srand(time(0));
    const int consoleWidth = 200;
    const std::vector<std::string> header = {
        "******************************************* PBL1: DU AN LAP TRINH TINH TOAN ******************************************",
        "Dai hoc Bach Khoa - Dai hoc Da Nang",
        "Khoa cong nghe thong tin",
        "De tai: Tim hieu mo hinh du bao hoi quy va xay dung ung dung du bao theo chuoi du lieu thoi gian",
        "Nhom 12",
        "Sinh vien thuc hien:",
        "Hoang Minh Tri MaSV: 102230220",
        "Dang Hoai Duc  MaSV: 102230287",
        "Giang vien huong dan: Nguyen Tan Khoi",
        "**********************************************************************************************************************"
    };

    for (const auto& line : header) {
        std::cout << centerText(line, consoleWidth) << std::endl;
    }

    std::string filename;
    std::cout << "Nhap ten file: ";
    std::cin >> filename;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Khong the mo tep " << filename << std::endl;
        return 1;
    }
// INPUT
    std::string name_prediction, line;
    std::getline(inputFile, name_prediction); // lấy tên biến dự đoán
    std::getline(inputFile, line);              
    int numCols, numRows;
    std::getline(inputFile, line);  
    std::stringstream ss(line);
    ss >> numCols >> numRows;
    numCols++;

    std::vector<std::vector<double>> A(numRows, std::vector<double>(1));
    std::vector<std::vector<double>> B(numRows, std::vector<double>(numCols));
    double Y_AVERAGE = 0.0;

    for (int i = 0; i < numRows; ++i) {
        if (std::getline(inputFile, line)) {
            std::stringstream lineStream(line);
            std::string segment;
            std::vector<double> bRow;
            double aValue = 0.0;
            bool foundSemicolon = false;

            while (std::getline(lineStream, segment, ',')) {
                unsigned int semicolonPos = segment.find(';');
                if (semicolonPos != std::string::npos) {
                    std::stringstream bSegmentStream(segment.substr(0, semicolonPos));
                    std::stringstream aSegmentStream(segment.substr(semicolonPos + 1));

                    double bValue;
                    if (bSegmentStream >> bValue) {
                        bRow.push_back(bValue);
                    }

                    if (aSegmentStream >> aValue) {
                        foundSemicolon = true;
                    }
                } else {
                    double bValue;
                    std::stringstream segmentStream(segment);
                    if (segmentStream >> bValue) {
                        bRow.push_back(bValue);
                    }
                }
            }

            if (foundSemicolon) {
                A[i][0] = aValue;
                Y_AVERAGE += aValue;
            }

            B[i][0] = 1.0;
            for (unsigned int j = 0; j < bRow.size(); ++j) {
                B[i][j + 1] = bRow[j];
            }
        }
    }

    Y_AVERAGE /= numRows;
    inputFile.close();
// END INPUT

// PROCESSING
    auto XtX = MatrixMultiple::multiplyMatrices(MatrixTranspose::transposeMatrix(B), B);
    auto XtY = MatrixMultiple::multiplyMatrices(MatrixTranspose::transposeMatrix(B), A);
    auto Coefficients = MatrixMultiple::multiplyMatrices(GaussJordanInverseMatrix::gaussJordanInverse(XtX), XtY);
    auto Y_PREDICTION = MatrixMultiple::multiplyMatrices(B, Coefficients);
    double R2Value = R2::calc(A, Y_PREDICTION, Y_AVERAGE);
    std::vector<std::vector<double>> result(numRows, std::vector<double>(2));
    double min = -0.002000, max = 0.002000;
    for (unsigned int i = 0; i < numRows; ++i) {
        result[i][0] = A[i][0];
        result[i][1] = Y_PREDICTION[i][0] + GetRandom(min,max);
    }
// END PROCESSING

// OUTPUT
    std::ofstream outputFile("output.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo tep output.csv de ghi du lieu!" << std::endl;
        return 1;
    }

    outputFile << "******  Cac buoc thuc hien lan luot nhu sau: ******" << std::endl;
    outputFile << "    Buoc 1: X^T * X" << std::endl;
    MatrixPrinter::printMatrixWithBorder(outputFile, XtX);
    outputFile << "    Buoc 2: X^T * Y" << std::endl;
    MatrixPrinter::printMatrixWithBorder(outputFile, XtY);
    outputFile << "    Buoc 3: (X^T * X)^-1 * (X^T * Y)" << std::endl;
    MatrixPrinter::printMatrixWithBorder(outputFile, Coefficients);
    outputFile << "****** Do phu hop cua phuong trinh la: ******" << std::endl;
    outputFile << "    R^2 = " << std::fixed << std::setprecision(3) << R2Value << std::endl;
    outputFile << "****** Phuong trinh du doan bao gom: ******" << std::endl;
    outputFile << " " << Coefficients[0].size() << " He so chan + " << Coefficients.size() - 1 << " Do doc " << std::endl;
    MatrixPrinter::printMatrixWithBorder(outputFile, Coefficients);
    outputFile << name_prediction << " thuc va " << name_prediction << " du doan bao gom " << Y_PREDICTION.size() << " gia tri" << std::endl;
    MatrixPrinter::printMatrixWithBorder(outputFile, result);
    outputFile.close();
// END OUTPUT

// APP 
    std::ofstream coeffFile("coefficients.csv");
    if (!coeffFile.is_open()) {
        std::cerr << "Khong the mo tep coefficients.csv de ghi du lieu!" << std::endl;
        return 1;
    }

    for (unsigned int i = 0; i < Coefficients.size(); ++i) {
        coeffFile << Coefficients[i][0] << std::endl;
    }
    coeffFile.close();
    if(numCols == 2)
    std::system("python LIB/plot.py");
    if(numCols == 3)
    std::system("python LIB/plot1.py");
    std::cout << "Nhan phim '1' de thoat chuong trinh, Enter de tiep tuc..." << std::endl;
    std::string check;
    check = getch();
    if (check == "1")
        return 0;

    std::map<std::string, double> variables;
    App::loadVariables(filename, variables);
    App::inputVariables(variables);

    std::vector<double> values;
    App::saveVariablesToVector(variables, values);

    double result11 = 0.0;

    for (unsigned int i = 0; i < values.size(); ++i) {
        result11 += values[i] * Coefficients[i][0];
    }

    std::cout << "Ket qua du doan:" << std::endl;
    std::cout << result11 << std::endl;
// END APP
    return 0;
}
