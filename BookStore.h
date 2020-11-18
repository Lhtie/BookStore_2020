#ifndef BOOKSTORE_2020_BOOKSTORE_H
#define BOOKSTORE_2020_BOOKSTORE_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define ERROR success = '0', puts("Invalid")
void init();
void read_string(fstream &file, string &str, int total_len);
void write_string(fstream &file, string str, int total_len);
class commandClass;
class userClass;
class bookClass;
class unrolledLinkedListClass;
class dataClass;

class commandClass{
	friend class dataClass;
private:
	string content, userID;
	char status, authority;
	long long time;
public:
	explicit commandClass(string content_ = "", string userID_ = "", char status_ = ' ', char authority = ' ', long long time_ = 0);
	void runCommand(string arg);
	void reportFinance() const;
	void reportEmployee() const;
	void log() const;
};

class userClass{
	friend void commandClass::runCommand(string arg);
	friend int main();
private:
	string userID, name, password;
	char authority;
public:
	explicit userClass(string userID_ = "", string name_ = "", char authority_ = '0', string password_ = "");
	void read_file(int pointer);
	void write_file() const;
	void login(string userID, string password = "#");
	void logout();
	void userAdd(userClass t);
	void Delete(string userID);
	void changePassword(string userID, string newPass, string oldPass = "#");
	void reportMyself() const;
};

class bookClass{
private:
	string ISBN, name, author, keyword;
	double price;
	int num;
public:
	explicit bookClass(string ISBN_ = "", string name_ = "", string author_ = "", string keyword_ = "", double price = 0, int num_ = 0);
	void read_file(int pointer);
	void write_file();
	void print_book() const;
	bool decompose_input(string arg);
	void select(string ISBN);
	void modify(string arg);
	void import(int num, double price);
	void buy(string ISBN, int num);
	void show(string arg);
	void show();
	void showFinance(int num) const;
	void showFinance() const;
};

class unrolledLinkedListClass{
private:
	const static int Block_Size;
	pair<int, int> hash(string arg);
	vector<pair<pair<int, int>, int> > Cache;
public:
	explicit unrolledLinkedListClass(char type);
	void writeIndexData(string arg, int pointer, char type);
	void writeIndexData(string oldArg, string newArg, int pointer, char type);
	vector<int> readIndexData(string arg, char type);
	void deleteIndexData(string arg, int pointer, char type);
};

class dataClass{
public:
	int createUserData(userClass t);
	void changeUserData(string password, int pointer);
	int createBookData(string ISBN);
	void changeBookData(string arg, int pointer, char type);
	void changeBookData(double price, int pointer);
	void changeBookData(int num, int pointer);
	void recordFinance(bool type, double money);
	void recordCommand(commandClass	command_manager);
};

extern stack<pair<userClass, int> > login_user;
extern map<string, bool> in_stack;
extern userClass current_user;
extern double expend, income;
extern int current_book, total_account, total_book;
extern char success;

extern dataClass data_manager;
extern unrolledLinkedListClass Userid, Isbn, Author, Name, Keyword;

#endif //BOOKSTORE_2020_BOOKSTORE_H
