#include "read.h"
#include "point.h"
#include "road.h"
#include "graph.h"
#include "order.h"
//#include "imported/nanoflann.hpp"
using namespace std;

//typedef pair<int, pair<Point, Point>> order;
///<time_count, start_p, end_p>

void analyse_driver_income() { // Topic A.1
    fstream fDIR("driver_income_report.csv", ios_base::out);
    fstream fID("income_distribution.csv", ios_base::out);
    fstream fOL("order_list.csv", ios_base::out);
    vector<pair<time_hms, double>> income_v;
    vector<order> order_v;
    double minx = INFINITY, maxx = 0, miny = INFINITY, maxy = 0;
    for (int i=6961;i<=12843;i++) {
        string filename = "[part-00000][" + to_string(i) + "]Sample.csv", buf;
        cerr << filename << endl;
        fstream fin("../data/Trajectory/" + filename, ios_base::in);
        CSVrow row;
        fin >> row >> row;
        Point last = Point(stod(row[3]),stod(row[4])), now = last;
        time_hms start_t;
        bool lin = !stoi(row[6]);
        if (lin) start_t.get(row[1]);
        double income = 0, travel_dist = 0, psg_dist = 0;
        Point start_p, end_p;
        while (fin >> row) {
            now = Point(stod(row[3]),stod(row[4]));
            minx = min(minx, now.longitude);
            maxx = max(maxx, now.longitude);
            miny = min(miny, now.latitude);
            maxy = max(maxy, now.latitude);
            bool nin = lin;
            if (row[13].find("TakeIn")!=string::npos) {
                nin = true;
                start_p = now;
                start_t.get(row[1]);
            }
            else if (row[13].find("TakeOff")!=string::npos) {
                nin = false;
                end_p = now;
                order_v.push_back((order){start_t.sec_count() , start_p, end_p});
            }
            double t = dist(now, last);
            travel_dist += t;
            if (lin && nin) {
                psg_dist += t;
            }
            if (lin && !nin && psg_dist > 0.1) {
                double now_inc = calc_income(psg_dist);
                income += now_inc;
//                cerr << "psg_dist:" << psg_dist << endl;
                income_v.push_back(make_pair(start_t, now_inc));
                psg_dist = 0;
            }

            lin = nin;
            last = now;
        }
        income -= travel_dist*0.5;
        fDIR << i << ',' << income << ',' << travel_dist << endl;
        fin.close();
    }
    sort(order_v.begin(), order_v.end(), [](order a,order b){
        return a.time_cnt < b.time_cnt;});
    sort(income_v.begin(), income_v.end(), [](pair<time_hms, double> a, pair<time_hms, double> b){
        return a.first < b.first;});
    for (auto &i:order_v)
        if (i.start_p == Point(0,0)) continue;
        else fOL << max(0, i.time_cnt - 5 * 60) << ',' << i.start_p << ',' << i.end_p << endl;
    for (auto &i:income_v) fID << i.first << ',' << i.second << endl;
    cerr << minx << ',' << maxx << ':' << miny << ',' << maxy << endl;
}

block_idx order_b(INTVX/2, INTVY/2, MINX, MAXX, MINY, MAXY);

vector<int> n2on;

vector<order> order_v;

vector<order> trans2order_v(const vector<Point> &v) {
    vector<order> ans;
    for (auto p:v)
        ans.push_back(order_v[n2on[get_point_id(p)]]);
    return ans;
}

