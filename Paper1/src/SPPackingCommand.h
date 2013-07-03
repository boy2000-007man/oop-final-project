#ifndef __SP_SPPACKINGCOMMAND_H__
#define __SP_SPPACKINGCOMMAND_H__
#include "PackingCommand.h"

namespace RECTPACKING {

class SPPackingCommand : public PackingCommand
{
public:
  SPPackingCommand(std::vector<int> &s1, std::vector<int> &s2):PackingCommand() {
    m_s1 = s1;
    m_s2 = s2;
  }
  ~SPPackingCommand() {}
  void interpretToLayout(Layout &layout);
  void dump(std::ostream &out);
  void next(Layout &layout, const int &mode);
  void getS(std::pair<std::vector<int>, std::vector<int> > &s) {
      s.first = m_s1;
      s.second = m_s2;
  }
  void setS(const std::pair<std::vector<int>, std::vector<int> > &s) {
      m_s1 = s.first;
      m_s2 = s.second;
  }

protected:
  std::vector<int> m_s1;
  std::vector<int> m_s2;
};

}

#endif	//__SP_SPPACKINGCOMMAND_H__
