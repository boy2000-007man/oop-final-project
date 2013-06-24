#include "sdk.h"
#include "rmst.h"

namespace sdk {
    using ::Edge;
}   // namespace sdk
namespace Guo {
class Edge {
    Edge(const Edge&);
public:
    sdk::Edge *edge;
    int Mandis;
    double Eucdis;
    Edge(const V_Position &v, const sdk::Edge &e) {
        edge = &e;
        Mandis = Man::dis(v[e.u], v[e.v]);
        Eucdis = Euc::dis(v[e.u], v[e.v]);
    }
    ~Edge() {}
}
bool cmp(const Edge &e1, const Edge &e2) {
    return (e1.Mandis < e2.Mandis) || (e1.Mandis == e2.Mandis && e1.Eucdis < e2.Eucdis);
}
int find(int root[], const int &leaf) {
    while (root[leaf] != root[root[leaf]])
        root[leaf] = root[root[leaf]];
    return root[leaf];
}
}   // namespace Guo
using namespace std;

void RMST(const V_Position &vertex, V_Edge &edge)  // You can modify variable names if you like
{
    assert(vertex.size() > 0);
    assert(edge.size() > 0);
    for (int i = 0; i < edge.size(); i++)
        assert(edge[i].size() > 0);

    vector<Guo::Edge> heap();
    for (int i = 0; i < edge.size(); i++)
        for (int j = 0; j < edge[i].size(); j++)
            heap.push_back(Guo::Edge(vertex, edge[i][j]));

    sort(heap.begin(), heap.end(), cmp);

    int root[vertex.size()];
    for (int i = 0; i < vertex.size(); i++)
        root[i] = i;

    for (int i = 0; i < heap.size(); i++) {
        sdk::Edge &e = *heap[i].e;

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