void negative_strategy() { // Topic A.2
    order_v = get_order();
    /*
    // Test get_nearest() //
    // order num 20w+, missed point ~1k, ok.
//    double min_ne = INFINITY, max_ne = 0;
//    for (auto &o:order_v) {
//        Point &p = o.start_p;
//        try {
//            double t = dist(p, p_b.get_nearest(p));
//            min_ne = min(min_ne, t);
//            max_ne = max(max_ne, t);
//        }
//        catch (...) {
//            cerr << p << endl;
//        }
//
//    }
//    cerr << min_ne << ',' << max_ne << endl;
//    cerr << "finished" <<endl;
    /
    // Test shortest_path() //
//    int err_num = 0;
//    for (auto &o:order_v) {
//        try {
//            //Point s = p_b.get_nearest(o.start_p), t = p_b.get_nearest(o.end_p);
//
//            //cerr << "::" << get_road_id(s).size() << ':' << get_road_id(t).size() << endl;
//            double ans = G.shortest_path(o.start_p, o.end_p);
//            err_num += ans == INFINITY;
//            cerr << "sp = " << ans << endl;
//        }
//        catch (...) {
//            err_num++;
//        }
//    }
//    cerr << "sp err num: " << err_num << endl;
*/
    /********************************/
    fstream fo("negative_strategy_report_income_distribution.csv", ios_base::out);
    n2on.clear();
    n2on.resize(MAXP);
    for (int i=0; i<order_v.size(); i++)
        n2on[get_point_id(order_v[i].start_p)] = i;
    for (int case_n = 0; case_n < 4000; case_n++) {
        cerr << "nowcase:" << case_n << endl;
        Point now_p = n2p[rand() % G.vn + 1];
        int order_front = 0, order_end = 0;
        double now_t = 0;

        //clear
        order_b.clear();
        for (int i = 0; i < order_v.size(); i++)
            order_b.insert_point(order_v[i].start_p);

        vector<order> in_3km;
        fstream fout("./negative_strategy/income_time_" + to_string(case_n) + ".csv", ios_base::out);

        double income = 0;
        while (order_front < order_v.size() && now_t < 24 * 60 * 60) {
            /*
            if (case_n > 60) {
                cerr << "now:" << now_p << ',' << order_front << endl;
                cerr << "time: " << order_v[order_front].time_cnt << ":"
                     << order_v[order_front].start_p << "," << order_v[order_front].end_p << endl;
            }
            */
            while (order_end < order_v.size() && order_v[order_end].time_cnt < now_t - 60 * 15) {
                // if waited more than 15min, cancel that order
                order_b.erase_point(order_v[order_end].start_p);
                order_end++;
            }
            if (order_end >= order_v.size()) break;
            if (order_front < order_end) order_front = order_end;
            while (order_front < order_v.size() && order_v[order_front].time_cnt < now_t) {
                const order &n = order_v[order_front];
                if (dist(n.start_p, now_p) < 3) {
                    in_3km.push_back(n);
                }
                order_front++;
            }
            if (order_front >= order_v.size()) break;
            if (!in_3km.empty()) {
                //find nearest point in graph
                vector<pair<int, double>> in_3km_v;
                for (auto o:in_3km) in_3km_v.push_back(get_nearest_graphp(o.start_p));
                auto pa = G.Dijkstra(now_p, in_3km_v);
                const order &obj = in_3km[pa.first];

                // go to that point, delete that order, update now_t, clear in_3km, calc income.
                order_b.erase_point(obj.start_p);
                double sp = G.shortest_path(obj.start_p, obj.end_p);
                double inc_dis = pa.second + sp;
                now_t += inc_dis / 40 * 60 * 60;
                now_p = obj.end_p;
                income += calc_income(sp) - inc_dis * 0.5;
                fout << now_t << ',' << calc_income(sp) - sp * 0.5 << endl;
                in_3km = trans2order_v(order_b.get_in_3km(now_p));
            }
            else { // wait till order appear in 3km
                while (order_front < order_v.size() && dist(order_v[order_front].start_p, now_p) >= 3) {
                    now_t = order_v[order_front].time_cnt;
                    order_front++;
                }
                if (order_front >= order_v.size()) break;
                in_3km.push_back(order_v[order_front]);
            }
        }
        fo << income << endl;
    }
}


//const int TIME_INTV = 25;// every 25 seconds

//const int INTV_P = INTV_T * 40 / MIN_INTV;

queue<int> vis_rn;
bool ban_r[MAXN];

bool fucked = false;

queue<Point> gen_random_path(const Point &np) { // return a path
//    cerr << "aaaa" << endl;
    fucked = false;
    while (vis_rn.size() > 40) {
        ban_r[vis_rn.front()] = false;
        vis_rn.pop();
    }
    Point p = p_b.get_nearest(np);
    int v = get_point_id(road_v[get_road_id(p)[0]].tail());
    queue<Point> ans;
    ans.push(np);
    if (np != n2p[v]) ans.push(n2p[v]);
    for (int i=0; i<10; i++) {// randomly go 10 roads
        bool finded = false;
        for (graph::edge *e=G.st[v]; e; e=e->n) {
            if (!ban_r[e->rn]) {
                //vis.insert(e->t);
                finded = true;
                vis_rn.push(e->rn);
                ban_r[e->rn] = true;
                for (auto t:road_v[e->rn]) {
                        ans.push(t);
                    }
                v = e->t;
                break;
            }
        }
        if (!finded) {
            fucked = true;
            break;
        }
    }
    if (!ans.empty())ans.pop();
    if (ans.empty()) {
        while (!vis_rn.empty()) {
            ban_r[vis_rn.front()] = false;
            vis_rn.pop();
        }
        return gen_random_path(np);
    }
    return ans;
}

