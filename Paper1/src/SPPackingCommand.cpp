#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include "SPPackingCommand.h"
#include "GraphPacking.h"
#include "Layout.h"
#include "Rect.h"

namespace RECTPACKING {
using namespace std;

void SPPackingCommand::interpretToLayout(Layout &layout)
{
  #ifdef __OUT__
  cout << "In SPPackingCommand::interpretToLayout" << endl;
  #endif
  //build position map
  int length = m_s1.size();
  vector<int> s1(length, 0), s2(length, 0);
  for (int i = 0; i < length; ++ i)
  {
    s1[m_s1[i]] = i;
    s2[m_s2[i]] = i;
  }
  //compute the horizontal constraint pairs and vertical constraint pairs
  vector<pair<int, int> > horCons;
  vector<pair<int, int> > verCons;
  for (int i = 0; i < length; ++ i)
  {
    for (int j = 0; j < length; ++ j)
    {
      if (i != j)
      {
        //bb->left: i is to the left of j
        if (s1[i] < s1[j] && s2[i] < s2[j])
        {
          horCons.push_back(make_pair(i, j));
        }
        //ab->below: i is below j
        if (s1[i] > s1[j] && s2[i] < s2[j])
        {
          verCons.push_back(make_pair(i, j));
        }
      }
    }
  }
  //packing by the longest path algorithm
  LongestGraphPacking(horCons, verCons, layout);
}

void SPPackingCommand::next(Layout &layout, const int &mode)
{
    const int size = m_s1.size();
    switch (mode) {
        case 0: {
                    const int i1 = rand() % size;
                    int i2;
                    while ((i2 = rand() % size) == i1);
                    int tmp = m_s1[i1];
                    m_s1[i1] = m_s1[i2];
                    m_s1[i2] = tmp;
                }
            break;
        case 1: {
                    const int i1 = rand() % size;
                    int i2;
                    while ((i2 = rand() % size) == i1);
                    vector<Rect> &rects = layout.getRects();
                    Rect tmp = rects[i1];
                    rects[i1] = rects[i2];
                    rects[i2] = tmp;
                }
            break;
        case 2: {
                    Rect &rect = layout.getRect(rand() % size);
                    int tmp = rect.width;
                    rect.width = rect.height;
                    rect.height = tmp;
                }
            break;
    }
}

void SPPackingCommand::dump(ostream &out)
{
  out << "Sequence Pair:";
  for (int i = 0; i < (int)m_s1.size(); ++ i)
  {
    out << " " << m_s1[i];
  }
  out << ",";
  for (int i = 0; i < (int)m_s2.size(); ++ i)
  {
    out << " " << m_s2[i];
  }
  out << endl;
}

}
