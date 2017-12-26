/*
 * PrintCommand.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "Command.h"
#include <iostream>

class StartCommand: public Command {
public:

	virtual void execute(vector<string> args) {
		cout << "create game: " << args[1] << endl;
	}
};




#endif /* STARTCOMMAND_H_ */
