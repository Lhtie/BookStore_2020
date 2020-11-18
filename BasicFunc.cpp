#include "BookStore.h"
#include <sstream>

stack<pair<userClass, int> > login_user;
map<string, bool> in_stack;
userClass current_user;
double expend, income;
int current_book, total_account, total_book;
char success;

dataClass data_manager;
unrolledLinkedListClass Userid('0'), Isbn('1'), Name('2'), Author('3'), Keyword('4');

void init(){
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::binary);
	if (!file){
		file.open("Data_Basic.dat", ios::out | ios::binary);
		int num = 0; char *address = reinterpret_cast<char *> (&num);
		file.write(address, 4), file.write(address, 4);
		double num_ = 0; char *address_ = reinterpret_cast<char *> (&num_);
		file.write(address_, 8), file.write(address_, 8), file.write(address, 4);
		file.close();
		file.open("Data_Finance.dat", ios::out | ios::binary);
		file.write(address, 4);
		file.close();
		userClass noname("noname", "noname", '0', "");
		Userid.writeIndexData("noname", data_manager.createUserData(noname), '0');
		userClass root("root", "root", '7', "sjtu");
		Userid.writeIndexData("root", data_manager.createUserData(root), '0');
	} else {
		file.close();
	}
	current_user.login("noname", "");
	current_book = -1;
	file.open("Data_Basic.dat", ios::in | ios::binary);
	file.read(reinterpret_cast<char *> (&total_account), 4);
	file.read(reinterpret_cast<char *> (&total_book), 4);
	file.read(reinterpret_cast<char *> (&expend), 8);
	file.read(reinterpret_cast<char *> (&income), 8);
	file.close();
}
void read_string(fstream &file, string &str, int total_len){
	char c;
	str.clear();
	for (int i = 0; i < total_len; ++i){
		file.read(&c, 1);
		if (c != ' ') str += c;
	}
}
void write_string(fstream &file, string str, int total_len){
	char VOID = ' '; int len = str.length();
	for (int i = 0; i < len; ++i) {
		char c = str[i];
		file.write(&c, 1);
	}
	for (int i = 1; i <= total_len - len; ++i)
		file.write(&VOID, 1);
}

commandClass::commandClass(string content_, string userID_, char status_, char authority_, long long time_)
						: userID(userID_), status(status_), authority(authority_), time(time_)
{
	int len = content_.length();
	for (int i = 0; i < len; ++i)
		if (content_[i] == ' ') content_[i] = '_';
	content = content_;
}
void commandClass::runCommand(string arg) {
	int len = arg.length(), i = 0;
	success = '1';
	string type;
	for (; i < len && arg[i] != ' '; ++i) type += arg[i];
	if (type == "su"){
		string user_id, passwd;
		for (++i; i < len && arg[i] != ' '; ++i) user_id += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) passwd += arg[i];
		if (user_id.size() <= 30 && passwd.size() <= 30){
			vector<int> index = Userid.readIndexData(user_id, '0');
			if (index.size() == 1) {
				userClass new_account;
				new_account.read_file(index[0]);
				if (passwd.empty()) {
					if (current_user.authority >= new_account.authority)
						current_user.login(user_id);
					else ERROR;
				} else current_user.login(user_id, passwd);
			} else ERROR;
		} else ERROR;
	} else if (type == "logout"){
		current_user.logout();
	} else if (type == "useradd"){
		string user_id, passwd, name; char authority_;
		for (++i; i < len && arg[i] != ' '; ++i) user_id += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) passwd += arg[i];
		authority_ = arg[++i], ++i;
		for (++i; i < len && arg[i] != ' '; ++i) name += arg[i];
		if (user_id.size() <= 30 && passwd.size() <= 30 && name.size() <= 30) {
			userClass new_account(user_id, name, authority_, passwd);
			vector<int> index = Userid.readIndexData(user_id, '0');
			if (current_user.authority >= '3' && current_user.authority > new_account.authority && index.empty())
				current_user.userAdd(new_account);
			else ERROR;
		} else ERROR;
	} else if (type == "register"){
		string user_id, passwd, name;
		for (++i; i < len && arg[i] != ' '; ++i) user_id += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) passwd += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) name += arg[i];
		if (user_id.size() <= 30 && passwd.size() <= 30 && name.size() <= 30) {
			userClass new_account(user_id, name, '1', passwd);
			vector<int> index = Userid.readIndexData(user_id, '0');
			if (index.empty()) current_user.userAdd(new_account);
		} else ERROR;
	} else if (type == "delete"){
		string user_id;
		for (++i; i < len && arg[i] != ' '; ++i) user_id += arg[i];
		if (user_id.size() <= 30 && current_user.authority >= '7') {
			current_user.Delete(user_id);
		} else ERROR;
	} else if (type == "passwd"){
		string user_id, oldpass, newpass;
		for (++i; i < len && arg[i] != ' '; ++i) user_id += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) oldpass += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) newpass += arg[i];
		if (user_id.size() <= 30 && oldpass.size() <= 30 && newpass.size() <= 30) {
			if (newpass.empty()) {
				if (current_user.authority >= '7')
					current_user.changePassword(user_id, oldpass);
				else ERROR;
			} else {
				if (current_user.authority >= '1') current_user.changePassword(user_id, newpass, oldpass);
				else ERROR;
			}
		} else ERROR;
	} else if (type == "select"){
		string ISBN;
		for (++i; i < len && arg[i] != ' '; ++i) ISBN += arg[i];
		if (ISBN.size() <= 20 && current_user.authority >= '3') {
			bookClass book; book.select(ISBN);
		} else ERROR;
	} else if (type == "modify"){
		string command;
		for (++i; i < len; ++i) command += arg[i];
		if (current_user.authority >= '3') {
			bookClass book; book.modify(command);
		} else ERROR;
	} else if (type == "import"){
		string value1, value2; int quantity; double cost_price;
		for (++i; i < len && arg[i] != ' '; ++i) value1 += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) value2 += arg[i];
		stringstream str1(value1), str2(value2);
		str1 >> quantity, str2 >> cost_price;
		if (current_user.authority >= '3') {
			bookClass book; book.import(quantity, cost_price);
		} else ERROR;
	} else if (type == "show"){
		if (i >= len || arg[i+1] == '-') {
			string command;
			for (++i; i < len; ++i) command += arg[i];
			if (current_user.authority >= '1') {
				bookClass book;
				if (command.empty()) book.show();
				else book.show(command);
			} else ERROR;
		} else {
			type.clear();
			for (++i; i < len && arg[i] != ' '; ++i) type += arg[i];
			if (type == "finance"){
				string value; int times;
				for (++i; i < len && arg[i] != ' '; ++i) value += arg[i];
				if (current_user.authority >= '7') {
					bookClass book;
					if (value.empty()) book.showFinance();
					else {
						stringstream str(value);
						str >> times;
						book.showFinance(times);
					}
				} else ERROR;
			} else ERROR;
		}
	} else if (type == "buy"){
		string ISBN, value; int quantity;
		for (++i; i < len && arg[i] != ' '; ++i) ISBN += arg[i];
		for (++i; i < len && arg[i] != ' '; ++i) value += arg[i];
		stringstream str(value); str >> quantity;
		if (ISBN.size() <= 20 && current_user.authority >= '1') {
			bookClass book; book.buy(ISBN, quantity);
		} else ERROR;
	} else if (type == "report") {
		string command;
		for (++i; i < len && arg[i] != ' '; ++i) command += arg[i];
		if (command == "finance"){
			if (current_user.authority >= '7') this->reportFinance();
			else ERROR;
		} else if (command == "employee"){
			if (current_user.authority >= '7') this->reportEmployee();
			else ERROR;
		} else if (command == "myself"){
			if (current_user.authority >= '3') current_user.reportMyself();
			else ERROR;
		} else ERROR;
	} else if (type == "log") {
		if (current_user.authority >= '3') this->log();
		else ERROR;
	} else ERROR;
	this->status = success;
