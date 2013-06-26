#include "sdk.h"
#include "bng.h"
#include <cmath>
#include <algorithm>
#include <cassert>
#define TEST
using namespace std;

#include <iostream>
void swap(Edge &x, Edge &y)
{
	swap(x.u, y.u);
	swap(x.v, y.v);
	swap(x.f1, y.f1);
	swap(x.f2, y.f2);
	swap(x.len, y.len);
	Edge *ret = x.link;
	x.link = y.link;
	y.link = ret;
}
namespace Guo {
void del(vector<Edge> &v_t, const Edge t) {
    for (vector<Edge>::iterator it = v_t.begin(); it != v_t.end(); )
        if (*it == t) {
			Edge ooo;
			(*((*(v_t.end()-1)).link)).link = &(*it);
			swap(*it, *(v_t.end()-1));
			v_t.erase(v_t.end()-1);
		}
        else
            it++;
}
int min(const int &a, const int &b) {
    return a < b ? a : b;
}
int max(const int &a, const int &b) {
    return a > b ? a : b;
}
void merge(V_Face &face, const Edge e) {
    if (e.f1 == e.f2) {                     // if f1 == f2
        if (e.f1 != face.size() - 1)        // if f1 is not the out face, then del the edge in f1
            del(face[e.f1].e, e);
        return ;
    }
    Face &f_min = face[min(e.f1, e.f2)];
    Face &f_max = face[max(e.f1, e.f2)];
    Face f;
    for (int i = 0; i < f_min.e.size(); i++)
        if (f_min.e[i] != e)
            f.e.push_back(f_min.e[i]);
        else {
            int loc = 0;
            if (f_max.e.size() != 0)
                while (f_max.e[loc] != e)
                    loc++;
            for (int j = 1; j < f_max.e.size(); j++)
                f.e.push_back(f_max.e[(loc + j) % f_max.e.size()]);
        }
    f_min = Face();
    if (max(e.f1, e.f2) == face.size() - 1)
        f_max = Face();
    else
        f_max = f;
	for (V_Face::iterator it = face.begin(); it != face.end() - 1; it++) // avoid delete the out face
		if ((*it).e.size() == 0) {
			face.erase(it);
			break;
		}
}
}   // namespace Guo

void BNG(const V_Position &vertex, V_Edge &edge, V_Face &face)  // You can modify variable names if you like
{
#ifdef TEST
	cerr << "assert vertex, edge and face..." << endl;
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size(); i++)
        assert(edge[i].size() > 0);
    assert(face.size() > 0);
	cerr << "assert end!" << endl;
#endif

    Edge PART[vertex.size()][4];
#ifdef TEST
	cerr << "size of PART[][4]" << sizeof(PART)/sizeof(Edge) << endl;
#endif
    for (int i = 0; i < vertex.size(); i++)
        for (int j = 0; j < 4; j++)
            PART[i][j].u = -1;

#ifdef TEST
	cerr << "Making BNG..." << endl;
#endif
    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++) {
#ifdef TEST
            cerr << "Start value init..." << endl;
#endif
            const Edge e = edge[i][j];
            const Position &e_u = vertex[e.u];
            const Position &e_v = vertex[e.v];
            const int r = judge_region_number(e_u, e_v);
            Edge &part = PART[i][r];
            const Position &p_u = vertex[part.u];
            const Position &p_v = vertex[part.v];
#ifdef TEST
            cerr << "value init finished." << endl;
#endif

            #undef DEL_EDGE
            #define DEL_EDGE(e) \
                Guo::del(edge[e.u], e);\
                Guo::del(edge[e.v], e);\
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
