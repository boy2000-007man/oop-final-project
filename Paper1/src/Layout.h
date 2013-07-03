#ifndef __SP_LAYOUT_H__
#define __SP_LAYOUT_H__
#include <iostream>
#include <vector>
#include <utility>
#include "Rect.h"
#include "PackingStrategy.h"

namespace RECTPACKING {
class PackingStrategy;
class Layout
{
public:
  Layout():m_pStrategy(0) {}
  ~Layout() {
    if (m_pStrategy)
      delete m_pStrategy;
  }
  void addRect(Rect &r) { m_rects.push_back(r); }
  std::vector<Rect> &getRects() { return m_rects; }
  int getRectNum() { return m_rects.size(); }
  Rect &getRect(int i) { return m_rects[i]; }
  PackingStrategy *getPackingStrategy() { return m_pStrategy; }
  void setPackingStrategy(PackingStrategy *s) {
    if (m_pStrategy)
      delete m_pStrategy;
    m_pStrategy = s;
  }
  void compConstraints(std::vector<std::pair<int, int> > &horCons, std::vector<std::pair<int, int> > &verCons);
  friend std::ostream & operator << (std::ostream &out, Layout &l);
  friend std::istream & operator >> (std::istream &in, Layout &l);
  double compArea();
  double rectsArea() {
      double rects_area = 0;
      for (int i = 0; i < m_rects.size(); i++)
          rects_area += m_rects[i].Area();
      return rects_area;
  }

private:
  std::vector<Rect> m_rects;
  PackingStrategy *m_pStrategy;
};

}

#endif	//__SP_LAYOUT_H__
