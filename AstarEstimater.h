//
// Created by Henry lin on 2017/9/1.
//

#ifndef PATHFIND_ASTARESTIMATER_H
#define PATHFIND_ASTARESTIMATER_H

#include "point.h"

class AstarEstimator{
public:
    virtual double estimate(const point & p, double g);
};

class TargetEstimator : AstarEstimator{
    //计算和终点的距离public:
    //需要用一个终点初始化
public:
    point * t;
    TargetEstimator(point * t){this->t = t; }

    double estimate(const point & p, double g);
};

#endif //PATHFIND_ASTARESTIMATER_H


