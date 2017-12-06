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

#define MAX_CONNECTED_CLIENTS 10
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
		int clientSocket1 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client 1 connected" << endl;

		// Accept a new client connection
		int clientSocket2 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client 2 connected" << endl;
		if (clientSocket2 == -1)
			throw "Error on accept";

		handleClients(clientSocket1,clientSocket2);

		// Close communication with the client
		close(clientSocket1);
		close(clientSocket2);
}

// Handle requests from a specific client
void Server::handleClients(int clientSocket1, int clientSocket2) {
	int arg1, arg2;
	char op;
	bool flag = true;
	int n;
	int result = -1;

	while (true) {
		// Read new exercise arguments
		if ( flag == true){
			n = write(clientSocket1, &result, sizeof(result));
			flag = false;
		} else {

			n = write(clientSocket1, &arg2, sizeof(arg2));
		}

		n = read(clientSocket1, &arg1, sizeof(arg1));
		if (n == -1) {
			cout << "Error reading arg1" << endl;
			return;
		}
		if (n == 0) {
			cout << "Client disconnected" << endl;
			return;
		}
		// Write the result back to the client
		n = write(clientSocket2, &arg1, sizeof(arg1));
		if (n == -1) {
			cout << "Error writing to socket" << endl;
			return;
		}
		n = read(clientSocket2, &arg2, sizeof(arg2));
		if (n == -1) {
			cout << "Error reading arg1" << endl;
			return;
		}
		if (n == 0) {
			cout << "Client disconnected" << endl;
			return;
		}
	}
}

int Server::calc(int arg1, const char op, int arg2) const {
	switch (op) {
	case '+':
		return arg1 + arg2;
	case '-':
		return arg1 - arg2;
	case '*':
		return arg1 * arg2;
	case '/':
		return arg1 / arg2;
	default:
		cout << "Invalid operator" << endl;
		return 0;
	}
}
void Server::stop() {
	close(serverSocket);
}
