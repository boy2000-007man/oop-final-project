#ifndef __SLT_H__
#define __SLT_H__
#include <list>
namespace CornerBlockList {
class SLT {
    std::list<int> names_;
    std::list<bool> orientations_;
    std::list<int> T_junctions_;
    PackingStrategy *packing_strategy_;
public:
    SLT(const PackingStrategy *ps) {
        packing_stragety_ = ps;
    }
    SLT(const SLT &slt) : packing_strategy_(NULL) {
        *this = slt;
    }
    ~SLT() {
        delete packing_strategy_;
    }
    PackingStrategy* getPackingStrategy() const {
        return packing_strategy_;
    }
    SLT& operator=(const SLT &slt) {
        if (this == &slt)
            return *this;
        names_ = slt.names_;
        orientations_ = slt.orientations_;
        T_junctions_ = slt.T_junctions_;
        return *this;
    }
};  // class SLT
}   // namespace CornerBlockList
#endif
