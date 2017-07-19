//
// Created by lulitao on 16-12-22.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "all.h"
#include "point.h"

int ff(int x);

struct graph {
    void add_edge(int u, int v, double w, int rn) {
        vn = max(vn, max(u, v));
        st[u] = new(&pool[en++])edge(v, w, st[u], rn);
    }
    void clear() {
        memset(st, 0, sizeof st);
        memset(pool, 0, sizeof pool);
        en = vn = 0;
    }
    double shortest_path(int S, int T);
    double shortest_path(const Point &S, const Point &T);

    bool to_calc[MAXN];
    pair<int,double> Dijkstra(int S, const vector<pair<int,double>> &V);
    pair<int, double> Dijkstra(const Point &p, const vector<pair<int,double>> &V);
    struct edge {
        int t;
        double w;
        edge *n;

        int rn;

        edge(int t = 0, double w = 0, edge *n = nullptr, int rn = 0):t(t), w(w), n(n), rn(rn) {}
    };
    edge *st[MAXN];
    edge pool[MAXE];
    int vn, en;

    bool vis[MAXN], inq[MAXN]; // vis: closed set, inq: open set
    double F[MAXN], G[MAXN];
} G;

//wrong!
//struct v_cmp {
//    bool operator()(int u, int v) {
//        return G.F[u] > G.F[v];
//    }
//};
double graph::shortest_path(int S, int T) { // A* algorithm
    //cerr << "sp called: " << S << ',' << T << endl;
//    if (ff(S) != ff(T)) return 0;
    static vector<int> changed;
    const Point &endp = n2p[T];
    typedef pair<double,int> pdi;
    priority_queue<pdi, vector<pdi>, greater<pdi>> open_set;
    F[S] = dist(n2p[S],n2p[T]);
    open_set.push(make_pair(0.0,S));
    inq[S] = true;
    changed.push_back(S);
    while (!open_set.empty()) {
//        if (changed.size() > 10000) break;
        pdi p = open_set.top();
        open_set.pop();
        int f = p.second;
        if (f == T) break;
        if (vis[f]) continue;
        inq[f] = false;
        vis[f] = true;
        //if (f == T) break;
        for (edge *i = st[f]; i; i = i->n) {
            int y = i->t;
            bool better = false;
            if (vis[y]) continue;
            double approx_dis = G[f] + i->w;
            if (!inq[y]) {
                changed.push_back(y);
                inq[y] = true;
                better = true;
            }
            else better = approx_dis < G[y];

            if (better) {
                G[y] = approx_dis;
                F[y] = G[y] + dist(n2p[y], endp); // haha, use explicit to find this error! y => n2p[y]
                open_set.push(make_pair(F[y], y));
            }
        }
    }
    double ans = G[T];

//    cerr << "changed num:" << changed.size() << endl;
    if (!inq[T]) ans = INFINITY;
    for (auto i:changed) { //restore
        vis[i] = inq[i] = false;
        F[i] = G[i] = 0;
    }
    changed.clear();
//    if (!vis[T]) return INFINITY;
    return ans;
    //throw(domain_error("place can not be reached"));
}

pair<int,double> graph::Dijkstra(int S, const vector<pair<int,double>> &V) { /// return (i,dis) s.t. V_i is nearest.
    //return a vector<double> : min_dist to S
    typedef pair<double, int> pdi;
    priority_queue<pdi,vector<pdi>,greater<pdi>> Q;
    static vector<int> changed;
    Q.push(make_pair(0.0,S));
    changed.push_back(S);
    int done_num = to_calc[S], Vsz = V.size();
    for (auto i:V) {
        to_calc[i.first] = true;
        if (ff(S) != ff(i.first)) Vsz--;
    }
    while (!Q.empty() && done_num<Vsz) {
        int f = Q.top().second;
        Q.pop();
        if (vis[f]) continue;
        vis[f] = true;
        done_num += to_calc[f];
        for (edge *e=st[f]; e; e=e->n) {
            int t = e->t;
            if (!vis[t]) {
                F[t] = F[f] + e->w;
                Q.push(make_pair(F[t],t));
                changed.push_back(t);
            }
        }

        //inq[f] = false;
    }

    double ans_dis = INFINITY;
    int ans = 0;
    for (size_t i=0; i<V.size(); i++) {
        if (vis[V[i].first] && F[V[i].first] + V[i].second < ans_dis) {
            ans_dis = F[V[i].first] + V[i].second;
            ans = i;
        }
        to_calc[V[i].first] = false;
    }

//    cerr << "changed:" << changed.size() << endl;
    for (auto i:changed) {
        F[i] = 0.0;
        vis[i] = false;
    }
    changed.clear();
    if (ans_dis == INFINITY) ans_dis = 0;
    return make_pair(ans,ans_dis);
}


int F[MAXN];
int bsz[MAXN];
int ff(int x) {
    return F[x] ? (F[x] = ff(F[x])) : x;
}
int calc_connect_block() { // just_for_test
    for (int i=1;i<=G.vn;i++) {
        for (graph::edge *e=G.st[i];e;e=e->n) {
            int t = e->t;
            //cerr << "(u,v) : " << i << ',' << t << endl;
            if (ff(i) != ff(t)) F[ff(i)] = ff(t);
        }
    }
    int ans = 0;
    for (int i=1;i<=G.vn;i++) {
        ans += (ff(i) == i);
        bsz[ff(i)]++;
    }
//    for (int i=1;i<=G.vn;i++) {
//        if (ff(i) == i) cerr << bsz[i] << endl;
//    }
    return ans;
}


#endif //GRAPH_H
