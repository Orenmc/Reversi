/*
 * CommandsManager.cpp
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#include "CommandsManager.h"
#include "GameRoom.h"
#include "ListGameCommand.h"
#include "StartCommand.h"
#include "JoinCommand.h"




CommandsManager* CommandsManager::instance = 0;
pthread_mutex_t CommandsManager::lock;
pthread_mutex_t CommandsManager::GR_lock;

CommandsManager* CommandsManager::getInstance() {
	if (instance == 0) {
		pthread_mutex_lock(&lock);
		if (instance == 0) {
			instance = new CommandsManager();
		}
		pthread_mutex_unlock(&lock);
	}
	return instance;
}

CommandsManager::CommandsManager() {
	commandsMap["list_games"] = new ListGamesCommand();
	commandsMap["start"] = new StartCommand();
	commandsMap["join"] = new JoinCommand();


	// Add more commands...
}


void CommandsManager::executeCommand(string command, vector<string> args, int socket) {

	Command *commandObj = commandsMap[command];
	commandObj->execute(args,this->vGR,GR_lock,socket);
}

CommandsManager::CommandsManager(const CommandsManager&) {
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it !=
			commandsMap.end(); it++) {
		delete it->second;
	}
}
