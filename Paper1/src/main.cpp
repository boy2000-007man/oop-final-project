#include "SPPackingStrategy.h"
#include "SPPackingCommand.h"
#include "Layout.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
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
    vector<int> s1, s2;
    layout.getPackingStrategy()->getPackingCommand()->getS1(s1);
    layout.getPackingStrategy()->getPackingCommand()->getS2(s2);

    const double T_min = 100;
    const double r = 0.9;
    double T = 6000;
    while (T > T_min) {
        double J1 = layout.compArea();
        layout.getPackingStrategy()->nextPackingCommand();
        layout.getPackingStrategy()->compPackingLayout(layout);
        double J2 = layout.compArea();
        double dE = J1 - J2;

        if (dE < 0 && exp(dE / T) < sdk::random()) {
            layout.getPackingStrategy()->getPackingCommand()->setS1(s1);
            layout.getPackingStrategy()->getPackingCommand()->setS2(s2);
            T *= r;
        } else {
            layout.getPackingStrategy()->getPackingCommand()->getS1(s1);
            layout.getPackingStrategy()->getPackingCommand()->getS2(s2);
        }

    }

    layout.getPackingStrategy()->compPackingLayout(layout);
    cout << layout << endl;
    cout << layout.compArea() << endl;

    return 0;
}
