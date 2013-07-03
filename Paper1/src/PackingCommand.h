#ifndef __SP_PACKINGCOMMAND_H__
#define __SP_PACKINGCOMMAND_H__
#include <vector>
#include <utility>
#include <ostream>

namespace RECTPACKING {
using namespace std;
class Layout;
class PackingCommand
{
public:
  PackingCommand() {}
  virtual ~PackingCommand() {}
  virtual void interpretToLayout(Layout &layout) = 0;
  virtual void dump(std::ostream &out) = 0;
  virtual void next(Layout &layout, const int &mode) = 0;
  virtual void getS(std::pair<std::vector<int>, std::vector<int> > &s) = 0;
  virtual void setS(const std::pair<std::vector<int>, std::vector<int> > &s) = 0;
};

std::ostream & operator << (std::ostream &out, PackingCommand &pcmd);

}

#endif	//__SP_PACKINGCOMMAND_H__