void positive_strategy() { // Topic A.3
    order_v = get_order();
    fstream fo("positive_strategy_report_income_distribution.csv", ios_base::out);
    n2on.clear();
    n2on.resize(MAXP);
    for (int i=0; i<order_v.size(); i++)
        n2on[get_point_id(order_v[i].start_p)] = i;
    queue<Point> path;
    for (int case_n = 0; case_n < 4000; case_n++) {
        cerr << "nowcase:" << case_n << endl;
        Point now_p = n2p[rand() % G.vn + 1];
        int order_front = 0, order_end = 0;
        double now_t = 0, travel_dis = 0;

        //clear
        order_b.clear();
        for (int i = 0; i < order_v.size(); i++)
            order_b.insert_point(order_v[i].start_p);

        vector<order> in_3km;
        fstream fout("./positive_strategy/income_time_" + to_string(case_n) + ".csv", ios_base::out);

        double income = 0;
        int eq_cnt = 0;
        double last_t = -1, last_income = -1;
        while (order_front < order_v.size() && now_t < 24 * 60 * 60) {
//            if (case_n > 60 || 1) {
//                cerr << "now:" << now_p << ',' << order_front << endl;
//                cerr << "time: " << order_v[order_front].time_cnt << ":"
//                     << order_v[order_front].start_p << "," << order_v[order_front].end_p << endl;
//            }
//            while (order_end < order_v.size() && order_v[order_end].time_cnt < now_t - 60 * 15) {
//                // if waited more than 15min, cancel that order
//                order_b.erase_point(order_v[order_end].start_p);
//                order_end++;
//            }
            if (eq_cnt > 10) break;
            if (order_end >= order_v.size()) break;
            if (order_front < order_end) order_front = order_end;
            while (order_front < order_v.size() && order_v[order_front].time_cnt < now_t) {
                const order &n = order_v[order_front];
                if (dist(n.start_p, now_p) < 3) {
                    in_3km.push_back(n);
                }
                order_front++;
            }
            if (order_front >= order_v.size()) break;

            if (!in_3km.empty()) {
                //find nearest point in graph
                vector<pair<int, double>> in_3km_v;
                for (auto o:in_3km) in_3km_v.push_back(get_nearest_graphp(o.start_p));
                auto pa = G.Dijkstra(now_p, in_3km_v);
                const order &obj = in_3km[pa.first];

                // go to that point, delete that order, update now_t, clear in_3km, calc income.
                order_b.erase_point(obj.start_p);
                double sp = G.shortest_path(obj.start_p, obj.end_p);
                now_t += (pa.second + sp) / 40 * 60 * 60;
                travel_dis += (pa.second + sp);
                now_p = obj.end_p;
                double income_inc =calc_income(sp) - sp*0.5;
                income += income_inc;
                fout << now_t << ',' << income_inc << endl;
                in_3km = trans2order_v(order_b.get_in_3km(now_p));
                if (fabs(now_t - last_t) < 1e-5 && fabs(income_inc - last_income) < 1e-5)
                    eq_cnt++;
                else eq_cnt = 0;
                last_t = now_t;
                last_income = income_inc;
            }
            else { // wander till meet an order
                int cnt = 0;
                double inc_t = 0;
                while (order_b.get_in_3km(now_p).empty() && inc_t < 30*60 ) {
                    // if no order after 30 min break;
//                    cnt++;
//                    if (cnt > 10) {
//                        cerr << now_p << endl << path.size();
//                    }
//                    cerr << now_p << ":::::" << endl;
                    if (path.empty()) path = gen_random_path(now_p);
                    if (fucked) break;
                    Point &next_p = path.front();
                    double inc_dis = dist(now_p, next_p);
                    inc_t += inc_dis / 10 * 60 * 60;
                    travel_dis += inc_dis;
                    now_p = next_p;
                    path.pop();
                }
                in_3km = trans2order_v(order_b.get_in_3km(now_p));
                now_t += inc_t;
            }
            if (fucked) { // if stucked, wait
                while (order_front < order_v.size() && dist(order_v[order_front].start_p, now_p) >= 3) {
                    now_t = order_v[order_front].time_cnt;
                    order_front++;
                }
                if (order_front >= order_v.size()) break;
                in_3km.push_back(order_v[order_front]);
            }
        }
        fo << income << endl;
    }
}

void test();

int main() {
    srand(92874);
    get_road_network();
    test();
//    analyse_driver_income();
//    negative_strategy();
//    positive_strategy();
}

void test() {
    cerr << "::::" << G.en << ":::" << G.vn << endl;
    cerr << G.shortest_path(Point(121.511936,31.302662), Point(121.60196,31.19398)) << endl; //FD-handan => FD-zhangjiang //20km
    cerr << G.shortest_path(Point(121.511936,31.302662), Point(121.481022,31.235086)) <<endl ; //FD-handan => Renming Square //11.6km
    cerr << G.shortest_path(Point(121.598293,31.205633), Point(121.481022,31.235086)) << endl; //ErFuZhong => Renming Square //16km
    cerr << G.shortest_path(Point(121.60544,31.195045), Point(121.607421,31.211632)) << endl; //FD-Zhangjiang => ChangTai Square //2.3km
//    cerr << n2p[60018] << ':' << n2p[18749] << endl;
    cerr << G.Dijkstra(Point(121.511936,31.302662), {get_nearest_graphp(Point(121.60196,31.19398))}).second << endl;
    cerr << G.Dijkstra(Point(121.511936,31.302662), {get_nearest_graphp(Point(121.481022,31.235086))}).second <<endl ;
    cerr << G.Dijkstra(Point(121.598293,31.205633), {get_nearest_graphp(Point(121.481022,31.235086))}).second << endl; //ErFuZhong => Renming Square //16km
    cerr << G.Dijkstra(Point(121.60544,31.195045), {get_nearest_graphp(Point(121.607421,31.211632))}).second << endl; //FD-Zhangjiang => Chang
    for (auto &r:road_v) for (auto &p:r) p_b.get_nearest(p);
}
