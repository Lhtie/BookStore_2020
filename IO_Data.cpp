#include "BookStore.h"

int dataClass::createUserData(userClass t) {
	t.write_file();
	total_account++;
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	file.seekp(0, ios::beg);
	file.write(reinterpret_cast<char *> (&total_account), 4);
	file.close();
	return total_account - 1;
}
void dataClass::changeUserData(string password, int pointer) {
	fstream file;
	file.open("Data_User.dat", ios::in | ios::out | ios::binary);
	file.seekp(pointer * 91 + 61);
	write_string(file, password, 30);
	file.close();
}
int dataClass::createBookData(string ISBN) {
	bookClass book(ISBN, "", "", "", 0);
	book.write_file();
	total_book++;
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	file.seekp(4);
	file.write(reinterpret_cast<char *> (&total_book), 4);
	file.close();
	return total_book - 1;
}
void dataClass::changeBookData(string arg, int pointer, char type) {
	fstream file;
	file.open("Data_Book.dat", ios::in | ios::out | ios::binary);
	int pos = pointer * 216;
	if (type > '1') pos += 21 + (type - '1' - 1) * 61;
	file.seekp(pos);
	write_string(file, arg, type == '1' ? 21 : 61);
	file.close();
}
void dataClass::changeBookData(double price, int pointer) {
	fstream file;
	file.open("Data_Book.dat", ios::in | ios::out | ios::binary);
	file.seekp(pointer * 216 + 21 + 61 * 3);
	file.write(reinterpret_cast<char *> (&price), 8);
	file.close();
}
void dataClass::changeBookData(int num, int pointer) {
	fstream file;
	file.open("Data_Book.dat", ios::in | ios::out | ios::binary);
	file.seekp(pointer * 216 + 21 + 61 * 3 + 8);
	file.write(reinterpret_cast<char *> (&num), 4);
	file.close();
}
void dataClass::recordFinance(bool type, double money) {
	fstream file; int n;
	file.open("Data_Finance.dat", ios::in | ios::out | ios::binary);
	file.read(reinterpret_cast<char *> (&n), 4);
	file.seekp(4 + n * 9);
	file.write(reinterpret_cast<char *> (&type), 1);
	file.write(reinterpret_cast<char *> (&money), 8);
	n++;
	file.seekp(0);
	file.write(reinterpret_cast<char *> (&n), 4);
	file.close();
}
void dataClass::recordCommand(commandClass command_manager) {
	fstream file;
	file.open("Data_Basic.dat", ios::in | ios::out | ios::binary);
	int num;
	file.seekg(24);
	file.read(reinterpret_cast<char *> (&num), 4);
	num++;
	file.seekp(24);
	file.write(reinterpret_cast<char *> (&num), 4);
	file.seekp(0, ios::end);
	write_string(file, command_manager.content, 250);
	write_string(file, command_manager.userID, 31);
	file.write(&command_manager.status, 1);
	file.write(&command_manager.authority, 1);
	file.write(reinterpret_cast<char *> (&command_manager.time), 8);
	file.write(reinterpret_cast<char *> (&income), 8);
	file.write(reinterpret_cast<char *> (&expend), 8);
	file.close();
}
