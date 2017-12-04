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
	Server(int port);
	void start();
	void stop();

private:
	int port;
	int serverSocket;

	void handleClient(int clientSocket);
	int calc(int arg1, const char op, int arg2) const;
};



#endif /* SERVER_H_ */
