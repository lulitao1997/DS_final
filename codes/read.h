//
// Created by lulitao on 16-12-14.
//

#ifndef READ_H
#define READ_H
#include "all.h"

class CSVrow : public vector<string> {
    friend istream &operator>>(istream &str, CSVrow &data);
private:
    void get_row(istream &src) {
        string buf, ele;
        getline(src, buf);
        if (!buf.empty()) buf.pop_back();
        stringstream s_in(buf);

        while (getline(s_in, ele, ','))
            push_back(ele);
    }
};
istream &operator>>(istream& str, CSVrow &data) {
    data.clear();
    data.get_row(str);
    return str;
}

struct time_hms { //almost all the time is in the day 2015-04-01
    int hour, minute, second;
    bool operator<(const time_hms &b) const {
        return hour != b.hour ? hour < b.hour :
               minute != b.minute ? minute < b.minute :
               second < b.second;
    }
    void get(const string &s) { //get rid of date, expected input:"2015-04-01 00:27:39"
        size_t pos = s.find(' ');
        sscanf(s.c_str() + (pos == string::npos ? 0 : pos),"%d:%d:%d",&hour,&minute,&second);
    }
    time_hms minus_5min() {
        if (minute < 5) {
            if (hour < 1) throw("time out of range!");
            return (time_hms){hour-1, minute+55, second};
        }
        return (time_hms){hour, minute-5, second};
    }
    int sec_count() const {
        return hour * 60 * 60 + minute * 60 + second;
    }
};
ostream &operator <<(ostream &out,const time_hms &a) {
    out << a.hour << ':' << a.minute << ':' << a.second;
}
#endif //READ_H
