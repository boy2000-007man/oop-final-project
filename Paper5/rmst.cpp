/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-06-26 11:02
* Filename      : rmst.cpp
* Description   : 
*****************************************************************/
#include "sdk.h"
#include "rmst.h"
#include <cassert>
#include <algorithm>
using namespace std;

namespace Guo {
class Edge {
public:
    sdk::Edge *edge;
    int Mandist;
    double Eucdist;
    Edge(const V_Position &v, sdk::Edge &e) {
        edge = &e;
        Mandist = Man::dist(v[e.u], v[e.v]);
        Eucdist = Euc::dist(v[e.u], v[e.v]);
    }
    ~Edge() {}
};
bool cmp(const Edge &e1, const Edge &e2) {
    return (e1.Mandist < e2.Mandist) || (e1.Mandist == e2.Mandist && e1.Eucdist < e2.Eucdist);
}
int find(int root[], const int &leaf) {             // used to find and renew specific leaf's root
    while (root[leaf] != root[root[leaf]])
        root[leaf] = root[root[leaf]];
    return root[leaf];
}
}   // namespace Guo

void RMST(const V_Position &vertex, V_Edge &edge, V_Face &face)  // You can modify variable names if you like
{
#ifdef TEST
    cerr << "assert vertex, edge and face..." << endl;
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size() - 1; i++)
        assert(edge[i].size() > 0);
    assert(face.size() > 0);
    cerr << "assert finished." << endl;
#endif

    vector<Guo::Edge> heap;
    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++)
            heap.push_back(Guo::Edge(vertex, edge[i][j]));

    sort(heap.begin(), heap.end(), Guo::cmp);           // this should be sort increase

    int root[vertex.size()];
    for (int i = 0; i < vertex.size(); i++)
        root[i] = i;

    for (int i = 0; i < heap.size(); i++) {
        sdk::Edge &e = *heap[i].edge;

        if (Guo::find(root, e.u) != Guo::find(root, e.v)) {
            e.ins = 1;
            if (e.u < e.v)
                root[e.v] = root[e.u];
            else
                root[e.u] = root[e.v];
        } else
            e.ins = 0;

        if (e.f1 == e.f2) {
            if (e.f1 != face.size() - 1) {
                vector<Edge>::iterator e1 = find(face[e.f1].e.begin(), face[e.f1].e.end(), e);
                assert(e1 != face[e.f1].e.end());
                vector<Edge>::iterator e2 = find(e1 + 1, face[e.f1].e.end(), e);
                assert(e2 != face[e.f1].e.end());

                e1->ins = e2->ins = e.ins;
            }
        } else {
            if (e.f1 != face.size() - 1) {
                vector<Edge>::iterator e1 = find(face[e.f1].e.begin(), face[e.f1].e.end(), e);
                assert(e1 != face[e.f1].e.end());

                e1->ins = e.ins;
            }
            if (e.f2 != face.size() - 1) {
                vector<Edge>::iterator e2 = find(face[e.f2].e.begin(), face[e.f2].e.end(), e);
                assert(e2 != face[e.f2].e.end());

                e2->ins = e.ins;
            }
        }
    }
}

