#include<iostream>
#include <cstdio>
#include "trans_matrix.h"
#include "print_screen.h"
#include "multiple_matrix.h"
#include "inverse_matrix.h"
#include "calcR2.h"
signed main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int m,n,m1,n1;
    std::cin >> m1 >> n1;
    // m1 : Số lượng đối tượng khảo sát
    // n1 : Số thuộc tính của đối tượng
    std::vector<std::vector<double>> A(n1,std::vector<double>(1));
    std::vector<std::vector<double>> B(n1,std::vector<double>(m1));
    double y_tb = 0;
    for(int i = 0 ; i < n1; i ++){
        for(int j = 0 ; j < 1 ; j ++){
            std::cin >> A[i][j];
            y_tb += A[i][j];
        }
    }
    y_tb /= n1; 
    for(int i = 0 ; i < n1; i ++){
        for(int j = 0 ; j < m1 ; j ++){
            std::cin >> B[i][j];
        }
    }
   
    
      std::vector<std::vector<double>> ans1 = MatrixMultiple::multiplyMatrices(MatrixTranspose::transposeMatrix(B),B);
      std::vector<std::vector<double>> ans2 = MatrixMultiple::multiplyMatrices(MatrixTranspose::transposeMatrix(B),A);
      std::vector<std::vector<double>> ans = MatrixMultiple::multiplyMatrices(InverseMatrix::inverseMatrix(ans1),ans2);
      std::vector<std::vector<double>> yans = MatrixMultiple::multiplyMatrices(B,ans);
      print::print_matrix(yans);
      double RR = R2::calc(A,yans,y_tb);
      std::cout << RR;  
}  