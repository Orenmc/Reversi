/*
 * Client.h
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */

class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	int sendExercise(int arg1, char op, int arg2);
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};
