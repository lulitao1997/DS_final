//
// Created by lulitao on 17-1-5.
//

#ifndef ORDER_H
#define ORDER_H
#include "all.h"
#include "point.h"
#include "read.h"
struct order {
    int time_cnt;
    Point start_p, end_p;
};

vector<order> get_order() {
    fstream fin("order_list.csv", ios_base::in);
    CSVrow row;
    vector<order> ans;
    while (fin >> row) {
        Point start_p = Point(stod(row[1]),stod(row[2])), end_p = Point(stod(row[3]), stod(row[4]));
        if (start_p != Point(0,0) && end_p != Point(0,0))
                ans.push_back((order){stoi(row[0]), start_p, end_p});
    }
    return ans;
}

#endif //TOPIC_A_ORDER_H
