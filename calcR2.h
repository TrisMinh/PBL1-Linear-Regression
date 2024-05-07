
#ifndef R2_H
#define R2_H
#include <iostream>
#include <vector> 
namespace R2 {
    double calc(std::vector<std::vector<double>>& y , std::vector<std::vector<double>>& y1, double y_tb){
        double r = 1;
        double res = 0;
        double tot = 0;
        for(int i = 0 ; i < y.size() ; i ++){
            res += (y[i][0] - y1[i][0]) * (y[i][0] - y1[i][0]);
            tot += (y[i][0] - y_tb) * (y[i][0] - y_tb);
           // std::cout << y[i][0] << std::endl;
        }
        r -= res / tot;
        return r;
    }
}
#endif 
