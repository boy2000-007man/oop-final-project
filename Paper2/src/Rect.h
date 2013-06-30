#ifndef __SP_RECT_H__
#define __SP_RECT_H__
#include "Point.h"
#include <iostream>
#include <vector>
namespace CornerBlockList {
struct Rect {
    int left() const    { return lb.x;          }
    int right() const   { return lb.x+width;    }
    int bottom() const  { return lb.y;          }
    int top() const     { return lb.y+height;   }
    friend std::istream& operator>>(std::istream &in, Rect &r) {
        return in >> r.width >> r.height;
    }
    friend std::ostream& operator<<(std::ostream &out, const Rect &r) {
        return out << "[" << r.left() << ", " << r.bottom() << "]"
            "-[" << r.right() << ", " << r.top() << "]";
    }
private:
    int width;
    int height;
    Point lb;
};  // struct Rect
typedef vector<Rect> V_Rect;
class Rects {
    V_Rect rects_;
public:
    Rects(std::istream &in) {
        int num;
        in >> num;
        Rect r;
        for (int i = 0; i < num; i++) {
            in >> r;
            rects_.push_back(r);
        }
    }
    friend std::ostream& operator<<(std::ostream &out, Rects &r) {
        for (int i = 0; i < rects_.size(); i++)
            out << rects_[i] << endl;
        return out;
    }
    Rect& operator[](const int &n) {
        return rects_[n];
    }
}   // namespace CornerBlockList
#endif	//__SP_RECT_H__
