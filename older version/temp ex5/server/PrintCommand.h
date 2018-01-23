/*
 * PrintCommand.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef PRINTCOMMAND_H_
#define PRINTCOMMAND_H_

#include "Command.h"
#include <iostream>

class PrintCommand: public Command {
public:

	virtual void execute(vector<string> args){
		string name = args[1];
		cout << "game name is: " << name << endl;
	}
};




#endif /* PRINTCOMMAND_H_ */
