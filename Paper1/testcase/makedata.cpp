#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << "       {num:2~..} {width_max:1~..} {height_max:1~..}" << endl;
        return 0;
    }

    const int num = atoi(argv[1]);
    const int width_max = atoi(argv[2]);
    const int height_max = atoi(argv[3]);
    assert(num > 1);
    assert(width_max > 0);
    assert(height_max > 0);

    cout << num << endl;
    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        int width = rand() % width_max + 1;
        int height = rand() % height_max + 1;
        cout << width << " " << height << endl;
    }

    return 0;
}
