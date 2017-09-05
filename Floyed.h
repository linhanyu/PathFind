//
// Created by Henry lin on 2017/9/2.
//

#ifndef PATHFIND_FLOYED_H
#define PATHFIND_FLOYED_H

#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 300;

extern double dp[MAXV][MAXV];
extern int path[MAXV][MAXV] ;


void init(int n);
void floyd(int n);
void getPath(int i ,int j,vector<int> & ans);
double dpfloyed(vector<int> & ac_point,vector<int> & path);
double cal_gene(vector<int > & gene,vector<int > & ac_point,int s,int t);
void exchange(vector<int > & gene1,vector<int> & gene2,int p1,int p2,vector<int > & n_gene);
void cross(vector<int > & gene1,vector<int > & gene2);
void mutate(vector<int > & gene);
double Genetic(vector<int> & ac_point,vector<int> & path,int gene_num,int max_iter,int cross_num,int mutate_num);
#endif //PATHFIND_FLOYED_H
