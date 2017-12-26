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
using namespace std;
class Command {
public:

	virtual void execute(vector<string> args) = 0;
	virtual ~Command() {}
};




#endif /* COMMAND_H_ */
