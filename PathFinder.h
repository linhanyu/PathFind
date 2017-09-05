//
// Created by Henry lin on 2017/9/1.
//

#ifndef PATHFIND_PATHFINDER_H
#define PATHFIND_PATHFINDER_H

#include "AstarEstimater.h"
#include "Graph.h"
#include <vector>
#include <algorithm>

using namespace std;

class pathFinder{
public:

    double dist[1<<MAXV][MAXV];
    pair<int,int> pre[1<<MAXV][MAXV];

    std::vector<int> AStarFinder(Graph & G,const std::vector<int> & ac_points);



};
#endif //PATHFIND_PATHFINDER_H
