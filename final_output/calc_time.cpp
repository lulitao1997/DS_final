#include <bits/stdc++.h>
using namespace std;

double income[24];

int cnt[24];

string pre = "./positive_strategy/income_time_";
double len = 60*60;

int main() {
	for (int i=0; i<4000; i++) {
		ifstream fin(pre + to_string(i) + ".csv");
		double t, c;
		while (fin>>t) {
			fin.get();
			fin>>c;
//			cerr << t << ":::" << c << endl;
			for (int j=0;j<24;j++) {
				if (j*len+0.01 < t && t < (j+1)*len ) {
					cnt[j]++;	
					income[j]+=c;
				}
			}
		}
		fin.close();
	}
	for (int i=0; i<24; i++) {
		cout << i*len << "~" << (i+1)*len << "," << cnt[i] << "," << income[i] << endl; 
	}
}
