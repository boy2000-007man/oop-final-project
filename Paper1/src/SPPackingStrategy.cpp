#include <iostream>
#include <algorithm>
#include "SPPackingStrategy.h"
#include "SPPackingCommand.h"
#include "Layout.h"

using namespace std;
namespace RECTPACKING {

void SPPackingStrategy::initialPacking(Layout &layout)
{
  int rectNum = layout.getRectNum();
  if (rectNum < 2)
      return;

  vector<int> s;
  for (int i = 0; i < rectNum; ++ i)
    s.push_back(i);
  random_shuffle(s.begin(), s.end());
  SPPackingCommand *spcmd = new SPPackingCommand(s, s);
  #ifdef __OUT__
  cout << "Packing Command in SPPackingStrategy::initialPacking" << endl;
  cout << *spcmd;
  #endif

  setPackingCommand(spcmd);
  spcmd->interpretToLayout(layout);
  #ifdef __OUT__
  cout << "Layout after SPPackingStrategy::initialPacking" << endl;
  cout << layout;
  #endif
}

void SPPackingStrategy::nextPackingCommand(Layout &layout, const int &mode)
{
  if (m_pCommand)
  {
    m_pCommand->next(layout, mode);
  }
}

void SPPackingStrategy::compPackingLayout(Layout &layout)
{
  if (m_pCommand)
    m_pCommand->interpretToLayout(layout);
}

}
