/*
 * PrintCommand.h
 *
 *  Created on: Dec 21, 2017
 *      Author: snirhazan
 */

#ifndef LISTGAMECOMMAND_H_
#define LISTGAMECOMMAND_H_

#include "Command.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;

class ListGamesCommand: public Command {
public:

	virtual void execute(vector<string> args,vector<GameRoom> &GR,pthread_mutex_t lock, int socket){

		char result[50] ="";

		pthread_mutex_lock(&lock);
		unsigned size = GR.size();
		for(int i =0 ; (unsigned)i < size ; i++){
			if(GR[i].getCounter() == 1){
				strcat(result,GR[i].getName().c_str());
				strcat(result," ");
			}
		}
		int n = write(socket,&result,strlen(result)+1);
		if(n== -1) {
			cout << "Error write to socket" << endl;
		}
		pthread_mutex_unlock(&lock);


		close(socket);
	}
};




#endif /* LISTGAMECOMMAND_H_ */
