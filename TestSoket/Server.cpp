/*
 * Server.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include "Server.h"
#include <fstream>

#define END_OF_GAME -3
#define DISCONNECTED -4
#define NO_MOVE -1
#define INIT -2
#define FIRST_PLAYER 1
#define SECONDE_PLAYER 2

using namespace std;

#define MAX_CONNECTED_CLIENTS 2
Server::Server():port(0), serverSocket(0) {
	ifstream myFILE;
		myFILE.open("ServerConfig.txt");
		myFILE>>port;
	cout << "Server" << endl;
}
void Server::start() {
	// Create a socket point
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local address to the socket
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress,
			sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr
			*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error on binding";
	}

	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;


	cout << "Waiting for client connections..." << endl;
	// Accept a new client connection
	do{
		int clientSocket1 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);

		if (clientSocket1 == -1)
			throw "Error on accept";

		cout << "Client 1 connected" << endl;


		int player1[2] = {FIRST_PLAYER,0};
		int n = write(clientSocket1, &player1, sizeof(player1));
		// Accept a new client connection
		int clientSocket2 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);

		if (clientSocket2 == -1)
			throw "Error on accept";

		cout << "Client 2 connected" << endl;

		int player2[2] = {SECONDE_PLAYER,0};
		n = write(clientSocket2, &player2, sizeof(player2));

		handleClients(clientSocket1,clientSocket2);
	}
	while(true);


}

// Handle requests from a specific client
void Server::handleClients(int clientSocket1, int clientSocket2) {
	int buf[2];
	bool flag = true;
	int n;
	int first_connection[2] = {INIT,INIT};
	int endGame[2]= {END_OF_GAME,END_OF_GAME};
	int disconnected[2] = {DISCONNECTED,DISCONNECTED};
	int counter = 0;
	while (true) {
		// Read move from client and send to another client.

		if (flag == true){
			n = write(clientSocket1, &first_connection, sizeof(first_connection));
			flag = false;
		} else if (buf[0]== NO_MOVE) {

			if(counter == 1){
				n = write(clientSocket1, &endGame, sizeof(endGame));
				n = write(clientSocket2, &endGame, sizeof(endGame));
				break;
			} else {
				counter = 1;
				n = write(clientSocket1, &buf, sizeof(buf));
			}
		} else {
			counter = 0;
			n = write(clientSocket1, &buf, sizeof(buf));
		}
		if (n == -1) {
			cout << "Error write move to client1" << endl;
			break;
		}
		if (n == 0) {
			cout << "Client1 disconnected" << endl;
			break;
		}
		//read from player 1
		n = read(clientSocket1, &buf, sizeof(buf));
		if (n == -1) {
			cout << "Error reading move from client1" << endl;
			break;
		}
		if (n == 0) {
			cout << "Client1 disconnected" << endl;
			n = write(clientSocket2, &disconnected, sizeof(disconnected));
			break;
		}

		if(buf[0]== NO_MOVE ){
			if(counter == 1){
				n = write(clientSocket2, &endGame, sizeof(endGame));
				n = write(clientSocket1, &endGame, sizeof(endGame));
				break;
			} else {
				counter = 1;
				n = write(clientSocket2, &buf, sizeof(buf));
			}
		} else {
			counter = 0;
			n = write(clientSocket2, &buf, sizeof(buf));
		}

		// Write the result back to the client
		if (n == -1) {
			cout << "Error writing move to client2" << endl;
			break;
		}
		if (n == 0) {
			cout << "Client2 disconnected" << endl;
			break;
		}



		n = read(clientSocket2, &buf, sizeof(buf));

		if (n == -1) {
			cout << "Error read move from client2" << endl;
			break;
		}
		if (n == 0) {
			cout << "Client2 disconnected" << endl;
			n = write(clientSocket1, &disconnected, sizeof(disconnected));
			break;
		}

	}
	 // "SERVER - only here close" << endl;
	// Close communication with the client
			close(clientSocket1);
			close(clientSocket2);
}

void Server::stop() {
	close(serverSocket);
}
