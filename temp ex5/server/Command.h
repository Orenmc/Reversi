/*
 * Command.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>
#include "GameRoom.h"
#include <unistd.h>
using namespace std;
#include <pthread.h>


class Command {

public:

	virtual void execute(vector<string> args,vector<GameRoom> &GR,pthread_mutex_t lock,int socket = 0) = 0;
	virtual ~Command() {}

};




#endif /* COMMAND_H_ */
