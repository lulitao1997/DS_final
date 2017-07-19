//
// Created by lulitao on 16-12-14.
//

#ifndef ROAD_H
#define ROAD_H
#include "all.h"
#include "point.h"
#include "read.h"
#include "graph.h"
#include "block.h"

struct road : public vector<Point> {
    const Point &head() {return *begin();}
    const Point &tail() {return *rbegin();}
    double calc_length() {
        Point last = head();
        double ans = 0;
        for (size_t i=1;i<size();i++) {
            ans += dist(last,operator[](i));
            last = operator[](i);
        }
        return ans;
    }
    double d2head(const Point &p) {
        if (p == head()) return 0;
        bool flag = false;
        Point last;
        double ans = 0;
        for (auto i = rbegin(); i!=rend(); i++) {
            if (flag) {
                ans += dist(last, *i);
                last = *i;
            }
            if (*i == p) flag = true;
        }
        if (!flag) throw(domain_error("Point not in this road."));
    }
    double d2tail(const Point &p) {
        if (p == tail()) return 0;
        bool flag = false;
        Point last;
        double ans = 0;
        for (auto &i:*this) {
            if (flag) {
                ans += dist(last, i);
                last = i;
            }
            if (i == p) flag = true;
        }
        if (!flag) throw(domain_error("Point not in this road."));
    }
};

block_idx p_b(INTVX/15, INTVY/15, MINX, MAXX, MINY, MAXY);

vector<road> road_v;

void get_road_network() { // BE AWARE OF ONE-DIRECTION ROAD!!!
    fstream fin("../data/RoadNetwork.csv", ios_base::in);
    CSVrow row;
    fin >> row;
    // X: longitude, Y: latitude
    int road_cnt = 0;

    double max_intv = 0, tot_intv = 0;
    int seg_cnt = 0, ovf_cnt = 0, v_cnt = 0;

    while (fin) {
        road r;
        Point last;
        bool flag = false;
        while (fin >> row && !row.empty()) {
            Point p(stof(row[1]),stof(row[0]));
            if (flag) {
                double intv = dist(p, last);
                int t = intv / MIN_INTV; //insert how many points ?
                //cerr << intv << ' ' << MIN_INTV << endl;
                //cerr << "intv sz: " << t << endl;
                Point delta = (p - last) / (t + 1), tp = last;
                for (int i=0; i<t; i++) {
                    tp = last + delta;
                    r.push_back(tp);
                }
            }
            r.push_back(p);
            last = p;
            flag = true;
        }
        if (r.size() < 2) break;
        road_v.push_back(r);
        G.add_edge(get_point_id(r.head()), get_point_id(r.tail()), r.calc_length(), road_v.size()-1);
        //cerr << "road added " << r.size() << endl;
        /// head -> tail ONE DIRECTION!
    }

    cross_num = pcnt;

    //static int n2rn_cnt[MAXP];
    int maxid = 0;
    for (auto &i:road_v) {
        v_cnt += i.size();
        for (auto &j:i) {
            p_b.insert_point(j);
            int id = get_point_id(j);
            maxid = max(maxid, id);
            //n2rn_cnt[id]++;
            auto &v = n2rn[id];
            if (find(v.begin(),v.end(),road_cnt)==v.end() && v.size()<2)
                v.push_back(road_cnt);
        }
        road_cnt++;
    }
    //cerr << maxid << endl;
    //for (int i=0; i<maxi)
    cerr << "total road number:" << road_cnt << endl;
    cerr << "max intv:" << max_intv << endl;
    cerr << "avg intv:" << tot_intv / seg_cnt << ' ' << ovf_cnt << ' ' << v_cnt << endl;
    cerr << G.vn << ',' << G.en << endl;

    int blk_num = 0;
    size_t p_num = 0, p_max = 0, p_min = 900000;
    for (int i=0; i<p_b.x_num; i++) for (int j=0; j<p_b.y_num; j++) {
            size_t t = p_b.blk[i][j].size();
            p_num += t;
            p_min = min(p_min, t);
            p_max = max(p_max, t);
        }
    cerr << "blk info:" << "avg: " << (double)p_num/p_b.x_num/p_b.y_num << "\nmin,max: " << p_min << ',' << p_max << endl;
    cerr << "x,y num" << p_b.x_num << ',' << p_b.y_num << endl;

    calc_connect_block();
}

pair<int, double> get_nearest_graphp(const Point &p) {
    double ansd = INFINITY, t;
    Point np = p_b.get_nearest(p);
    int po = get_point_id(np);
    if (po <= G.vn) return make_pair(po,0.0);
    int ans = 0;
    for (auto i:n2rn[po]) if ((t = road_v[i].d2tail(np)) < ansd) {
            ansd = t;
            ans = get_point_id(road_v[i].tail());
        }
    return make_pair(ans, ansd);
}

double graph::shortest_path(const Point &S, const Point &T) {
    auto ps = get_nearest_graphp(S), pt = get_nearest_graphp(T);
    double ans = ps.second + shortest_path(ps.first, pt.first) + pt.second;
//    if (ans > 500) {
//        cerr << ps.second << ":" << shortest_path(ps.first, pt.first) << ":" << pt.second << endl;
//    }
    return ans;
}

pair<int, double> graph::Dijkstra(const Point &p, const vector<pair<int,double>> &V) {
    auto pa = get_nearest_graphp(p);
    if (V.size() > 100 || 1) {
        auto ans = Dijkstra(pa.first, V);
        ans.second += pa.second;
        return ans;
    };
    int ans;
    double ansd = INFINITY, t;
    for (int i=0; i<V.size(); i++) {
        if ((t = shortest_path(pa.first,V[i].first) + V[i].second) < ansd) {
            ansd = t;
            ans = i;
        }
    }
    return make_pair(ans, ansd + pa.second);
};



#endif //ROAD_H
