#include <bits/stdc++.h>
using namespace std;
vector<double> A;

double len = 100;

int cnt[100];

int main() {
	double x;
	while (cin>>x) A.push_back(x);
	for (double i:A) {
		for (int j = 0; j < 50; j++) {
			if (j*len+0.01 < i && i < (j+1)*len )
				cnt[j]++;
		}
	}
	for (int i = 0; i<50; i++) {
		cout << i*len << "~" << (i+1)*len << "," << cnt[i] << endl; 
	}
}
