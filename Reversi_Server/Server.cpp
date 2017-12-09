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

using namespace std;

#define MAX_CONNECTED_CLIENTS 2
Server::Server(int port): port(port), serverSocket(0) {
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
		int player1[2] = {1,0};
		int n = write(clientSocket1, &player1, sizeof(player1));

		// Accept a new client connection
		int clientSocket2 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);

		if (clientSocket2 == -1)
			throw "Error on accept";

		cout << "Client 2 connected" << endl;
		int player2[2] = {2,0};
		n = write(clientSocket2, &player2, sizeof(player2));


		handleClients(clientSocket1,clientSocket2);

		// Close communication with the client
		close(clientSocket1);
		close(clientSocket2);
	}
	while(true);


}

// Handle requests from a specific client
void Server::handleClients(int clientSocket1, int clientSocket2) {
	int buf[2];
	bool flag = true;
	int n;
	int first_connection[2] = {-2,-2};
	int endGame[2]= {-3,-3};
	int counter = 0;

	while (true) {
		// Read move from client and send to another client.

		if (flag == true){
			n = write(clientSocket1, &first_connection, sizeof(first_connection));
			flag = false;
		} else if (buf[0]== -1) {
			if(counter == 1){
				n = write(clientSocket1, &endGame, sizeof(endGame));

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
			return;
		}
		if (n == 0) {
			cout << "Client1 disconnected" << endl;
			return;
		}

		n = read(clientSocket1, &buf, sizeof(buf));
		if (n == -1) {
			cout << "Error reading move from client1" << endl;
			return;
		}
		if (n == 0) {
			cout << "Client1 disconnected" << endl;
			return;
		}

		if(buf[0]== -1){
			if(counter == 1){
				n = write(clientSocket2, &endGame, sizeof(endGame));

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
			return;
		}
		if (n == 0) {
			cout << "Client2 disconnected" << endl;
			return;
		}

		n = read(clientSocket2, &buf, sizeof(buf));
		if (n == -1) {
			cout << "Error read move from client2" << endl;
			return;
		}
		if (n == 0) {
			cout << "Client2 disconnected" << endl;
			return;
		}

	}
}

void Server::stop() {
	close(serverSocket);
}
