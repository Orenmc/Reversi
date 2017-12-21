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

	virtual void execute(vector<string> args) {
		for (int i = 0; (unsigned)i < args.size(); i++) {
			cout << args[i] << " ";
		}
		cout << endl;
	}
};




#endif /* PRINTCOMMAND_H_ */
