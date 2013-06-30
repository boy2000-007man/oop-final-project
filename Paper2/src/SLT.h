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
        names_ = slt.names_;
        orientations_ = slt.orientations_;
        T_junctions_ = slt.T_junctions_;
    }
    ~SLT() {
        delete packing_strategy_;
    }
    PackingStrategy* getPackingStrategy() const {
        return packing_strategy_;
    }
};  // class SLT
}   // namespace CornerBlockList
#endif
