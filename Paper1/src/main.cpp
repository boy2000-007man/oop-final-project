#include "GraphPacking.h"
#include "sdk.h"
#include <fstream>
using namespace std;

int main() {
    sdk::V_Rects v_rects;
    ifstream in("in.txt");
    in >> v_rects;

    RECTPACKING::Layout layout;
    layout.getRects() = v_rects.getRects();

