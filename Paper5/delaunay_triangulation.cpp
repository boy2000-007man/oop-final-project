#include "defs.h"
#include "decl.h"
#include "extern.h"
#include "edge.h"
#include "delaunay_triangulation.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define SIZE(x) ((int) (x).size())

void Delaunay_Triangulation(V_Position &Points, V_Edge &Edges, V_Face &Faces) {
	int n = SIZE(Points);
	edge *l_cw, *r_ccw;
	index i;
	point **p_sorted, **p_temp;

	if (n <= 2)
		cerr << "Number of points less than 3" << endl;

	alloc_memory(n);
	read_points(Points);

	/* Initialise entry edge pointers. */
	for (i = 0; i < n; i++) p_array[i].entry_pt = NULL;

	/* Sort. */
	p_sorted = (point **) malloc((unsigned) n * sizeof(point *));
	if (p_sorted == NULL)
		cerr << "triangulate: not enough memory" << endl;
	p_temp = (point **) malloc((unsigned) n * sizeof(point *));
	if (p_temp == NULL)
		cerr << "triangulate: not enough memory" << endl;
	for (i = 0; i < n; i++) p_sorted[i] = p_array + i;

	merge_sort(p_sorted, p_temp, 0, n - 1);
	free((char *) p_temp);

	/* Triangulate. */
	divide(p_sorted, 0, n - 1, &l_cw, &r_ccw);
	free((char *) p_sorted);

	get_edges(n, Edges);
	get_result(n, Points, Edges, Faces);

	free_memory();
}

