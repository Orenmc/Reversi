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



RemotePlayer::RemotePlayer(const char *serverIP, int serverPort):Player("player_2",'O'),
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
	int buffer[2];
	int n = read(clientSocket, &buffer, sizeof(buffer));

	if (n == -1) {
		cout << "Error reading move from server" << endl;
		return;
	}
	if (n == 0) {
		cout << "Client1 disconnected" << endl;
		return;
	}

	cout<<"----------------"<<endl;
	if(buffer[0] == 1){
		cout<<"You are the first player to connect - player 'X'"<<endl;
		cout <<"Waiting for other player to join..."<< endl;
	} else if(buffer[0] == 2){
		cout<<"You are the second player to connect - player 'O'"<<endl;
		cout<< "waiting for opponent plays..." <<endl;
	}
	cout<<"----------------"<<endl;
}

void RemotePlayer::readFromServer(int buf[]) {
	int test[2];

	int n = read(clientSocket, &test, sizeof(test));
	if (n == -1) {
		cout << "Error reading move from server" << endl;
		return;
	}
	if (n == 0) {
		cout << "Client1 disconnected" << endl;
		return;
	}

	buf[0]=test[0];
	buf[1]=test[1];
}

void RemotePlayer::writeToServer(int buf[]) {
	int buffer[2];
	int n;
	buffer[0]=buf[0];
	buffer[1]=buf[1];
	cout<< "waiting for opponent plays..." <<endl;
	n = write(clientSocket, &buffer,sizeof(buffer));
	if (n == -1) {
		cout << "Error writing to the server" << endl;
		return;
	}
	if (n == 0) {
		cout << "Client1 disconnected" << endl;
		return;
	}

}
