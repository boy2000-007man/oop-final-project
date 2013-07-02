#ifndef __SP_RECT_H__
#define __SP_RECT_H__
#include <iostream>
#include <vector>
namespace CornerBlockList {
struct Point {
    int x, y;
    Point(int i = 0, int j = 0) : x(i), y(j) {
    }
};
struct Rect {
    int left() const    { return lb.x;          }
    int right() const   { return lb.x+width;    }
    int bottom() const  { return lb.y;          }
    int top() const     { return lb.y+height;   }
    int getWidth() const   { return width;         }
    int getHeight() const  { return height;        }
    void set(const int &x, const int &y) {
        lb = Point(x, y);
    }
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
typedef std::vector<Rect> V_Rect;
class Rects {
    V_Rect rects_;
public:
    Rect& operator[](const int &n) {
        return rects_[n];
    }
    friend std::istream& operator>>(std::istream &in, Rects &r) {
        int num;
        in >> num;
        Rect rect;
        for (int i = 0; i < num; i++) {
            in >> rect;
            r.rects_.push_back(rect);
        }
    }
    friend std::ostream& operator<<(std::ostream &out, Rects &r) {
        for (int i = 0; i < r.rects_.size(); i++)
            out << r.rects_[i] << std::endl;
        return out;
    }
    int size() {
        return rects_.size();
    }
};  // class Rects
}   // namespace CornerBlockList
#endif	//__SP_RECT_H__
