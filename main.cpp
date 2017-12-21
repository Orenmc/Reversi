/*
 * main.cpp
 *
 *  Created on: Dec 21, 2017
 *      Author: oren
 */

#include "CommandsManager.h"
#include <vector>
#include <string>
int main() {
	CommandsManager cm =  CommandsManager();
	vector<string> vs;
	string  x,y;
	x = "1";
	y = "2";
	vs.push_back(x);
	vs.push_back(y);

	cm.executeCommand("play",vs);


	return 1;
}

