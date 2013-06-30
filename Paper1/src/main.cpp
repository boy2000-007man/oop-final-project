/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-06-28 22:29
* Filename      : main.cpp
* Description   : 
*****************************************************************/
#include "SPPackingStrategy.h"
#include "SPPackingCommand.h"
#include "Layout.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
using namespace std;
namespace sdk {
double random() {
    return (std::rand() % 999 + 1.0) / 1000;
}
}   // namespace sdk
int main() {
    srand(time(NULL));

    ifstream in("in.txt");
    RECTPACKING::Layout layout;
    in >> layout;
    in.close();

    layout.setPackingStrategy(new RECTPACKING::SPPackingStrategy);
    layout.getPackingStrategy()->initialPacking(layout);
    pair<vector<int>, vector<int> > s_best;
    layout.getPackingStrategy()->getPackingCommand()->getS(s_best);

    const double T_max = pow(layout.getRectNum(), 2);
    const double T_min = 1;
    const double r = 0.99;
    const double avr_size = layout.compArea() / layout.getRectNum() / 50;
    pair<vector<int>, vector<int> > s = s_best;
    for (double T = T_max, J1 = layout.compArea(), J2, J_best = INT_MAX, dE; T > T_min; T *= r) {
        layout.getPackingStrategy()->nextPackingCommand();
        layout.getPackingStrategy()->compPackingLayout(layout);
        J2 = layout.compArea();
        dE = (J1 - J2) / avr_size;

        if (exp(dE / T) < sdk::random()) {
            layout.getPackingStrategy()->getPackingCommand()->setS(s);
        } else {
            layout.getPackingStrategy()->getPackingCommand()->getS(s);
            J1 = J2;
            if (J_best > J1) {
                J_best = J1;
                s_best = s;
            }
        }
    }

    /*cout << "最近局部较优解：" << endl;
    layout.getPackingStrategy()->compPackingLayout(layout);
    cout << layout << endl;
    cout << layout.compArea() << endl;

    cout << "全局较优解：" << endl;*/
    layout.getPackingStrategy()->getPackingCommand()->setS(s_best);
    layout.getPackingStrategy()->compPackingLayout(layout);
//    cout << layout << endl;
    cout << layout.compArea() << endl;

    return 0;
}
