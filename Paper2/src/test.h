#ifndef __TEST_H__
#define __TEST_H__
#include "SLT.h"
#include "Rect.h"
#include <iostream>
#include <cmath>
namespace CornerBlockList {
int findOverlap() {
    int cover = 0;
    for (int i = 0; i < SLT::rects_.size(); i++)
        for (int j = i + 1; j < SLT::rects_.size(); j++) {
            const Rect &r1 = SLT::rects_[i];
            const Rect &r2 = SLT::rects_[j];
            const int r1_x2 = r1.left() + r1.right();
            const int r1_y2 = r1.bottom() + r1.top();
            const int r2_x2 = r2.left() + r2.right();
            const int r2_y2 = r2.bottom() + r2.top();
            if (std::abs(r1_x2 - r2_x2) < r1.getWidth() + r2.getWidth() && std::abs(r1_y2 - r2_y2) < r1.getHeight() + r2.getHeight())
                std::cerr << "Cover" << cover++ << ": "
                    "Rectangle" << i << ":" << r1 << " overlap "
                    "Rectangle" << j << ":" << r2 << std::endl;
        }
    if (cover == 0)
        std::cerr << "No overlap detected." << std::endl;
    return cover;
}
}   // namespace CornerBlockList
#endif  // __TEST_H__
