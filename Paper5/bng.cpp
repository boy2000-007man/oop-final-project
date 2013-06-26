/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-06-26 11:03
* Filename      : bng.cpp
* Description   : 
*****************************************************************/
#include "sdk.h"
#include "bng.h"
#ifdef TEST
#include <cassert>
#endif
#include <cmath>
using namespace std;

namespace Guo {
void del(vector<Edge> &v_t, const Edge t) {         // delete the specific edge in the vector
    for (vector<Edge>::iterator it = v_t.begin(); it != v_t.end(); )
        if (*it == t)
            it = v_t.erase(it);
        else
            it++;
}
void clean(V_Face &face) {                          // delete empty face in V_Face
    for (V_Face::iterator it = face.begin(); it != face.end(); )
        if (it->e.size() == 0)
            it = face.erase(it);
        else
            it++;
}
void merge(V_Face &face, const Edge e) {            // merge face f1 && f2 of the deleted edge
    Face &f1 = face[e.f1];
    Face &f2 = face[e.f2];
    Face f;
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
    clean(face);
}
}   // namespace Guo

void BNG(const V_Position &vertex, V_Edge &edge, V_Face &face)  // You can modify variable names if you like
{
    #ifdef TEST
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size(); i++)
        assert(edge[i].size() > 0);
    assert(face.size() > 0);
    #endif

    Edge PART[vertex.size()][4];
    for (int i = 0; i < vertex.size(); i++)
        for (int j = 0; j < 4; j++)
            PART[i][j].u = -1;

    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++) {
            const Edge e = edge[i][j];
            const Position &e_u = vertex[e.u];
            const Position &e_v = vertex[e.v];
            const int r = judge_region_number(e_u, e_v);
            Edge &part = PART[i][r];
            const Position &p_u = vertex[part.u];
            const Position &p_v = vertex[part.v];

            #ifndef NULL
            #define NULL 0
            #endif
            #undef DEL_EDGE
            #define DEL_EDGE(e) \
                if (e.link != NULL) \
                    e.link->link = NULL; \
                Guo::del(edge[e.u], e);\
                Guo::merge(face, e)
            if (part.u == -1) {
                part = e;
            } else if (Man::dist(e_u, e_v) > Man::dist(p_u, p_v)) {
                DEL_EDGE(e);
            } else if (Man::dist(e_u, e_v) < Man::dist(p_u, p_v)) {
                DEL_EDGE(part);
                part = e;
            } else if (Euc::dist(e_u, e_v) > Euc::dist(p_u, p_v)) {
                DEL_EDGE(e);
            } else {
                DEL_EDGE(part);
                part = e;
            }
            #undef DEL_EDGE
        }
}
