#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <cassert>
#include <climits>
#include "SPPackingCommand.h"
#include "Layout.h"

namespace RECTPACKING {
using namespace std;

static void FloydWarshallShortestPath(int **d, int num_nodes)
{
    for (int k=0; k<num_nodes; k++)
        for (int i=0; i<num_nodes; i++)
            for (int j=0; j<num_nodes; j++)
                if (d[i][k] != INT_MAX && d[k][j] != INT_MAX && d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                }
}

static void OneDirectionPacking(vector<pair<int, int> > &cons, Layout &layout, bool hor)
{
  //number of rects + virtual source
  vector<Rect> &rects = layout.getRects();
  const int rectNum = rects.size();
  const int num_nodes = rectNum+1;
  const int sourceId = rectNum;

  //make an adjacent matrix with weights
  int **d = new int* [num_nodes];
  for(int i = 0; i < num_nodes; i++)
  {
    d[i] = new int[num_nodes];
    for(int j = 0; j < num_nodes; j++)
    {
        d[i][j] = INT_MAX;
    }
  }
  for(int i = 0; i < num_nodes; i++)
  {
      d[i][i] = 0;
  }

  //add the edges
  if (hor)
  {
    for (int i = 0; i < rectNum; ++ i)
    {
        #ifdef __OUT__
        cout << "Add edge <" << sourceId << "," << i << "> " << -rects[i].width << endl;
        #endif
        d[sourceId][i] = -rects[i].width;
    }
    for (int i = 0; i < (int)cons.size(); ++ i)
    {
        #ifdef __OUT__
        cout << "Add edge <" << cons[i].first << "," << cons[i].second << "> " << -rects[cons[i].second].width << endl;
        #endif
        d[cons[i].first][cons[i].second] = -rects[cons[i].second].width;
    }
  }
  else
  {
    for (int i = 0; i < rectNum; ++ i)
    {
        #ifdef __OUT__
        cout << "Add edge <" << sourceId << "," << i << "> " << -rects[i].height << endl;
        #endif
        d[sourceId][i] = -rects[i].height;
    }
    for (int i = 0; i < (int)cons.size(); ++ i)
    {
        #ifdef __OUT__
        cout << "Add edge <" << cons[i].first << "," << cons[i].second << "> " << -rects[cons[i].second].height << endl;
        #endif
        d[cons[i].first][cons[i].second] = -rects[cons[i].second].height;
    }
  }
  #ifdef __OUT__
  cout << "Finished building the directed graph (adjacency matrix) with " << num_nodes << " vertices and " << num_nodes*num_nodes << " edges" << endl;
  #endif
  FloydWarshallShortestPath(d, num_nodes);
  for (int i = 0; i < rectNum; ++ i)
  {
      #ifdef __OUT__
      std::cout << "dii " << d[i][i] << endl;
      #endif
      int dis = -d[sourceId][i];
      #ifdef __OUT__
      std::cout << "Rect " << i << ": " << dis << endl;
      #endif
      if (hor)
      {
        rects[i].lb.x = dis-rects[i].width;
      }
      else
      {
        rects[i].lb.y = dis-rects[i].height;
      }
  }

  for(int i = 0; i < num_nodes; i++)
    delete [] d[i];
  delete []d;
}

void LongestGraphPacking(vector<pair<int, int> > &horCons, vector<pair<int, int> > &verCons, Layout &layout)
{
  #ifdef __OUT__
  cout << "In LongestGraphPacking " << endl;
  #endif
  bool hor = true;
  #ifdef __OUT__
  cout << "========== horizontal ==========" << endl;
  #endif
  OneDirectionPacking(horCons, layout, hor);
  hor = false;
  #ifdef __OUT__
  cout << "========== vertical ==========" << endl;
  #endif
  OneDirectionPacking(verCons, layout, hor);
}

}
