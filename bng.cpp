#include "sdk.h"
#include "bng.h"
#include <cassert>
#include <cmath>
using namespace std;

namespace Euclidean {
double dist(const Position &p1, const Position &p2) {
    const double dx = p1.x - p2.x,
                 dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}
}   // namespace Euclidean
namespace Manhattan {
int ::dist(const Position &p1, const Position &p2);
}   // namespace Manhattan
namespace Guo {
template <class T>
void del(std::vector<T> &v_t, const T t) {
    for (std::vector<T>::iterator it = v_t.begin(); it != v_t.end(); )
        if (*it == t)
            it = v_t.erase(it);
        else
            it++;
}
void merge(V_Face &face, const Edge e) {
    Face &f1 = face[e.f1];
    Face &f2 = face[e.f2];
    Face f();
    for (int i = 0; i < f1.e.size(); i++)
        if (f1.e[i] != e)
            f.e.push_back(f1.e[i]);
        else {
            int loc = 0;
            while (f2.e[loc] != e)
                loc++;
            for (int j = 1; j < f2.e.size(); j++)
                f.e.push_back(f2.e[(loc + j) % f2.e.size()]);
        }
    if (e.f1 > e.f2) {
        f1 = f;
        f2 = Face();
    } else {
        f2 = f;
        f1 = Face();
    }
    del(face, Face());
}
}   // namespace Guo
static bool operator != (const Position &p1, const Position &p2) {
    return !(p1 == p2);
}

namespace Euc = Euclidean;
namespace Man = Manhattan;

void BNG(const V_Position &vertex, V_Edge &edge, V_Face &face)  // You can modify variable names if you like
{
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size(); i++)
        assert(edge[i].size() > 0);
    assert(face.size() > 0);

    edge PART[vertex.size()][4];
    for (int i = 0; i < vertex.size(); i++)
        for (int j = 0; j < 4; j++)
            PART[i][j].u = -1;

    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++) {
            const Edge e = edge[i][j];
            const int r = judge_region_number(e.u, e.v);
            Edge &part = PART[i][r];

            using namespace Guo;
            #undef DEL_EDGE
            #define DEL_EDGE(e) \
                del(edge[e.u], e);\
                del(edge[e.v], e);\
                merge(face, e)
            if (part.u == -1) {
                part = e;
            } else if (Man::dis(e.u, e.v) > Man::dis(part.u, part.v)) {
                DEL_EDGE(e);
            } else if (Man::dis(e.u, e.v) < Man::dis(part.u, part.v)) {
                DEL_EDGE(part);
                part = e;
            } else if (Euc::dis(e.u, e.v) > Euc::dis(part.u, part.v)) {
                DEL_EDGE(e);
            } else {
                DEL_EDGE(part);
                part = e;
            }
            #undef DEL_EDGE
        }
}
