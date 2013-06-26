#include "defs.h"
#include "decl.h"
#include "extern.h"
#include "edge.h"
#include "sdk.h"
#include <stdio.h>
#include <algorithm>
using namespace std;

static void print_edges(int n);
static void print_triangles(int n);

void read_points(V_Position &vector) {
	int np = (int) vector.size();
	index i;

	for (i = 0; i < np; i++) 
		p_array[i].x = vector[i].x, p_array[i].y = vector[i].y;
}

Edge* add_edges(V_Edge &Edges, int x, int y) {
	Edges[x].push_back(Edge());
	Edge &edge = Edges[x].back();
	edge.u = x, edge.v = y;
	edge.f1 = edge.f2 = -1;
	return &(Edges[x].back());
}

// for generating Edges defined in sdk.h
struct TempEdge {
	int x, y;
	Edge *link;
	TempEdge() {}
	TempEdge(int _x, int _y, Edge *_link) {
		x = _x, y = _y, link = _link;
	}
};
bool TempEdgeCmp(TempEdge a, TempEdge b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool EdgeCmp(Edge a, Edge b) {
	return a.u < b.u || (a.u == b.u && a.v < b.v);
}
/* 
 *	Return the ring of edges about each vertex.
 */
void get_edges(int n, V_Edge &Edges) {
	Edges.resize(n);

	edge *e_start, *e;
	point *u, *v;
	index i;

	for (i = 0; i < n; i++) {
		u = &p_array[i];
		e_start = e = u->entry_pt;
		do
		{
			v = Other_point(e, u);
			if (u < v) {
				int x = u - p_array, y = v - p_array;
	Edge *edge1 = add_edges(Edges, x, y);
	Edge *edge2 = add_edges(Edges, y, x);
			}
			e = Next(e, u);
		} while (!Identical_refs(e, e_start));
	}

	for (int i = 0; i < Edges.size(); ++i) 
		sort(Edges[i].begin(), Edges[i].end(), EdgeCmp);

	vector<TempEdge> TempEdges;
	for (int i = 0; i < Edges.size(); ++i) for (int j = 0; j < Edges[i].size(); ++j) {
		Edge &edge = Edges[i][j];
		TempEdges.push_back(TempEdge(edge.v, edge.u, &edge));
	}
	sort(TempEdges.begin(), TempEdges.end(), TempEdgeCmp);

	int TempEdgeITR = 0;
	for (int i = 0; i < Edges.size(); ++i) for (int j = 0; j < Edges[i].size(); ++j) {
		Edge &edge = Edges[i][j];
		TempEdge tempedge = TempEdges[TempEdgeITR];
		if (tempedge.x == edge.u && tempedge.y == edge.v) {
			edge.link = tempedge.link;
			++TempEdgeITR;
		}
	}
}

// for generating datas defined in sdk.h
struct TempFace {
	int x, y, f;
	TempFace() {}
	TempFace(int _x, int _y, int _f) {
		x = _x, y = _y, f = _f;
	}
};
bool TempFaceCmp(TempFace a, TempFace b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
/* 
 *	Return the ring of triangles about each vertex.
 */
void get_result(int n, V_Position &Points, V_Edge &Edges, V_Face &Faces) {
	vector<TempFace> TempFaces;

	edge *e_start, *e, *next;
	point *u, *v, *w;
	index i;
	point *t;
	int FaceCnt = 0;

	for (i = 0; i < n; i++) {
		u = &p_array[i];
		e_start = e = u->entry_pt;
		do
		{
			v = Other_point(e, u);
			if (u < v) {
	next = Next(e, u);
	w = Other_point(next, u);
	if (u < w)
		if (Identical_refs(Next(next, w), Prev(e, v))) {	
			/* Triangle. */
			if (v > w) { t = v; v = w; w = t; }
			int x = u - p_array, y = v - p_array, z = w - p_array;
			if (Points[x].det(Points[y], Points[z]) < 0) {
				int t = y; y = z; z = t;
			}
			TempFaces.push_back(TempFace(x, y, FaceCnt));
			TempFaces.push_back(TempFace(y, z, FaceCnt));
			TempFaces.push_back(TempFace(z, x, FaceCnt));
			++FaceCnt;
			Faces.push_back(Face());
		}
			}

			/* Next edge around u. */
			e = Next(e, u);
		} while (!Identical_refs(e, e_start));
	}

	sort(TempFaces.begin(), TempFaces.end(), TempFaceCmp);
	int TempFaceITR = 0;
	for (int i = 0; i < Edges.size(); ++i) for (int j = 0; j < Edges[i].size(); ++j) {
		if (TempFaceITR >= TempFaces.size()) break;
		Edge &edge = Edges[i][j];
		TempFace tempface = TempFaces[TempFaceITR];
		if (tempface.x == edge.u && tempface.y == edge.v) {
			edge.f2 = tempface.f;
			++TempFaceITR;
		}
	}

	for (int i = 0; i < Edges.size(); ++i) for (int j = 0; j < Edges[i].size(); ++j) {
		Edge &edge = Edges[i][j];
		if (edge.f1 != -1) (edge.link)->f2 = edge.f1;
		if (edge.f1 == -1) edge.f1 = (edge.link)->f2;
		if (edge.f2 != -1) (edge.link)->f1 = edge.f2;
		if (edge.f2 == -1) edge.f2 = (edge.link)->f1;
	}

	TempFaceITR = 0;
	for (int i = 0; i < Edges.size(); ++i) for (int j = 0; j < Edges[i].size(); ++j) {
		Edge &edge = Edges[i][j];
		if (edge.f2 == -1) continue;
		Face &face = Faces[edge.f2];
		face.e.push_back(edge);
	}

	for (int i = 0; i < Faces.size(); ++i) {
		Edge edge1 = Faces[i].e[0];
		Edge edge2 = Faces[i].e[1];
		if (edge1.v != edge2.u) 
			swap(Faces[i].e[1], Faces[i].e[2]);
	}
}
