#include "SPPackingCommand.h"
#include "Layout.h"
#include "Rect.h"
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <cassert>
#include <climits>

namespace RECTPACKING {
using namespace std;
static int Link(vector<Rect> &rects, vector<vector<int> > &rely, const int &num, const bool &hor) {
    if (hor) {
        if (rects[num].lb.x != -1)
            return rects[num].right();
        rects[num].lb.x = 0;
        for (int i = 0; i < rely[num].size(); i++)
            if (rects[num].lb.x < Link(rects, rely, rely[num][i], hor))
                rects[num].lb.x = Link(rects, rely, rely[num][i], hor);
        return rects[num].right();
    } else {
        if (rects[num].lb.y != -1)
            return rects[num].top();
        rects[num].lb.y = 0;
        for (int i = 0; i < rely[num].size(); i++)
            if (rects[num].lb.y < Link(rects, rely, rely[num][i], hor))
                rects[num].lb.y = Link(rects, rely, rely[num][i], hor);
        return rects[num].top();
    }
}
static void OneDirectionPacking(vector<pair<int, int> > &cons, Layout &layout, bool hor)
{
  vector<Rect> &rects = layout.getRects();
  const int rectNum = rects.size();

  vector<vector<int> > rely(rectNum, vector<int>());
  for (int i = 0; i < cons.size(); i++)
      rely[cons[i].second].push_back(cons[i].first);

  if (hor)
    for (int i = 0; i < rectNum; i++)
        rects[i].lb.x = -1;
  else
    for (int i = 0; i < rectNum; i++)
        rects[i].lb.y = -1;

  for (int i = 0; i < rectNum; i++)
      Link(rects, rely, i, hor);
}
void LongestGraphPacking(vector<pair<int, int> > &horCons, vector<pair<int, int> > &verCons, Layout &layout)
{
  #ifdef __OUT__
  cout << "In LongestGraphPacking " << endl;
  #endif
  bool hor = true;
  #ifdef __OUT__
  cout << "========== horizontal ==========" << endl;
  #endif
  OneDirectionPacking(horCons, layout, hor);
  hor = false;
  #ifdef __OUT__
  cout << "========== vertical ==========" << endl;
  #endif
  OneDirectionPacking(verCons, layout, hor);
}
}
