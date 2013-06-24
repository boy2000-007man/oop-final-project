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
int find(int root[], const int &leaf) {
    while (root[leaf] != root[root[leaf]])
        root[leaf] = root[root[leaf]];
    return root[leaf];
}
}   // namespace Guo

void RMST(const V_Position &vertex, V_Edge &edge)  // You can modify variable names if you like
{
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size(); i++)
        assert(edge[i].size() > 0);

    vector<Guo::Edge> heap;
    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++)
            heap.push_back(Guo::Edge(vertex, edge[i][j]));

    sort(heap.begin(), heap.end(), Guo::cmp);

    int root[vertex.size()];
    for (int i = 0; i < vertex.size(); i++)
        root[i] = i;

    for (int i = 0; i < heap.size(); i++) {
        sdk::Edge &e = *heap[i].edge;

        using Guo::find;
        if (find(root, e.u) != find(root, e.v)) {
            e.ins = 1;
            if (e.u < e.v)
                root[e.v] = root[e.u];
            else
                root[e.u] = root[e.v];
        } else
            e.ins = 0;
    }
}

