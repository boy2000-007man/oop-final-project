#include "GraphPacking.h"
#include "sdk.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

double random() {
    return (rand() % 999 + 1.0) / 1000;
}

int main() {
    srand(time(NULL));

    ifstream in("in.txt");
    sdk::V_Rects v_rects;
    in >> v_rects;
    in.close();

    RECTPACKING::Layout layout;
    layout.getRects() = v_rects.getRects();
    RECTPACKING::SPPackingStrategy spps;
    spps.initialPacking(layout);
    RECTPACKING::SPPackingCommand *sppc = spps.getPackingCommand();
    vectory<int> s1, s2;
    sppc->getS1(s1);
    sppc->getS2(s2);

    const double T_min = 100;
    const double r = 0.9;
    double T = 6000;
    while (T > T_min) {
        double J1 = layout.compArea();
        spps.nextPackingCommand();
        spps.compPackingLayout(layout);
        double J2 = layout.compArea();
        double dE = J1 - J2;

        if (dE < 0 && exp(dE / T) < random()) {
            sppc->setS1(s1);
            sppc->setS2(s2);
        } else {
            sppc->getS1(s1);
            sppc->getS2(s2);
        }

        T *= r;
    }

    spps.compPackingLayout(layout);
    cout << layout << endl;

    return 0;
}
