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
  virtual void next() = 0;
  virtual void getS1(std::vector<int> &s1) = 0;
  virtual void getS2(std::vector<int> &s2) = 0;
  virtual void setS1(const std::vector<int> &s1) = 0;
  virtual void setS2(const std::vector<int> &s2) = 0;
};

std::ostream & operator << (std::ostream &out, PackingCommand &pcmd);

}

#endif	//__SP_PACKINGCOMMAND_H__
