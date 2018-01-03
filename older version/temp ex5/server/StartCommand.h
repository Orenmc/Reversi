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

	virtual void execute(vector<string> args,vector<GameRoom> &GR,pthread_mutex_t lock, int socket) {
		char result[100] = "good1";

		pthread_mutex_lock(&lock);
		unsigned size =  GR.size();


		for(int i =0 ; (unsigned)i < size; i++){
			if(GR[i].getName() == args[1]){
				strcpy(result,"notgood");
				break;
			}
		}
		if(strcmp(result,"good1") == 0) {
			GameRoom gr = GameRoom(socket,0,1,args[1]);
			GR.push_back(gr);
		}
		pthread_mutex_unlock(&lock);

		int n = write(socket,&result,sizeof(result));
		cout << "start command -" << result<< endl;
		if(n== -1) {
			cout << "Error write to socket" << endl;
		}

	//	close(socket);
	}
};




#endif /* STARTCOMMAND_H_ */
