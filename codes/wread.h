//
// Created by lulitao on 17-1-5.
//

#ifndef WREAD_H
#define WREAD_H
#include "all.h"

class wCSVrow : public vector<wstring> {
    friend wistream &operator>>(wistream &str, wCSVrow &data);
private:
    void get_row(wistream &src) {
        wstring buf, ele;
        getline(src, buf);
//        src >> buf;
        if (!buf.empty()) buf.pop_back();
        wstringstream s_in(buf);

        while (getline(s_in, ele, L','))
            push_back(ele);
    }
};
wistream &operator>>(wistream& str, wCSVrow &data) {
    data.clear();
    data.get_row(str);
    return str;
}

#endif //TOPIC_A_WREAD_H
