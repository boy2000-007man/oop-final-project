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
        std::vector<std::vector<int> > h(1, std::vector<int>()), v(1, std::vector<int>());
        for (int i = 1; i < rects_.size(); i++) {
            std::vector<int> tmp_h, tmp_v;
            switch (orientations_[i]) {
                case VERTICAL:
                    for (int j = 0; j <= T_junctions_[i]; j++)
                        if (!H.empty()) {
                            tmp_h.push_back(H.back());
                            H.pop_back();
                        } else {
                            T_junctions_[i] /= 2;
                            return false;
                        }
                    tmp_v = v[tmp_h.back()];
                    break;
                case HORIZONAL:
                    for (int j = 0; j <= T_junctions_[i]; j++)
                        if (!V.empty()) {
                            tmp_v.push_back(V.back());
                            V.pop_back();
                        } else {
                            T_junctions_[i] /= 2;
                            return false;
                        }
                    tmp_h = h[tmp_v.back()];
                    break;
            }
            h.push_back(tmp_h);
            v.push_back(tmp_v);
            H.push_back(i);
            V.push_back(i);
        }
        for (int i = 0; i < rects_.size(); i++) {
            int lx = 0, by = 0;
            for (int j = 0; j < v[i].size(); j++)
                if (lx < rects_[names_[v[i][j]]].right())
                    lx = rects_[names_[v[i][j]]].right();
            for (int j = 0; j < h[i].size(); j++)
                if (by < rects_[names_[h[i][j]]].top())
                    by = rects_[names_[h[i][j]]].top();
            rects_[names_[i]].set(lx, by);
        }
        return true;
    }
public:
    static Rects rects_;
    SLT() {
        for (int i = 0; i < rects_.size(); i++) {
            names_.push_back(i);
            orientations_.push_back(rand() % 2 ? VERTICAL : HORIZONAL);
            T_junctions_.push_back(rand() % 2);
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
                        const int r = rand() % size;
                        switch (orientations_[r]) {
                            case VERTICAL:
                                orientations_[r] = HORIZONAL;
                                break;
                            case HORIZONAL:
                                orientations_[r] = VERTICAL;
                                break;
                        }
                    }
                    break;
            case 2: {
                        const int r = rand() % size;
                        if (T_junctions_[r] == 0)
                            T_junctions_[r]++;
                        else
                            T_junctions_[r] += (rand() % 2 ? 1 : -1);
                    }
                    break;
        }
    }
};  // class SLT
Rects SLT::rects_;
}   // namespace CornerBlockList
#endif  // __SLT_H__
