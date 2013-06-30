#ifndef __TEST_H__
#define __TEST_H__
#include "Layout.h"
#include "Rect.h"
#include "PackingCommand.h"
#include "PackingStrategy.h"
#include <vector>
#include <iostream>
namespace sdk {
void findOverlap(RECTPACKING::Layout &layout) {
    std::vector<RECTPACKING::Rect> rects = layout.getRects();
    for (int i = 0; i < rects.size(); i++)
        for (int j = 0; j < rects.size(); j++) {
            if (i == j)
                continue;
            RECTPACKING::Rect &r1 = rects[i];
            RECTPACKING::Rect &r2 = rects[j];
            if (r2.left() < r1.right() && r1.right()<= r2.right())
                if (r1.bottom() < r2.top() && r1.top() > r2.bottom()) {
                    std::cerr << "Rectangle" << i << ":[" << r1.left() << ", " << r1.bottom() << "]-[" << r1.right() << ", " << r1.top() << "]" << std::endl
                        << "Rectangle" << j << ":[" << r2.left() << ", " << r2.bottom() << "]-[" << r2.right() << ", " << r2.top() << "]" << std::endl
                        << "Overlap." << std::endl;
                    return ;
                }
        }
    std::cerr << "No overlap detected." << std::endl;
}
}   // namespace sdk
#endif
