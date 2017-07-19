//
// Created by lulitao on 16-12-29.
//

#ifndef BLOCK_H
#define BLOCK_H

#include "all.h"
#include "point.h"



class block_idx {
public:
    double intv_x, intv_y, min_x, max_x, min_y, max_y;
    int x_num, y_num, size;
    vector<Point> blk[XNUM][YNUM];

    pair<int,int> get_block_id(const Point &p) {
        int ix = (p.longitude - min_x) / intv_x, iy = (p.latitude - min_y) / intv_y;
        if (ix < 0 || iy < 0 || ix > x_num || iy > y_num) throw(domain_error("Point out of range"));
        return make_pair(ix + 1, iy + 1);
    }
    block_idx(double intv_x, double intv_y, double min_x, double max_x, double min_y, double max_y):
            intv_x(intv_x), intv_y(intv_y), min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y) {
        x_num = (max_x - min_x) / intv_x + 10 , y_num = (max_y - min_y) / intv_y + 10 ;
//        cerr << "init blk: (x_num, y_num) = " << "(" << x_num << ',' << y_num << ")" << endl;
//        cerr << "range:" << min_x << ',' << max_x << ':' << min_y << ',' << max_y << endl;
    }
    void clear() {
        for (int i=0; i<x_num; i++) for (int j=0; j<y_num; j++)
                blk[i][j].clear();
        size = 0;
    }

    bool use_last;
    pair<int,int> last_idx;
    vector<Point> last_ans;

    void insert_point(const Point &p) {
        auto i = get_block_id(p);
        blk[i.first][i.second].push_back(p);
        size++;
        use_last = false;
    }
    void erase_point(const Point &p) {
        auto i = get_block_id(p);
        auto &b = blk[i.first][i.second];
        auto it = find(b.begin(), b.end(), p);
        if (it!=b.end()) {
            b.erase(it);
            size--;
            use_last = false;
        }
    }
    vector<Point> get_in_3km(const Point &p) {
        vector<Point> ans;
        int calced = 0;
        auto id = get_block_id(p);
        if (use_last && id == last_idx) {
            return last_ans;
        }
        use_last = true;
        last_idx = id;
        int r = id.first, c = id.second;
        for (int i = max(0, r-1); i <= min(x_num-1, r+1); i++) {
            for (int j = max(0, c - 1); j <= min(y_num-1, c + 1); j++) {
                for (Point &b:blk[i][j]) {
                    calced++;
                    if (dist(b, p) < 3) {
                        ans.push_back(b);
                    }
                }
            }
        }
        //cerr << "calc:" << calced << ":" << ans.size() <<" :: " << size << endl;
        return last_ans = ans;
    }
    vector<Point> get_in_3km_norm(const Point &p) {
        use_last = false;
        return get_in_3km(p);
    }

    Point get_nearest(const Point &p) { //TODO use kd-tree
        double ans = INFINITY, t;
        Point ansp;
        auto id = get_block_id(p);
        int r = id.first, c = id.second;
        int calced = 0;
        for (int step = 1; step < 15; step++) {
            for (int i = max(0, r - step); i <= min(x_num-1, r + step); i++) {
                for (int j = max(0, c - step); j <= min(y_num-1, c + step); j++) {
                    for (Point &b:blk[i][j]) {
                        calced++;
                        if ((t = dist(b, p)) < ans) {
                            ans = t;
                            ansp = b;
                        }
                    }
                }
            }
            if (ans != INFINITY) break;
        }
        if (ans == INFINITY) throw(domain_error("can't find nearest"));
        //cerr << "nearest dist:" << dist(p, ansp) << endl;
        //cerr << "nearest clacnum:" << calced << endl;
        return ansp;
    }
};

#endif //BLOCK_H
