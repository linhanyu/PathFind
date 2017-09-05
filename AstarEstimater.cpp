//
// Created by Henry lin on 2017/8/31.
//

#include "point.h"
#include "AstarEstimater.h"
//

double AstarEstimator::estimate(const point &p, double g) {
    return g;
}

double TargetEstimator::estimate(const point &p, double g) {
    return g+t->cal_dis(p);
}
