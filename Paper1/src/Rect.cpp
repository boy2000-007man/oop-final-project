#include <iostream>
#include "Rect.h"

namespace RECTPACKING {
using namespace std;

ostream & operator << (ostream &out, Rect &r)
{
  return out << "[" << r.left() << ", " << r.bottom() << "]"
      "-[" << r.right() << ", " << r.top() << "]";
}

}
