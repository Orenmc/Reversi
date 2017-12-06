/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemotePlayer.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;


RemotePlayer::RemotePlayer(const char *serverIP, int serverPort):Player("remote",'X'),
	serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	/*
	 * SHOULD READ FROM FILE - OPEN FILE->READ PORT->AND IP
	 */
	try {
		connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason:" << msg << endl;
				exit(-1);
	}
}

RemotePlayer::~RemotePlayer() {

}

string RemotePlayer::get_type() const {
	return "REMOTE";
}
void RemotePlayer::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}
	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof
			address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char
			*)server->h_addr, server->h_length);
	// htons converts values between host and network byte

	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
}
void RemotePlayer::sendNumber() {
	int buffer[2];

	// Write the exercise arguments to the socket

	int n = read(clientSocket, &buffer, sizeof(buffer));
	if (buffer[1] == -1) {
	cout << "this is first time"<<endl;
	} else {
		cout << "this is the point: " << buffer[0] <<" ," << buffer[1] << endl;
	}
	cout << "Enter two numbers" << endl;
	cin >> buffer[0] >> buffer[1];
	n = write(clientSocket, &buffer,sizeof(buffer));

}

