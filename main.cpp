#include <iostream>


//#include "AstarEstimater.h"
//#include "point.h"
//#include "PathFinder.h"

using namespace std;

#include "Floyed.h"
#include "consts.h"

using namespace std;

int main() {
    int n,k,begin,end;

    scanf("%d",&n);
    int dummy = ++n;
    init(n);

    while (true){
        int x,y;
        double c;
        scanf("%d%d%lf",&x,&y,&c);
        if (x<0) break;
        dp[x][y] = dp[y][x] = min(dp[x][y],c);
    }

    scanf("%d%d",&begin,&end);

    dp[end][dummy] = dp[dummy][end] = 0;

    floyd(n);

    scanf("%d",&k);

    vector<int > ac_points;
    vector<int > path;

    ac_points.push_back(begin);
    ac_points.push_back(dummy);

    path.push_back(begin);
    double ans = 0;
    for (int i = 0; i < k; ++i) {
        int p;
        scanf("%d",&p);
        ac_points.push_back(p);
    }
    if (k >= MAXK-2){
//  if (k >= 16){        //遗传算法+floyed近似
        ans = Genetic(ac_points,path,100,500,50,1);
    }else{
        //floyed+动态规划最优
        ans = dpfloyed(ac_points,path);
    }

    printf("%lf\n",ans);
    for (int i = 0; i < path.size()-1; ++i)
        printf("%d ",path[i]);

//    测试部分
//
//    puts("算法2");
//    clock_t a = clock();
//    ans = dpfloyed(ac_points,path);
//    printf("执行时间%ld\n",clock() - a);
//    printf("%lf\n",ans);
//    for (int i = 0; i < path.size()-1; ++i)
//        printf("%d ",path[i]);
//    puts("");
//
//    path.clear();
//    path.push_back(begin);
//
//    puts("算法3");
//    a = clock();
//    ans = Genetic(ac_points,path,300,1000,50,1);
//    printf("执行时间%ld\n",clock() - a);
//    printf("%lf\n",ans);
//    for (int i = 0; i < path.size()-1; ++i)
//        printf("%d ",path[i]);
//    puts("");
    return 0;
}

//已舍弃的启发式搜索
//int main() {
//
//
//    g.init();
//
//    int n,k,begin,end;
//    scanf("%d",&n);
//
//    while (true){
//        int x,y,c;
//        scanf("%d%d%d",&x,&y,&c);
//        if (x<0) break;
//        g.addedge(x,y,c);
//    }
//
//    scanf("%d%d",&begin,&end);
//    if (begin == end){
//        //拆点法
//        end = n++;
//        g.addedge(end,begin,0);
//    }
//
//    scanf("%d",&k);
//    vector<int > ac_points;
//
//    ac_points.push_back(begin);
//    ac_points.push_back(end);
//
//    for (int i = 0; i < k; ++i) {
//        int p;
//        scanf("%d",&p);
//        ac_points.push_back(p);
//    }
//
//    vector<int > path = pf.AStarFinder(g,ac_points);
//    for (int i = 0; i < path.size(); ++i) {
//        printf("%d\n",path[i]);
//    }
//
//    return 0;
//}