//
// Created by lulitao on 16-12-14.
//

#ifndef POINT_H
#define POINT_H
#include "all.h"

const double eps = 1e-4;

struct Point {
    double longitude, latitude;
    explicit Point (double x=0, double y=0): longitude(x), latitude(y) {}
    bool operator==(const Point &b) const {
        return fabs(longitude-b.longitude)<eps && fabs(latitude-b.latitude)<eps;
    }
    bool operator!=(const Point &b) const {
        return !operator==(b);
    }
    Point operator+ (const Point &p) const {
        return Point(longitude + p.longitude, latitude + p.latitude);
    }
    Point operator- (const Point &p) const {
        return Point(longitude - p.longitude, latitude - p.latitude);
    }
    Point operator/ (int d) const {
        return Point(longitude/d, latitude/d);
    }
};
ostream &operator<<(ostream &out, const Point &a) {
    out << a.longitude << ',' << a.latitude;
    return out;
}
inline double dist(const Point &a, const Point &b) {
    /*
    return sqrt(
            pow(6371*2*M_PI*(a.longitude-b.longitude)*cos((a.latitude+b.latitude)/2)/360,2) +
            pow(6371*2*M_PI*(a.latitude-b.latitude)/360,2)
    );
     */
    double longitude_delta = fabs(a.longitude - b.longitude);
    double latitude_delta = fabs(a.latitude - b.latitude);
    double latitude_ave_arc = fabs(a.latitude + b.latitude) / 2 / 180 * M_PI;
    double resx = longitude_delta * cos(latitude_ave_arc) * 6371 * 2 * M_PI / 360;
    double resy = latitude_delta * 6371 * 2 * M_PI / 360;
    double res = sqrt(resx * resx + resy * resy);
    return res;
}

double calc_income(double travel_dis) {
    double net_income = 0;
    if (travel_dis <= 3) net_income = 14;
    else net_income = 14 + (travel_dis-3)*2.4;
    return net_income;
}

/*********** Distinguish Point ***************/
typedef long long hash_type;
hash_type Point_hash(const Point &p) {
    return int(p.longitude*100000)*100000000LL + int(p.latitude*100000);
}
Point n2p[MAXP];
int pcnt = 0;
int get_point_id(const Point &p) {
    static unordered_map<hash_type, int> h2n;
    int &t = h2n[Point_hash(p)];
    if (!t) n2p[t = ++pcnt] = p;
    return t;
}

int cross_num = 0;

/***********End Distinguish Point ************/

vector<int> n2rn[MAXP];
vector<int> get_road_id(const Point &p) {
    return n2rn[get_point_id(p)];
}

#endif //POINT_H
