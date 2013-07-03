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
#define STD_IN
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

    const double T_max = pow(layout.getRectNum(), 2);
    const double T_min = 1;
    const double r = 0.99;
    const double factor = T_max / layout.rectsArea();
    const int T_Num = layout.getRectNum();
    for (double T = T_max, J1 = layout.compArea(), J_best = INT_MAX; T > T_min; T *= r) {
        for (int i = 0; i < T_Num; i++) {
            /*int mode = rand() % layout.getRectNum();
            if (mode == -1)
                mode = (T / T_max > sdk::random()) ? 1 : 2;
            else
                mode = 0;*/
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

    layout.getPackingStrategy()->getPackingCommand()->setS(s_best);
    layout.getPackingStrategy()->compPackingLayout(layout);
//    cout << layout << endl;
    cout << "全局较优解：" << layout.rectsArea() / layout.compArea()
        << "[" << layout.rectsArea() << "/" << layout.compArea() << "]" << endl;
    sdk::findOverlap(layout);

    return 0;
}
