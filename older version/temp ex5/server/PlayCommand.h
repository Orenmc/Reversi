/*
 * PrintCommand.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "Command.h"
#include <iostream>

class PlayCommand: public Command {
public:

	virtual void execute(vector<string> args) {
		if(args.size() != 2) {
			cout << "not goot optin" << endl;
		} else {
			cout << "row is: " << args[0] << " " << "col is: " << args[1] << endl;
		}
	}
};




#endif /* PLAYCOMMAND_H_ */