//	data_manager.recordCommand(*this);
}
void commandClass::reportFinance() const {
	puts("Reporting Finance--------------------------------------");
	printf("Total income: + %.2lf Total expense: - %.2lf\n", income, expend);
	if (income > expend) printf("Your bookstore gains profits up to %.2lf !\n", income - expend);
	else printf("Your bookstore doesn't run well !\n");
	puts("Finance Report ends------------------------------------");
}
void commandClass::reportEmployee() const {
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	string content_, userID_; char status_, authority_; long long time_; int n; double income_, expend_;
	file.seekg(24);
	file.read(reinterpret_cast<char *> (&n), 4);
	puts("Reporting Employee-------------------------------------");
	for (int i = 1; i <= n; ++i){
		read_string(file, content_, 250);
		read_string(file, userID_, 31);
		file.read(&status_, 1);
		file.read(&authority_, 1);
		file.read(reinterpret_cast<char *> (&time_), 8);
		file.read(reinterpret_cast<char *> (&income_), 8);
		file.read(reinterpret_cast<char *> (&expend_), 8);
		if (authority_ == '3') {
			if (status_ == '1') {
				cout << "Employee " << userID_ << " successfully operated a command: " << content_ << " at time: " << time_
					 << endl;
			} else {
				cout << "Employee" << userID_ << " attempted to operate: " << content_ << " but failed at time: " << time_
					 << endl;
			}
		}
	}
	puts("Employee Report ends-----------------------------------");
	file.close();
}
void commandClass::log() const {
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	string content_, userID_; char status_, authority_; long long time_; int n;
	double income_last = 0, expend_last = 0, income_, expend_;
	file.seekg(24);
	file.read(reinterpret_cast<char *> (&n), 4);
	puts("Reporting Employee-------------------------------------");
	for (int i = 1, Case = 0; i <= n; ++i){
		read_string(file, content_, 250);
		read_string(file, userID_, 31);
		file.read(&status_, 1);
		file.read(&authority_, 1);
		file.read(reinterpret_cast<char *> (&time_), 8);
		file.read(reinterpret_cast<char *> (&income_), 8);
		file.read(reinterpret_cast<char *> (&expend_), 8);
		if (authority_ >= '1') {
			cout << "COMMAND #" << ++Case << ":" << endl;
			cout << userID_ << " required to " << content_ << " at time: " << time_ << endl;
			cout << "This line of command was "
				 << (status_ == '0' ? "rejected and ignored..." : "approved and successfully operated!") << endl;
			if (income_ > income_last) {
				printf("After this operation, the BookStore earned %.2lf !\n", income_ - income_last);
			}
			if (expend_ > expend_last) {
				printf("This operation cost the BookStore %.2lf ...\n", expend_ - expend_last);
			}
			cout << endl;
		}
		income_last = income_, expend_last = expend_;
	}
	puts("Employee Report ends-----------------------------------");
	file.close();
}
