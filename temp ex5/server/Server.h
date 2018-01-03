/*
 * Server.h
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <vector>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>


using namespace std;

class Server{
public:
	Server();
	void start();
	void stop();

	static void print_game_list(long clientSocket);


private:
	int port;
	int serverSocket;
	pthread_t serverThreadId;


	static void handleClients(int clientSocket1,int clientSocket2);
};



#endif /* SERVER_H_ */
