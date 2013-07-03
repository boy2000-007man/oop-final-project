#ifndef __SLT_H__
#define __SLT_H__
#include "Rect.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
namespace CornerBlockList {
class SLT {
    std::vector<int> names_;
    enum Orientation {
        VERTICAL = 0, HORIZONAL = 1
    };
    std::vector<Orientation> orientations_;
    std::vector<int> T_junctions_;
    bool transformToFloorplan() {
        std::vector<int> H(1, 0), V(1, 0);
        rects_[names_[0]].set(0, 0);
        for (int i = 1; i < rects_.size(); i++) {
            int lx = 0, by = 0;
            switch (orientations_[i]) {
                case VERTICAL:
                    T_junctions_[i] %= H.size();
                    lx = rects_[names_[H[H.size() - 1 - T_junctions_[i]]]].left();
                    for (int j = 0; j <= T_junctions_[i]; j++) {
                        by = std::max(by, rects_[names_[H.back()]].top());
                        H.pop_back();
                    }
                    break;
                case HORIZONAL:
                    T_junctions_[i] %= V.size();
                    by = rects_[names_[V[V.size() - 1 - T_junctions_[i]]]].bottom();
                    for (int j = 0; j <= T_junctions_[i]; j++) {
                        lx = std::max(lx, rects_[names_[V.back()]].right());
                        V.pop_back();
                    }
                    break;
            }
            rects_[names_[i]].set(lx, by);
            H.push_back(i);
            V.push_back(i);
        }
        return true;
    }
public:
    static Rects rects_;
    SLT() {
        for (int i = 0; i < rects_.size(); i++) {
            names_.push_back(i);
            orientations_.push_back(rand() % 2 ? VERTICAL : HORIZONAL);
            T_junctions_.push_back(rand());
        }
        random_shuffle(names_.begin(), names_.end());
    }
    SLT(const SLT &slt) {
        *this = slt;
    }
    ~SLT() {
    }
    SLT& operator=(const SLT &slt) {
        if (this == &slt)
            return *this;
        names_ = slt.names_;
        orientations_ = slt.orientations_;
        T_junctions_ = slt.T_junctions_;
        return *this;
    }
    double compArea() {
        while (!transformToFloorplan());
        int rx = 0, ty = 0;
        for (int i = 0; i < rects_.size(); i++) {
            if (rx < rects_[i].right())
                rx = rects_[i].right();
            if (ty < rects_[i].top())
                ty = rects_[i].top();
        }
        return rx * ty;
    }
    void change(const int &mode) {
        const int size = rects_.size();
        switch (mode) {
            case 0: {
                        const int r1 = rand() % size;
                        int r2;
                        while ((r2 = rand() % size) == r1);
                        int tmp = names_[r1];
                        names_[r1] = names_[r2];
                        names_[r2] = tmp;
                    }
                    break;
            case 1: {
                        Orientation &ori = orientations_[rand() % size];
                        ori = (ori == VERTICAL ? HORIZONAL : VERTICAL);
                    }
                    break;
            case 2: {
                        T_junctions_[rand() % size] = rand();
                    }
                    break;
            case 3: {
                        rects_[rand() % size].transpose();
                    }
                    break;
        }
    }
};  // class SLT
Rects SLT::rects_;
}   // namespace CornerBlockList
#endif  // __SLT_H__
