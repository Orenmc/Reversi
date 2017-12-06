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
	void sendNumber();
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};
