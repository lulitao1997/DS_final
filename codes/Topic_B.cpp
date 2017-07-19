//
// Created by lulitao on 17-1-1.
//
#include "all.h"
//#include "road.h"
#include "graph.h"
#include "road.h"
#include "restaurant.h"
#include "order.h"
void test();

double dis_score(double dis) {
    if (dis < 0.1) return 10;
    if (dis < 1) return 7;
    if (dis < 2) return 6;
    return 3;
}
double dis_coef(double dis) {
    if (dis < 0.2) return 1;
    if (dis < 1) return 0.9;
    if (dis < 2) return 0.8;
    return 0.7;
}

block_idx r_b(INTVX,INTVY,MINX,MAXX,MINY,MAXY);

unordered_map<hash_type, int> p2rn;

double score[MAXR];

void calc_score() {
    vector<order> vo = get_order();
    get_POI();
    int rcnt = 0;
    for (auto &r:r_v) {
        r_b.insert_point(r.pos);
        p2rn[Point_hash(r.pos)] = rcnt++;
    }

    vector<Point> ans;
    int calc_num = 0;
    for (auto &o:vo) {
        ans = r_b.get_in_3km(o.end_p);
        for (auto i:ans) {
            int n = p2rn[Point_hash(i)];
            score[n] += dis_score(dist(o.end_p, i));
        }
        if (++calc_num % 100 == 0) cerr << calc_num << endl;
    }
    ofstream fout("restaurant_score.csv", ios_base::out);
    for (int i = 0; i < rcnt; i++) {
        fout << score[i] << endl;
    }
}


void get_score() {
    ifstream fin("restaurant_score.csv", ios_base::in);
    for (int i=0; i<136322; i++) fin >> score[i];
}

wstring hint = L"请输入指令，\n1 + (x,y)：推荐附近商店（按距离）"\
               L"2:推荐附近商店（综合）\n3 + tag：筛选列表n；\n" \
               L"==========================================\n";

Point cmp_p;

double dis2p[MAXR];

struct cmp_struct {
    bool operator() (int a, int b) const {
        return dis2p[a] < dis2p[b];
    }
};

struct cmp_struct2 {
    bool operator() (int a, int b) const {
        return score[a] * dis_coef(dis2p[a]) > score[b] * dis_coef(dis2p[b]);
    }
};

double sp2(const Point &s, const Point &t) {
    if (dist(s,t) < 1) return dist(s, t);
    return G.shortest_path(s,t);
}

int main() {
    std::locale::global(std::locale(""));
//    calc_score();
    get_road_network();
    get_POI();
    get_score();

    int rcnt = 0;
    int tnum = 0;
    for (auto &r:r_v) {
        r_b.insert_point(r.pos);
//        if (r.name == L"悦仙茶栈") tnum++;
        p2rn[Point_hash(r.pos)] = rcnt++;
    }
//    cerr <<"tnum:" << tnum << endl;
    wcout << hint << endl;
    int cmd;
    vector<int> nv;
    Point np;
    cerr << r_b.size << endl;
    while (wcin >> cmd) {
        vector<Point> in_3km;
        if (cmd == 1) {
            wcin >> np.longitude >> np.latitude;
            cerr << np << endl;
            in_3km.clear();
            in_3km = r_b.get_in_3km_norm(np);
            cerr << in_3km.size() << endl;
            cmp_p = np;
            nv.clear();
            for (auto i:in_3km) {
                int t = p2rn[Point_hash(i)];
                dis2p[t] = sp2(np, i);
                if (dis2p[t] < 500)
                    nv.push_back(p2rn[Point_hash(i)]);
            }
            //for (auto i:nv) dis2p[i] = G.shortest_path(r_v[i].pos, np);
            sort(nv.begin(), nv.end(), cmp_struct());
        }
        else if (cmd ==2) {
            wcin >> np.longitude >> np.latitude;
            in_3km.clear();
            in_3km = r_b.get_in_3km_norm(np);
            cmp_p = np;
            nv.clear();
            int ttt = 0;
            for (auto i:in_3km) {
//                ttt += dist(i, Point(121.579,31.2033)) < 0.03;
                int t = p2rn[Point_hash(i)];
                dis2p[t] = sp2(np, i);
                if (dis2p[t] < 500)
                    nv.push_back(p2rn[Point_hash(i)]);
            }
            for (auto i:nv) dis2p[i] = G.shortest_path(r_v[i].pos, np);
            sort(nv.begin(), nv.end(), cmp_struct2());
            cerr << "ttt:::" << ttt << endl;
            //while (1);
        }
        else if (cmd ==3) {
            wstring tag;
            wcin >> tag;
            vector<int> tmp;
            for (auto r:nv) if (find(r_v[r].tag.begin(), r_v[r].tag.end(), tag) != r_v[r].tag.end())
                    tmp.push_back(r);
            nv = tmp;
        }
//        for (auto &i:nv) {
//            wcout << i.name << ':' << endl;
//        }

        system("clear");
        wcout << hint << endl;

        cerr << "nv.size(): " << nv.size() << endl;
        unique(nv.begin(), nv.end());
        int cnt = 0;
        double max_dis = 0;
        for (auto &r:nv) {
            wcout << ++cnt << ". " << r_v[r].name << endl;
            wcout << "(" << in_3km[cnt-1].longitude <<"," << in_3km[cnt-1].latitude<< endl;
            wcout << dis2p[r] << endl;
            for (int i=0; i<cnt-1; i++) max_dis = max(max_dis, dist(r_v[nv[i]].pos, r_v[r].pos));
            if (cnt > 10) break;
        }
        if (max_dis < 1) {
            int cnt2 = 11;
            for (;cnt < nv.size() && cnt2 < 15; cnt++) {
                if (dist(r_v[nv[cnt]].pos, r_v[nv[0]].pos) > 1) {
                    wcout << ++cnt2 << ". " << r_v[nv[cnt]].name << endl;
                }
            }
        }
    }
//    test();
}

void test() {
        cerr << G.shortest_path(Point(121.511936,31.302662), Point(121.60196,31.19398)); //FD-handan => FD-zhangjiang //20km
    cerr << G.shortest_path(Point(121.511936,31.302662), Point(121.481022,31.235086)); //FD-handan => Renming Square //11.6km
    cerr << G.shortest_path(Point(121.598293,31.205633), Point(121.481022,31.235086)); //ErFuZhong => Renming Square //16km
    cerr << G.shortest_path(Point(121.60544,31.195045), Point(121.607421,31.211632)); //FD-Zhangjiang => ChangTai Square //2.3km

}