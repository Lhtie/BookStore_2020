#include "BookStore.h"
#include <sstream>
#include <algorithm>

vector<string> decompose_keyword(string arg){
	vector<string> ans;
	int len = arg.length();
	for (int i = 0; i < len; ++i){
		string keyword;
		for (; i < len && arg[i] != '|'; ++i)
			keyword += arg[i];
		ans.push_back(keyword);
	}
	sort(ans.begin(), ans.end());
	return ans;
}

bookClass::bookClass(string ISBN_, string name_, string author_, string keyword_, double price_, int num_) :
					ISBN(ISBN_), name(name_), author(author_), keyword(keyword_), price(price_), num(num_) {}
void bookClass::read_file(int pointer) {
	fstream file;
	file.open("Data_Book.dat", ios::in | ios::out | ios::binary);
	file.seekg(pointer * 216);
	read_string(file, ISBN, 21);
	read_string(file, name, 61);
	read_string(file, author, 61);
	read_string(file, keyword, 61);
	file.read(reinterpret_cast<char *> (&price), 8);
	file.read(reinterpret_cast<char *> (&num), 4);
	file.close();
}
void bookClass::write_file() {
	fstream file;
	file.open("Data_Book.dat", ios::in | ios::out | ios::app | ios::binary);
	write_string(file, ISBN, 21);
	write_string(file, name, 61);
	write_string(file, author, 61);
	write_string(file, keyword, 61);
	file.write(reinterpret_cast<char *> (&price), 8);
	file.write(reinterpret_cast<char *> (&num), 4);
	file.close();
}
void bookClass::print_book() const {
	cout << ISBN << '\t' << name << '\t' << author << '\t' << keyword << '\t';
	printf("%.2lf\t%d\n", price, num);
}
bool bookClass::decompose_input(string arg) {
	int len = arg.length();
	for (int i = 0; i < len; ++i){
		if (arg[i] == '-') {
			string command, value;
			for (i++; i < len && arg[i] != '='; ++i)
				command += arg[i];
			if (arg[++i] == '"') {
				for (++i; i < len && arg[i] != '"'; ++i)
					value += arg[i];
			} else {
				for (; i < len && arg[i] != ' '; ++i)
					value += arg[i];
			}
			if (command == "ISBN" && value.size() <= 20) ISBN = value;
			else if (command == "name" && value.size() <= 60) name = value;
			else if (command == "author" && value.size() <= 60) author = value;
			else if (command == "keyword" && value.size() <= 60) keyword = value;
			else if (command == "price"){
				stringstream str(value);
				str >> price;
			} else return false;
		}
	}
	return true;
}
void bookClass::select(string ISBN) {
	vector<int> index = Isbn.readIndexData(ISBN, '1');
	if (index.size() == 1)
		current_book = login_user.top().second = index[0];
	else {
		int id = data_manager.createBookData(ISBN);
		Isbn.writeIndexData(ISBN, id, '1');
		current_book = login_user.top().second = id;
	}
}
void bookClass::modify(string arg) {
	if (current_book == -1) {ERROR; return ;}
	this->read_file(current_book);
	bookClass new_book;
	new_book.price = -1;
	if (!new_book.decompose_input(arg)) {ERROR; return ;}
	if (!new_book.keyword.empty()) {	//Judge keyword before modification
		vector<string> part = decompose_keyword(new_book.keyword);
		bool valid = true;
		for (int i = 1; i < part.size(); ++i)
			if (part[i] == part[i-1]) {ERROR; return ;}
	}
	if (!new_book.ISBN.empty()) {
		vector<int> index = Isbn.readIndexData(new_book.ISBN, '1');
		if (index.size() == 0){
			Isbn.writeIndexData(this->ISBN, new_book.ISBN, current_book, '1');
			data_manager.changeBookData(new_book.ISBN, current_book, '1');
		} else {ERROR; return ;}
	}
	if (!new_book.name.empty()) {
		Name.writeIndexData(this->name, new_book.name, current_book, '2');
		data_manager.changeBookData(new_book.name, current_book, '2');
	}
	if (!new_book.author.empty()) {
		Author.writeIndexData(this->author, new_book.author, current_book, '3');
		data_manager.changeBookData(new_book.author, current_book, '3');
	}
	if (!new_book.keyword.empty()){
		vector<string> part = decompose_keyword(this->keyword);
		for (int i = 0; i < part.size(); ++i)
			Keyword.deleteIndexData(part[i], current_book, '4');
		part = decompose_keyword(new_book.keyword);
		for (int i = 0; i < part.size(); ++i)
			Keyword.writeIndexData(part[i], current_book, '4');
		data_manager.changeBookData(new_book.keyword, current_book, '4');
	}
	if (new_book.price != -1){
		data_manager.changeBookData(new_book.price, current_book);
	}
}
void bookClass::import(int num, double price) {
	if (current_book == -1) {ERROR; return ;}
	expend += price;
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	file.seekp(8);
	file.write(reinterpret_cast<char *> (&expend), 8);
	file.close();
	this->read_file(current_book);
	this->num += num;
	data_manager.changeBookData(this->num, current_book);
	data_manager.recordFinance(1, price);
}
void bookClass::buy(string ISBN, int num) {
	vector<int> index = Isbn.readIndexData(ISBN, '1');
	if (index.size() != 1) {ERROR; return ;}
	this->read_file(index[0]);
	if (this->num >= num) {
		this->num -= num;
		data_manager.changeBookData(this->num, index[0]);
		income += num * price;
		printf("%.2lf\n", num * price);
		fstream file;
		file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
		file.seekp(16);
		file.write(reinterpret_cast<char *> (&income), 8);
		file.close();
		data_manager.recordFinance(0, num * price);
	} else ERROR;
}
void bookClass::show(string arg) {
	bookClass required;
	if (!required.decompose_input(arg)) {ERROR; return ;}
	vector<int> total, index;
	bool initialized = false;
	if (!required.ISBN.empty()){
		index = Isbn.readIndexData(required.ISBN, '1');
		if (!initialized) total = index, initialized = true;
		else {
			vector<int> res;
			sort(total.begin(), total.end());
			sort(index.begin(), index.end());
			set_intersection(total.begin(), total.end(), index.begin(), index.end(), back_inserter(res));
			total = res;
		}
	}
	if (!required.name.empty()){
		index = Name.readIndexData(required.name, '2');
		if (!initialized) total = index, initialized = true;
		else {
			vector<int> res;
			sort(total.begin(), total.end());
			sort(index.begin(), index.end());
			set_intersection(total.begin(), total.end(), index.begin(), index.end(), back_inserter(res));
			total = res;
		}
	}
	if (!required.author.empty()){
		index = Author.readIndexData(required.author, '3');
		if (!initialized) total = index, initialized =  true;
		else {
			vector<int> res;
			sort(total.begin(), total.end());
			sort(index.begin(), index.end());
			set_intersection(total.begin(), total.end(), index.begin(), index.end(), back_inserter(res));
			total = res;
		}
	}
	if (!required.keyword.empty()){
		index = Keyword.readIndexData(required.keyword, '4');
		if (!initialized) total = index, initialized = true;
		else {
			vector<int> res;
			sort(total.begin(), total.end());
			sort(index.begin(), index.end());
			set_intersection(total.begin(), total.end(), index.begin(), index.end(), back_inserter(res));
			total = res;
		}
	}
	vector<pair<string, int> > pool;
	for (int i = 0; i < total.size(); ++i){
		this->read_file(total[i]);
		pool.push_back(make_pair(this->ISBN, total[i]));
	}
	sort(pool.begin(), pool.end());
	for (int i = 0; i < pool.size(); ++i){
		this->read_file(pool[i].second);
		this->print_book();
	}
	if (!pool.size()) puts("");
}
void bookClass::show() {
	vector<pair<string, int> > pool;
	for (int i = 0; i < total_book; ++i){
		this->read_file(i);
		pool.push_back(make_pair(this->ISBN, i));
	}
	sort(pool.begin(), pool.end());
	for (int i = 0; i < pool.size(); ++i){
		this->read_file(pool[i].second);
		this->print_book();
	}
	if (!pool.size()) puts("");
}
void bookClass::showFinance(int num) const {
	int n = 0;
	fstream file;
	file.open("Data_Finance.dat", ios::in | ios::binary);
	file.read(reinterpret_cast<char *> (&n), 4);
	if (n >= num){
		double ret_income = 0, ret_expand = 0;
		for (int i = n - 1; i >= n - num; --i){
			file.seekg(4 + i * 9);
			bool type; double money;
			file.read(reinterpret_cast<char *> (&type), 1);
			file.read(reinterpret_cast<char *> (&money), 8);
			if (!type) ret_income += money;
			else ret_expand += money;
		}
		printf("+ %.2lf - %.2lf\n", ret_income, ret_expand);
	} else ERROR;
	file.close();
}
void bookClass::showFinance() const {
	printf("+ %.2lf - %.2lf\n", income, expend);
}
