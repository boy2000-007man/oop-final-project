/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-07-02 09:00
* Filename      : main.cpp
* Description   : 
*****************************************************************/
#include "SLT.h"
#include "test.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#define STD_IN
namespace CornerBlockList {
double random() {
    return (std::rand() % 999 + 1.0) / 1000;
}
}   // namespace CornerBlockList
using namespace std;
int main() {
    srand(time(NULL));

#ifdef STD_IN
    cin >> CornerBlockList::SLT::rects_;
#else
    ifstream fin("in.txt");
    fin >> CornerBlockList::SLT::rects_;
    fin.close();
#endif

    const double T_max = pow(CornerBlockList::SLT::rects_.size(), 2);
    const double T_min = 1;
    const double r = 0.9999;
    CornerBlockList::SLT slt;
    const double factor = T_max / slt.compArea();
    CornerBlockList::SLT slt_best = slt, slt_tmp = slt;
    for (double T = T_max, J1 = slt.compArea(), J_best = INT_MAX; T > T_min; T *= r) {
        slt.change(rand() % 3);
        double J2 = slt.compArea();
        double dE = (J1 - J2) * factor;

        if (exp(dE / T) < CornerBlockList::random()) {
            slt = slt_tmp;
        } else {
            slt_tmp = slt;
            J1 = J2;
            if (J_best > J1) {
                J_best = J1;
                slt_best = slt;
            }
        }
    }

    cout << "全局较优解：" << slt_best.compArea() << endl;
    //cout << CornerBlockList::SLT::rects_ << endl;
    CornerBlockList::findOverlap();

    return 0;
}
