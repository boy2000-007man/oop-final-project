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
#include "test.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#define STD_IN  // remove this to read from "in.txt"
using namespace std;
namespace sdk {
double random() {
    return (std::rand() % 999 + 1.0) / 1000;
}
}   // namespace sdk
int main() {
    srand(time(NULL));

    RECTPACKING::Layout layout;
#ifdef STD_IN
    cin >> layout;
#else
    ifstream fin("in.txt");
    fin >> layout;
    fin.close();
#endif

    layout.setPackingStrategy(new RECTPACKING::SPPackingStrategy);
    layout.getPackingStrategy()->initialPacking(layout);
    pair<vector<int>, vector<int> > s_best;
    layout.getPackingStrategy()->getPackingCommand()->getS(s_best);
    pair<vector<int>, vector<int> > s = s_best;

    // start simulated annealing
    const double T_max = pow(layout.getRectNum(), 2);
    const double T_min = 1;
    const double r = 0.99;
    const double factor = pow(layout.getRectNum(), 2.5) / layout.rectsArea();
    const int T_Num = layout.getRectNum();
    for (double T = T_max, J1 = layout.compArea(), J_best = INT_MAX; T > T_min; T *= r) {
        if (rand() % (int)T_max == 0)
            layout.getPackingStrategy()->nextPackingCommand(layout, (T / T_max > sdk::random()) ? 1 : 2);
        for (int i = 0; i < T_Num; i++) {
            layout.getPackingStrategy()->nextPackingCommand(layout, 0);
            layout.getPackingStrategy()->compPackingLayout(layout);
            double J2 = layout.compArea();
            double dE = (J1 - J2) * factor;

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
    }
    // finish simulated annealing

    layout.getPackingStrategy()->getPackingCommand()->setS(s_best);
    layout.getPackingStrategy()->compPackingLayout(layout);
    cout << "全局较优解：" << layout.rectsArea() / layout.compArea()
        << "[" << layout.rectsArea() << "/" << layout.compArea() << "]" << endl;
    // test if exist overlaps
    sdk::findOverlap(layout);
    // cout << layout << endl;  // this will show the rectangles' position

    return 0;
}
