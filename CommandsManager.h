/*
 * CommandsManager.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_

#include <map>
#include "Command.h"

class CommandsManager {
public:
	CommandsManager();
	~CommandsManager();
	void executeCommand(string command,vector<string> args);
private:
	map<string, Command *> commandsMap;
};


#endif /* COMMANDSMANAGER_H_ */
