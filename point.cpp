//
// Created by Henry lin on 2017/8/31.
//


#include <cmath>
#include "point.h"


double point::cal_dis(const point &b) {
    return sqrt((x-b.x)*(x-b.x)) + sqrt((y-b.y)*(y-b.y));
}
