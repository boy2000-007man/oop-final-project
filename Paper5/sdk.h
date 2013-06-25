#ifndef SDK_H_INCLUDED
#define SDK_H_INCLUDED

#include <vector>

namespace sdk {
// Stand for the position of a vertex
class Position
{
	public:
	int x, y;  // Notice that all points can be refined in integer coordinates
	Position() {}
	Position(int i, int j) : x(i), y(j) {}
	~Position() {}
};
class Edge
{
	public:
	int u, v;    // From point u to point v
	Edge *link;  // Point to the edge in opposite
	int f1, f2;  // Two faces that the edge adjacent, when walk from u to v, the right hand is f1 and the left hand is f2
	int ins;     // This flag is only used in the third and the fourth algorithm (RMST, polygonal contraction), indicate wheather the edge from BNG is in RMST, 1 for yes and 0 for no
	Edge();
    Edge(const Edge&);
	~Edge();
    Edge& operator = (const Edge &e);
};
class Face
{
	public:
	std::vector <Edge> e; // Edges in counterclockwise in the polygonal face
	Face() {}
	~Face() { e.clear(); }
};
typedef std::vector < Position > V_Position;
typedef std::vector < std::vector < Edge > > V_Edge;
typedef std::vector < Face > V_Face;

const double Lowest_Improvement_Factor = 0.99;  // Check wheather the solution can be improved

bool operator == (const Edge &e1, const Edge &e2);
bool operator != (const Edge &e1, const Edge &e2);
bool operator == (const Face &f1, const Face &f2);              // this == is special, must be careful
bool operator == (const Position &p1, const Position &p2);        // Compare wheather p1 == p2
bool operator != (const Position &p1, const Position &p2);        // Compare wheather p1 != p2
namespace Euclidean {
double dist(const Position &p1, const Position &p2);              // Return the Euclidean distance of p1 and p2
}   // namespace Euclidean
namespace Manhattan {
int dist(const Position &p1, const Position &p2);                 // Return the Manhattan distance of p1 and p2
}   // namespace Manhattan
namespace Euc = Euclidean;
namespace Man = Manhattan;
using Man::dist;
int judge_region_number(const Position &p1, const Position &p2);  // Judge the region number of p1 in which p2 lies
//  return  0 when p2 is right of p1
//  return  1 when p2 is above p1
//  return  2 when p2 is left of p1
//  return  3 when p2 is below p1
//  return -1 when p1 == p2

bool Check_The_Graph(V_Position &vertex, V_Edge &edge, V_Face &face);
// This function can help you check the graph
// 1. Check the Euler theorem (for a planar graph, v + f = e + 2)
// 2. Check the edge connecting
// 3. Check correctness between edges and faces
}   // namespace sdk
using namespace sdk;

#endif // SDK_HH_INCLUDED
