/*
 * Server.h
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */

#ifndef SERVER_H_
#define SERVER_H_

class Server{
public:
	Server();
	void start();
	void stop();
	static void*  handle(void* args);

private:
	int port;
	int serverSocket;
	static void * handleClients(void * args);
	//void handleClients(int clientSocket1,int clientSocket2);
};



#endif /* SERVER_H_ */
