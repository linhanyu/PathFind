//
// Created by Henry lin on 2017/9/1.
//

#include "Graph.h"
#include <cstring>

void Graph::init() {
    memset(head,-1, sizeof(head));
    cur = 0;
    vcur = 0;
}

void Graph::addedge_(int u, int v, double c) {
    G[cur].v = v;
    G[cur].c = c;
    G[cur].next = head[u];
    head[u] = cur++;
}

void Graph::addedge(int u, int v, double c) {
    addedge_(u,v,c);
    addedge_(v,u,c);

}

void Graph::addpoint(int x, int y) {
    points[vcur].x = x;
    points[vcur].y = y;
    vcur++;
}
