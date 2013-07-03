#ifndef __TEST_H__
#define __TEST_H__
#include "Layout.h"
#include "Rect.h"
#include <vector>
#include <iostream>
#include <cmath>
namespace sdk {
int findOverlap(RECTPACKING::Layout &layout) {
    std::vector<RECTPACKING::Rect> rects = layout.getRects();
    int cover = 0;
    for (int i = 0; i < rects.size(); i++)
        for (int j = i + 1; j < rects.size(); j++) {
            RECTPACKING::Rect &r1 = rects[i];
            RECTPACKING::Rect &r2 = rects[j];
            const int r1_x2 = r1.left() + r1.right();
            const int r1_y2 = r1.bottom() + r1.top();
            const int r2_x2 = r2.left() + r2.right();
            const int r2_y2 = r2.bottom() + r2.top();
            if (std::abs(r1_x2 - r2_x2) < r1.width + r2.width && std::abs(r1_y2 - r2_y2) < r1.height + r2.height)
                std::cerr << "Cover" << cover++ << ": "
                    "Rectangle" << i << ":" << r1 << " overlap "
                    "Rectangle" << j << ":" << r2 << std::endl;
        }
    if (cover == 0)
        std::cerr << "No overlap detected." << std::endl;
    return cover;
}
}   // namespace sdk
#endif
