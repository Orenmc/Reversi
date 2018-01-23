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
#include <pthread.h>
#include <sstream>
#include <iterator>
#include <string.h>
#include <string>
#include "CommandsManager.h"

static void* handle_one_client(void* socketId);
static void* acceptClients(void*);

#define MAX_CONNECTED_CLIENTS 10
#define COMMAND_SIZE 50

using namespace std;


Server::Server():port(0), serverSocket(0), serverThreadId(0){
	ifstream Info;
	Info.open("./ServerConfig.txt");

	if(Info.is_open()){
		Info>>port;
		Info.close();
	} else {
		cout << "Unable to open the file" << endl;
	}

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
	pthread_create(&serverThreadId,NULL,&acceptClients,(void*)(intptr_t)serverSocket);

}
static void* acceptClients(void* socket) {
	long serverSocket = (long) socket;

	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen ;//= sizeof(clientAddress);

	do{
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection

		int clientSocket = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);

		if (clientSocket == -1){
			throw "Error on accept";
		}

		cout << "Client  connected" << endl;

		pthread_t t;
		pthread_create(&t,NULL,handle_one_client,(void*)(intptr_t)clientSocket);

	}
	while(true);

}

static void* handle_one_client(void *socketId) {

	long clientSocket = (long)socketId;
	char command[COMMAND_SIZE];


	int n = read(clientSocket, &command, sizeof(command));
	if(n==0) {
		cout << "Error reading command from client." << endl;
		return (void*)2;
	}


	stringstream ss(command);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vCommand(begin, end);


	CommandsManager::getInstance()->executeCommand(vCommand[0],vCommand,clientSocket);
	return (void*)2;

}

void Server::stop() {
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "server stop" << endl;
}
