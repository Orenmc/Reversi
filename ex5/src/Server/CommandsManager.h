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
#include "GameRoom.h"

class CommandsManager {
public:
	static CommandsManager* getInstance();
	void executeCommand(string command,vector<string> args, int socket = 0);
private:
	CommandsManager();
	CommandsManager(const CommandsManager &);
	~CommandsManager();
	static CommandsManager* instance;
	static pthread_mutex_t lock;
	static pthread_mutex_t GR_lock;

	vector<GameRoom> vGR;
	map<string, Command *> commandsMap;
};


#endif /* COMMANDSMANAGER_H_ */
