#ifndef __SDK_H__
#define __SDK_H__
#include "Rect.h"
#include <istream>
#include <vector>
#include <cstdlib>

namespace sdk {
class V_Rects {
    std::vector<RECTPACKING::Rect> m_rects;
    V_Rects(const V_Rects&);
public:
    V_Rects() {}
    friend std::istream& operator>>(std::istream &in, V_Rects &v_rects) {
        int num;
        in >> num;
        RECTPACKING::Rect tmp;
        for (int i = 0; i < num; i++) {
            in >> tmp.width >> tmp.height;
            v_rects.m_rects.push_back(tmp);
        }
        return in;
    }
    std::vector<RECTPACKING::Rect>& getRects() {
        return m_rects;
    }
};  // class V_Rect
double random() {
    return (std::rand() % 999 + 1.0) / 1000;
}
}   // namespace sdk
#endif
