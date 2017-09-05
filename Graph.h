//
// Created by Henry lin on 2017/9/1.
//

#ifndef PATHFIND_FORWORDSTAR_H
#define PATHFIND_FORWORDSTAR_H

#include "consts.h"
#include "point.h"
#include "cstring"

class edge{
public:
    int v,next;
    double c;
};

class Graph{
public:
    point points[MAXV];
    edge G[MAXE];
    int head[MAXV],cur,vcur;

    void init();
    void addedge(int u,int v,double c);
    void addedge_(int u,int v,double c);;
    void addpoint(int x,int y);
};



#endif //PATHFIND_FORWORDSTAR_H
