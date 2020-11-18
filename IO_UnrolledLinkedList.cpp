#include "BookStore.h"

const int KEY[2] = {393241, 786433};
const int MOD = 998244353;
const int unrolledLinkedListClass::Block_Size = 1000;
const string FileName[5] = {"Index_Userid.dat", "Index_ISBN.dat", "Index_Name.dat", "Index_Author.dat", "Index_Keyword.dat"};

pair<int, int> unrolledLinkedListClass::hash(string arg) {
	int hash[2];
	for (int type = 0; type < 2; ++type){
		hash[type] = 0;
		for (int i = 0; i < arg.length(); ++i) {
			hash[type] = int(((long long)hash[type] * KEY[type] + arg[i] - '0') % MOD);
		}
	}
	return make_pair(hash[0], hash[1]);
}
unrolledLinkedListClass::unrolledLinkedListClass(char type) {
	Cache.clear();
	fstream file;
	file.open(FileName[type-'0'], ios::in | ios::binary);
	if (!file){
		file.open(FileName[type-'0'], ios::out | ios::binary);
		int num = 1, VOID = 0;
		file.write(reinterpret_cast<char *> (&num), 4);
		file.write(reinterpret_cast<char *> (&VOID), 4);
		file.write(reinterpret_cast<char *> (&VOID), 4);
		file.close();
		Cache.push_back(make_pair(make_pair(0, 0), 0));
		return ;
	}
	int n;
	file.read(reinterpret_cast<char *> (&n), 4);
	for (int i = 0; i < n; ++i) {
		file.seekg(4 + i * (8 + Block_Size * 12));
		int next, size, first, second;
		file.read(reinterpret_cast<char *> (&next), 4);
		file.read(reinterpret_cast<char *> (&size), 4);
		file.read(reinterpret_cast<char *> (&first), 4);
		file.read(reinterpret_cast<char *> (&second), 4);
		Cache.push_back(make_pair(make_pair(first, second), next));
	}
	file.close();
}
void unrolledLinkedListClass::writeIndexData(string arg, int pointer, char type) {
	pair<int, int> key = hash(arg);
	int p = 0;
	while (Cache[p].second && Cache[Cache[p].second].first <= key)
		p = Cache[p].second;
	fstream file;
	file.open(FileName[type - '0'], ios::in | ios::out | ios::binary);
	file.seekg(4 + p * (8 + Block_Size * 12));
	int next, n;
	vector<pair<pair<int, int>, int> > value;
	file.read(reinterpret_cast<char *> (&next), 4);
	file.read(reinterpret_cast<char *> (&n), 4);
	for (int i = 0; i < n; ++i) {
		pair<pair<int, int>, int> tmp;
		file.read(reinterpret_cast<char *> (&tmp.first.first), 4);
		file.read(reinterpret_cast<char *> (&tmp.first.second), 4);
		file.read(reinterpret_cast<char *> (&tmp.second), 4);
		value.push_back(tmp);
	}
	if (n == 0){
		value.push_back(make_pair(key, pointer));
		n++;
		file.seekp(4 + p * (8 + Block_Size * 12) + 4);
		file.write(reinterpret_cast<char *> (&n), 4);
		file.write(reinterpret_cast<char *> (&value[0].first.first), 4);
		file.write(reinterpret_cast<char *> (&value[0].first.second), 4);
		file.write(reinterpret_cast<char *> (&value[0].second), 4);
		Cache[p].first = key;
	} else {
		int pos = 0;
		while (pos < n && value[pos].first <= key) pos++;
		value.push_back(value[n - 1]);
		for (int i = n - 1; i >= pos + 1; --i) value[i] = value[i-1];
		value[pos] = make_pair(key, pointer);
		if (pos == 0) Cache[p].first = key;
		n++;
		if (n > Block_Size){
			int n_new = n / 2, next_new = next;
			n -= n_new;
			vector<pair<pair<int, int>, int> > value_new;
			for(int i = n; i < n + n_new; ++i) value_new.push_back(value[i]);
			int total;
			file.seekg(0);
			file.read(reinterpret_cast<char *> (&total), 4);
			next = total++;
			Cache[p].second = next;
			file.seekp(0);
			file.write(reinterpret_cast<char *> (&total), 4);
			Cache.push_back(make_pair(value_new[0].first, next_new));
			file.seekp(4 + (total - 1) * (8 + Block_Size * 12));
			file.write(reinterpret_cast<char *> (&next_new), 4);
			file.write(reinterpret_cast<char *> (&n_new), 4);
			for (int i = 0; i < n_new; ++i){
				file.write(reinterpret_cast<char *> (&value_new[i].first.first), 4);
				file.write(reinterpret_cast<char *> (&value_new[i].first.second), 4);
				file.write(reinterpret_cast<char *> (&value_new[i].second), 4);
			}
		}
		file.seekp(4 + p * (8 + Block_Size * 12));
		file.write(reinterpret_cast<char *> (&next), 4);
		file.write(reinterpret_cast<char *> (&n), 4);
		for (int i = 0; i < n; ++i){
			file.write(reinterpret_cast<char *> (&value[i].first.first), 4);
			file.write(reinterpret_cast<char *> (&value[i].first.second), 4);
			file.write(reinterpret_cast<char *> (&value[i].second), 4);
		}
	}
	file.close();
}
void unrolledLinkedListClass::writeIndexData(string oldArg, string newArg, int pointer, char type) {
	if (!oldArg.empty()) this->deleteIndexData(oldArg, pointer, type);
	if (!newArg.empty()) this->writeIndexData(newArg, pointer, type);
}
vector<int> unrolledLinkedListClass::readIndexData(string arg, char type) {
	pair<int, int> key = hash(arg);
	int p = 0;
	while (Cache[p].second && Cache[Cache[p].second].first < key)
		p = Cache[p].second;
	vector<int> ret;
	fstream file;
	file.open(FileName[type - '0'], ios::in | ios::out | ios::binary);
	do {
		file.seekg(4 + p * (8 + Block_Size * 12));
		int next, n;
		vector<pair<pair<int, int>, int> > value;
		file.read(reinterpret_cast<char *> (&next), 4);
		file.read(reinterpret_cast<char *> (&n), 4);
		if (!n) break;
		for (int i = 0; i < n; ++i) {
			pair<pair<int, int>, int> tmp;
			file.read(reinterpret_cast<char *> (&tmp.first.first), 4);
			file.read(reinterpret_cast<char *> (&tmp.first.second), 4);
			file.read(reinterpret_cast<char *> (&tmp.second), 4);
			value.push_back(tmp);
		}
		for (int i = 0; i < n; ++i)
			if (value[i].first == key && value[i].second != -1)
				ret.push_back(value[i].second);
		p = Cache[p].second;
	} while(p && Cache[p].first == key);
	file.close();
	return ret;
}
void unrolledLinkedListClass::deleteIndexData(string arg, int pointer, char type) {
	pair<int, int> key = hash(arg);
	int p = 0;
	while (Cache[p].second && Cache[Cache[p].second].first < key)
		p = Cache[p].second;
	fstream file;
	file.open(FileName[type-'0'], ios::in | ios::out | ios::binary);
	do {
		file.seekg(4 + p * (8 + Block_Size * 12));
		int next, n;
		vector<pair<pair<int, int>, int> > value;
		file.read(reinterpret_cast<char *> (&next), 4);
		file.read(reinterpret_cast<char *> (&n), 4);
		if (!n) break;
		for (int i = 0; i < n; ++i) {
			pair<pair<int, int>, int> tmp;
			file.read(reinterpret_cast<char *> (&tmp.first.first), 4);
			file.read(reinterpret_cast<char *> (&tmp.first.second), 4);
			file.read(reinterpret_cast<char *> (&tmp.second), 4);
			value.push_back(tmp);
		}
		for (int i = 0; i < n; ++i)
			if (value[i].first == key && value[i].second == pointer)
				value[i].second = -1;
		file.seekp(4 + p * (8 + Block_Size * 12) + 8);
		for (int i = 0; i < n; ++i) {
			file.write(reinterpret_cast<char *> (&value[i].first.first), 4);
			file.write(reinterpret_cast<char *> (&value[i].first.second), 4);
			file.write(reinterpret_cast<char *> (&value[i].second), 4);
		}
		p = Cache[p].second;
	} while(p && Cache[p].first == key);
	file.close();
}
