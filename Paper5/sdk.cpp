#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "sdk.h"
using namespace std;

bool sdk::operator == (const Edge &e1, const Edge &e2) {
    return (e1.u == e2.u) && (e1.v == e2.v);
}
bool sdk::operator != (const Edge &e1, const Edge &e2) {
    return !(e1 == e2);
}
bool sdk::operator == (const Face &f1, const Face &f2) {
    return f1.e == f2.e;
}
bool sdk::operator == (const Position &p1, const Position &p2) {        // Compare wheather p1 == p2
    return (p1.x == p2.x) && (p1.y == p2.y);
}
bool sdk::operator != (const Position &p1, const Position &p2) {        // Compare wheather p1 != p2
    return !(p1 == p2);
}
Edge::Edge() : link(NULL) {}
Edge::Edge(const Edge &e) : link(NULL) {
    *this = e;
}
Edge::~Edge() {}
Edge& Edge::operator = (const Edge &e) {
    if (this == &e)
        return *this;
    this->u = e.u;
    this->v = e.v;
    this->link = e.link;
    this->f1 = e.f1;
    this->f2 = e.f2;
    this->ins = e.ins;
    return *this;
}
double Euclidean::dist(const Position &p1, const Position &p2)
{
	const int dx = p1.x - p2.x;
	const int dy = p1.y - p2.y;
	return sqrt(dx * dx + dy * dy);
}
int Manhattan::dist(const Position &p1, const Position &p2)
{
	int tmp1 = p1.x-p2.x;
	int tmp2 = p1.y-p2.y;
	if (tmp1 < 0) tmp1 = -tmp1;
	if (tmp2 < 0) tmp2 = -tmp2;
	return tmp1+tmp2;
}
int sdk::judge_region_number(const Position &p1, const Position &p2)
{
	if (p1 == p2) return -1;
	if (p2.y-p2.x < p1.y-p1.x && p2.x+p2.y >= p1.x+p1.y) return 0;
	if (p2.x+p2.y > p1.x+p1.y && p2.y-p2.x >= p1.y-p1.x) return 1;
	if (p2.y-p2.x > p1.y-p1.x && p2.x+p2.y <= p1.x+p1.y) return 2;
	return 3;
	//if (p2.x+p2.y < p1.x+p1.y && p2.y-p2.x <= p1.y-p1.x) return 3;
}
bool sdk::Check_The_Graph(V_Position &vertex, V_Edge &edge, V_Face &face)
{
	int e = 0, n = vertex.size(), f = face.size();
	for (int i = 0; i < n; i++) e += edge[i].size();
	e /= 2;
	if (n + f != e + 2) {
		cerr << "Wrong answer at Euler theorem!!!" << endl;
		return 0;
	}
	map <int, int> m;
	m.clear();
	for (int i = 0; i < n; i++) {
		int tot = edge[i].size();
		for (int j = 0; j < tot; j++) {
			long long hash = (long long)edge[i][j].u*1000000000+edge[i][j].v;
			if (m[hash] == 1) {
				cerr << "Multiple edge occur!!!" << endl;
				return 0;
			}
			else m[hash] = 1;
			if (edge[i][j].u == edge[i][j].v) {
				cerr << "Self edeg occur!!!" << endl;
				return 0;
			}
			if (edge[i][j].u != i) {
				cerr << "Edge ends error!!!" << endl;
				return 0;
			}
			Edge *oppo = edge[i][j].link;
			if (oppo->u != edge[i][j].v || oppo->v != edge[i][j].u || oppo->link != &edge[i][j]) {
				cerr << "Opposite edge error!!!" << endl;
				return 0;
			}
		}
	}
	for (int i = 0; i < f-1; i++) {
		int tot = face[i].e.size();
		for (int j = 0; j < tot; j++)
			if (face[i].e[j].f1 != i && face[i].e[j].f2 != i) {
				cerr << "Face and edge connection error!!!" << endl;
				return 0;
			}
	}
	return 1;
}

