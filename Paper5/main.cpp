// The Polygonal Contraction Heuristic for Rectilinear Steiner Tree Construction
// Copyright 2013 OOP group. All rights reserved.
// Authors: Weiran He, Xuenan Guo, Dieqiao Feng

/* Polygonal Contraction Heuristic (PCH)
 * Require: The input is a set of points. The output is a Steiner tree.
 * repeat
 *     Construct the Delaunay triangulation on the point set.
 *     Construct the BNG as in Algorithm 1.
 *     Construct the RMST from the BNG.
 *     Do polygonal contraction as in Algorithm 2.
 * until the MST can not be improved much
 */

// This is the main program
#include "sdk.h"
#include "delaunay_triangulation.h"
#include "bng.h"
#include "rmst.h"
#include "polygonal_contraction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

const string Read_In_File_Name = "input.txt";
const string Write_Out_File_Name = "output.txt";

void Read_IN(V_Position &vertex)
{
	int n;  // Total number of points in the input file
	ifstream fin(Read_In_File_Name.c_str());
	Position r_tmp;

	vertex.clear();
	for (int i = 0; i < n; i++) {
		fin >> r_tmp.x >> r_tmp.y;
		vertex.push_back(r_tmp);
	}

	fin.close();
}
void Write_OUT(V_Position &vertex, int solution)
{
	ofstream fout(Write_Out_File_Name.c_str());

	fout << "The best current solution the program computed is " << solution << endl;
	fout << "Here is the vertexes distribution:" << endl;
	fout << "The total number of vertexes is " << vertex.size() << endl;
	for (int i = 0; i < vertex.size(); i++)
		fout << vertex[i].x << ' ' << vertex[i].y << endl;
	
	fout.close();
}
int main()
{
	V_Position vertex;
	V_Edge edge, mst_edge;
	V_Face face;
	// To travel all the edges like this:
	/*
	for (int i = 0; i < vertex.size(); i++)
		for (vector<Edge>::iterator it = edge[i].begin(); it != edge[i].end(); it++) {
			int u = it->u;
			int v = it->v;
			// Edge from u to v, notice i == u
			Edge *oppo = it->link;
			int flag = (oppo->u == v && oppo->v == u && oppo->link == &(*it));
			if (! flag) {
				cerr << "Wrong edge value!!!" << endl;
			}
		}
	*/

	// Readin steps
	// All points will be saved in vertex
	Read_IN(vertex);

	long long pre_solution, now_solution = (long long)1 << 60;
	do {
		pre_solution = now_solution;

		// Construct the Delaunay triangulation on the point set.
		// Input variables: vertex
		// Compute variables: edge, face
		// Attention: Do not modify vertex. Let f = face.size(), you must assign the outermost face index f-1!!! face[0..f-2] are inner faces so you should compute edges around the face for them, but for face[f-1] you need not compute the edges. However you still need to let face[f-1] empty and existent.
		// Achieve it in delaunay_triangulation.cpp
		Delaunay_Triangulation(vertex, edge, face);
		// A checking step, see more in sdk, help you find faults
		if (! Check_The_Graph(vertex, edge, face)) {
			cerr << "Wrong answer at step1!!!" << endl;
			//for ( ; ; );
		}

		// Construct the BNG as in Algorithm 1.
		// Input variables: vertex, edge, face
		// Compute variables: edge, face
		// Attention: Do not modify vertex. Compute edge[] and face[] for BNG of the previous graph. Let f = face.size(), you still need to guarantee face[f-1] is the outermost face. You need not to compute the edges around face[f-1], but you need to let face[f-1] empty and existent.
		// Achieve it in bng.cpp
		BNG(vertex, edge, face);
		// A checking step, see more in sdk, help you find faults
		if (! Check_The_Graph(vertex, edge, face)) {
			cerr << "Wrong answer at step2!!!" << endl;
			//for ( ; ; );
		}

		// Construct the RMST from the BNG.
		// Input variables: vertex, edge
		// Compute variables: edge[][].ins
		// Attention: Do not modify vertex and other elements except .ins in edge[][]. This step is relatively easy, so you'd better to try using O(n) algorithm to compute spanning tree of the plannar graph, see more in [18] in the paper.
		// Achieve it in rmst.cpp
		RMST(vertex, edge, face);

		// Do polygonal contraction as in Algorithm 2.
		// Input variables: vertex, edge, face
		// Compute variables: vertex, function return value
		// Attention: The most difficult step in the program. You may add new vertexes and edges to the graph if needed during contraction, or you may modify edge[][].ins to delete the edge from RMST. Finally you should compute the new vertex set and the cost of the new RMST.
		// Achieve it in polygonal_contraction.cpp
		now_solution = Polygonal_Contraction(vertex, edge, face);

		
	} while ((double)now_solution/pre_solution < Lowest_Improvement_Factor);

	Write_OUT(vertex, now_solution);
	return 0;
}

