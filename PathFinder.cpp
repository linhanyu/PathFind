//
// Created by Henry lin on 2017/9/1.
//

#include "PathFinder.h"
#include <algorithm>
#include <vector>
#include <queue>
#include "point.h"

using namespace std;

typedef pair<double,pair<int,int > > p;

vector<int> pathFinder::AStarFinder(Graph & G,const vector<int> & ac_points) {
    priority_queue<p,vector<p>,less<p>> Q;

    int s = ac_points[0],t=ac_points[1];
    //s源点，t汇
    for (int i = 0; i < (1<<MAXV); ++i)
        for (int j = 0; j < MAXV; ++j)
            dist[i][j] = INF;



    int finalmask = 0,beginmask = 1<<s;
    for (int i = 0; i < ac_points.size(); ++i) finalmask |= 1<<ac_points[i];
    dist[beginmask][s] = 0;
    Q.push(p(dist[beginmask][s],pair<int,int>(s,beginmask)));

    while (!Q.empty()){
        p point = Q.top();
        Q.pop();

        int u =  point.second.first;
        int umask =  point.second.second;
        double udist =  point.first;

        if (umask == finalmask) break;

        if (dist[umask][u] < udist) continue;

        for (int i = G.head[u];~i;i = G.G[i].next){
            int v = G.G[i].v;
            int vmask = (1<<v)|umask;


            if (dist[vmask][v] < dist[umask][u] + G.G[i].c){
                dist[vmask][v] = dist[umask][u] + G.G[i].c;
                Q.push(p(dist[vmask][v],pair<int,int>(vmask,v)));
                pre[vmask][v] = pair<int,int>(umask,u);
            }

        }

        vector<int> ans;

        for (int i = t, mask = finalmask; mask != beginmask && i != s; i = pre[mask][i].second,mask = pre[mask][i].first ) {
            ans.push_back(i);
        }

        ans.push_back(s);
        reverse(ans.begin(),ans.end());
        return ans;

    }


}
