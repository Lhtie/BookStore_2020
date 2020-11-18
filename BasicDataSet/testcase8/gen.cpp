#include <bits/stdc++.h>
using namespace std;

int main(){
	fstream file;
	string contant[100000];
	for (int i = 1; i <= 100; ++i){
		string x = "";
		if (i < 10){
			x = char(i + '0');
		} else if (i < 100) {
			x += char(i / 10 + '0');
			x += char(i % 10 + '0');
		} else x = "100";
		string st = ""; st += x;
		file.open((st + ".txt").c_str(), ios::in);
		int cnt = 0;
		while (getline(file, st)){
			contant[++cnt] = st;
		}
		file.close();
		st += x;
		freopen((st + ".txt").c_str(), "w", stdout);
		cout << "su root sjtu" << '\n';
		for (int j = 1; j <= cnt; ++j)
			cout << contant[j] << '\n';
	}
	return 0;
}
