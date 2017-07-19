//
// Created by lulitao on 17-1-5.
//

#ifndef RESTAURANT_H
#define RESTAURANT_H
#include "all.h"
#include "point.h"
#include "wread.h"
struct restaurant {
    Point pos;
    wstring name;
    vector<wstring> tag;

    explicit restaurant(const wCSVrow &r) : pos(stod(r[2]),stod(r[3])), name(r[0]) {
        const wstring &s = r[1];
        wstring ele;
        wstringstream s_in(s);
        while (getline(s_in, ele, L';')) {
            if (tag.empty() || ele != *tag.rbegin())
                tag.push_back(ele);
        }
    }

    bool operator== (const restaurant &b) const {
        return name == b.name;
    }
};

vector<restaurant> r_v;

void get_POI() {
    wfstream fin("../data/test.csv", ios_base::in);
    wCSVrow r;
    fin >> r;
    while (fin >> r) {
        r_v.push_back(restaurant(r));
    }
}


#endif //TOPIC_A_RESTAURANT_H
