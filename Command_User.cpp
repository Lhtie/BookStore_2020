#include "BookStore.h"

userClass::userClass(string userID_, string name_, char authority_, string password_) :
					userID(userID_), name(name_), authority(authority_), password(password_) {}
void userClass::read_file(int pointer) {
	fstream file;
	file.open("Data_User.dat", ios::in | ios::out | ios::binary);
	file.seekg(pointer * 91);
	read_string(file, userID, 30);
	read_string(file, name, 30);
	file.read(&authority, 1);
	read_string(file, password, 30);
	file.close();
}
void userClass::write_file() const {
	fstream file;
	file.open("Data_User.dat", ios::in | ios::out | ios::app | ios::binary);
	write_string(file, userID, 30);
	write_string(file, name, 30);
	file.write(&authority, 1);
	write_string(file, password, 30);
	file.close();
}
void userClass::login(string userID, string password) {
	vector<int> index = Userid.readIndexData(userID, '0');
	fstream file;
	file.open("Data_User.dat", ios::in | ios::out | ios::binary);
	file.seekg(index[0] * 91 + 61);
	string password_origin;
	read_string(file, password_origin, 30);
	if (password == password_origin || password == "#"){
		file.seekg(index[0] * 91);
		read_string(file, this->userID, 30);
		read_string(file, this->name, 30);
		file.read(&this->authority, 1);
		read_string(file, this->password, 30);
		login_user.push(make_pair(*this, -1));
		in_stack[userID] = true;
	} else ERROR;
	file.close();
}
void userClass::logout() {
	if (login_user.top().first.userID == "noname"){
		ERROR; return ;
	}
	in_stack[current_user.userID] = false;
	login_user.pop();
	current_user = login_user.top().first;
	current_book = login_user.top().second;
}
void userClass::userAdd(userClass t) {
	Userid.writeIndexData(t.userID, data_manager.createUserData(t), '0');
}
void userClass::Delete(string userID) {
	vector<int> index = Userid.readIndexData(userID, '0');
	if (index.size() == 1) {
		if (!in_stack[userID])
			Userid.deleteIndexData(userID, index[0], '0');
		else ERROR;
	} else ERROR;
}
void userClass::changePassword(string userID, string newPass, string oldPass) {
	vector<int> index = Userid.readIndexData(userID, '0');
	fstream file;
	file.open("Data_User.dat", ios::in | ios::binary);
	file.seekg(index[0] * 91 + 61);
	string password_origin;
	read_string(file, password_origin, 30);
	if (oldPass == password_origin || oldPass == "#"){
		data_manager.changeUserData(newPass, index[0]);
		if (this->userID == userID) this->password = newPass;
	} else ERROR;
	file.close();
}
void userClass::reportMyself() const {
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	string content_, userID_; char status_, authority_; long long time_; int n; double income_, expend_;
	file.seekg(24);
	file.read(reinterpret_cast<char *> (&n), 4);
	puts("Reporting Myself---------------------------------------");
	for (int i = 1; i <= n; ++i){
		read_string(file, content_, 250);
		read_string(file, userID_, 31);
		file.read(&status_, 1);
		file.read(&authority_, 1);
		file.read(reinterpret_cast<char *> (&time_), 8);
		file.read(reinterpret_cast<char *> (&income_), 8);
		file.read(reinterpret_cast<char *> (&expend_), 8);
		if (userID_ == userID) {
			if (status_ == '1') {
				cout << "I successfully operated a command: " << content_ << " at time: " << time_ << endl;
			} else {
				cout << "I attempted to operate: " << content_ << " but failed at time: " << time_ << endl;
			}
		}
	}
	puts("Self Report ends---------------------------------------");
	file.close();
}
