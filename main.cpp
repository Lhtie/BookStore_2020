#include "BookStore.h"

int main() {
	init();
	string command;
	while (getline(cin, command)){
		if (command == "quit" || command == "exit") break;
		commandClass command_manager(command, current_user.userID, ' ', current_user.authority, time(nullptr));
		command_manager.runCommand(command);
	}
	return 0;
}
