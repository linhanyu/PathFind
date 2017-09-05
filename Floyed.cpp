//
// Created by Henry lin on 2017/9/2.
//
#include "Floyed.h"

#include <random>
#include <vector>
#include <algorithm>

using namespace std;
#define lowbit(x) (x&-x)



double dp[MAXV][MAXV] ;
int path[MAXV][MAXV] ;
double dpf[MAXV][1<<13];
int fpath[MAXV][1<<13];


void init(int n){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = INF;
            path[i][j] = 0;
        }
        dp[i][i] = 0;
    }
}

void floyd(int n){
    int i,j,k;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            for(k=1;k<=n;k++)
                if(dp[i][k] + dp[k][j] < dp[i][j]){
                    dp[i][j] = dp[i][k] + dp[k][j];
                    path[i][j] = k;
                }
}

void getPath(int i ,int j,vector<int> & ans){
    if(i==j) return;
    if(path[i][j]==0)
        ans.push_back(j);
    else{
        getPath(i,path[i][j],ans);
        getPath(path[i][j],j,ans);
    }
}

double dpfloyed(vector<int> & ac_point,vector<int> & path){
    int k = ac_point.size();

    //待在v点，访问了status个点
    for (int i=0;i<(1<<k);i++)
        for (int j = 0; j < k; ++j)
            dpf[j][i] = INF;

    dpf[0][1] = 0;

    for (int statu = 1; statu < (1 << k); ++statu) {
        for (int cur = 0; cur < k; ++cur) {
            int curve = 1<<cur;
            if (statu & curve) continue;
                //尚未访问过
            for (int i = 0; i < k; ++i) {
                if (dpf[i][statu] + dp[ac_point[i]][ac_point[cur]] < dpf[cur][statu|curve]){
                    dpf[cur][statu|curve] = dpf[i][statu] + dp[ac_point[i]][ac_point[cur]];
                    //访问cur点，在所有起始位置开始，走最短路到达下一个点
                    fpath[cur][statu|curve] = statu;
                }
            }
        }
    }

    int statu = (1<<k)-1,p = 1;
    double ans = dpf[1][statu];
    //停在终点

    vector<int > path_point;
    //记录下到达次序,反向存储的
    while (statu){
        int i=-1,curve = statu ^ fpath[p][statu];
        while (curve) curve>>=1,i++;
        path_point.push_back(i);
        statu = fpath[i][statu];
    }
    //生成路径
    for (int i = path_point.size()-1; i > 0 ; --i) {
        getPath(ac_point[path_point[i]],ac_point[path_point[i-1]],path);
    }

    return ans;
}

double cal_gene(vector<int > & gene,vector<int > & ac_point,int s,int t){
    double ans = dp[s][ac_point[*gene.begin()]] + dp[ac_point[*gene.rbegin()]][t];
    for (int i = 1; i < ac_point.size(); ++i) {
        ans += dp[ac_point[i-1]][ac_point[i]];
    }
    return ans;

}


void exchange(vector<int > & gene1,vector<int> & gene2,int p1,int p2,vector<int > & n_gene){
    bool mask[MAXV];
    memset(mask,0, sizeof(mask));
    for (int j = p1; j <= p2 ; ++j) mask[gene2[j]] = true;

    for (int i = 0; i < gene1.size(); ++i) {
        if (gene1[i] == gene2[p1])
            for (int j = p1; j <= p2 ; ++j)
                n_gene.push_back(gene2[j]);

        if (mask[gene1[i]]) continue;

        mask[gene1[i]] = true;
        n_gene.push_back(gene1[i]);
    }
}

void cross(vector<int > & gene1,vector<int > & gene2){
    int point1 = rand()%gene1.size();
    int point2 = rand()%gene1.size();
    if (point1 > point2) swap(point1,point2);

    vector<int > n_gene1,n_gene2;

    exchange(gene1,gene2,point1,point2,n_gene1);
    exchange(gene2,gene1,point1,point2,n_gene2);

    gene1 = n_gene1;
    gene2 = n_gene2;
}

void mutate(vector<int > & gene){
    int point1 = rand()%gene.size();
    int point2 = rand()%gene.size();
    swap(gene[point1],gene[point2]);
}

double Genetic(vector<int> & ac_point,vector<int> & path,int gene_num,int max_iter,int cross_num,int mutate_num){
    vector<int> gene_poll[MAXV*2][2];
    vector<int> sub_ac_point;
    for (int i = 0; i < ac_point.size()-2; ++i) sub_ac_point.push_back(ac_point[i+2]);

    vector<int> nums(sub_ac_point.size());

    pair<double,int> weights[MAXV*2];

    for (int i = 0; i < nums.size(); ++i) nums[i] = i;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    int pool = 0;

    for (int i = 0; i < gene_num; ++i) {
        gene_poll[i][pool] = nums;
        shuffle(nums.begin(),nums.end(),default_random_engine (seed));
    }


    for (int i = 0; i < max_iter; ++i) {
        int curve = gene_num;
        double weights_sum  = 0;

        for (int k = 0; k < mutate_num; ++k) {
            int g = rand()%gene_num;
            gene_poll[curve++][pool] = gene_poll[g][pool];
            mutate(gene_poll[g][pool]);
        }

        for (int k = 0; k < cross_num; ++k) {
            int g1 = rand()%gene_num;
            int g2 = rand()%gene_num;
            gene_poll[curve++][pool] = gene_poll[g1][pool];
            gene_poll[curve++][pool] = gene_poll[g2][pool];
            cross(gene_poll[g1][pool],gene_poll[g2][pool]);
        }

        for (int j = 0; j < curve; ++j)
            weights[j] = pair<double,int >(cal_gene(gene_poll[j][pool],sub_ac_point,ac_point[0],ac_point[1]),0);

        sort(weights,weights+curve,less<pair<double,int >>());

        for (int j = 0; j < gene_num; ++j)
            gene_poll[j][!pool] = gene_poll[weights[j].second][pool];

        pool = !pool;
    }
    getPath(ac_point[0],sub_ac_point[gene_poll[0][pool][0]],path);
    int len = gene_poll[0][pool].size();
    for (int i = 1; i < len; ++i) {
        getPath(sub_ac_point[gene_poll[0][pool][i-1]],sub_ac_point[gene_poll[0][pool][i]],path);
    }
    getPath(sub_ac_point[gene_poll[0][pool][len-1]],ac_point[1],path);
    return cal_gene(gene_poll[0][pool],sub_ac_point,ac_point[0],ac_point[1]);

}