#ifndef __SDK_H__
#define __SDK_H__
#include "Rect.h"
#include <istream>
#include <vector>

namespace sdk {
class V_Rects {
    std::vector<Rect> m_rects;
    V_Rects(const V_Rects&);
public:
    friend std::istream& operator>>(std::istream &in, V_Rects &v_rects) {
        int num;
        in >> num;
        Rect tmp;
        for (int i = 0; i < num; i++) {
            in >> tmp.width >> tmp.heigh;
            m_rects.push_back(tmp);
        }
        return in;
    }
    std::vector<Rect>& getRects() {
        return m_rects;
    }
}   // class V_Rect
}   // namespace sdk
