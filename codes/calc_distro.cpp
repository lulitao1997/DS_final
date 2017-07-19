#include <bits/stdc++.h>
using namespace std;
vector<double> A;

double len = 60*60;

int cnt[24];

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

int main() {
	time_hms t;
	string s;double x;
	while (cin>>s>>x) {
		t.get(s);
		double i = t.sec_count();
		for (int j = 0; j < 24; j++) {
			if (j*len+0.01 < i && i < (j+1)*len )
				cnt[j]++;
		}
	}
	for (int i = 0; i<24; i++) {
		cout << i*len << "~" << (i+1)*len << "," << cnt[i] << endl; 
	}
}
