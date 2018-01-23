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

#define END_OF_GAME -3
#define DISCONNECTED -4
#define NO_MOVE -1
#define INIT -2
#define FIRST_PLAYER 1
#define SECONDE_PLAYER 2
#define MAX_CONNECTED_CLIENTS 10


static void* handle_one_client(void* socketId);
static void* acceptClients(void*);
vector<pthread_t> vThreads;
pthread_mutex_t print;
pthread_mutex_t add_thread;
#define COMMAND_SIZE 20



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

		pthread_mutex_lock(&add_thread);
		pthread_t t;
	//	vThreads.push_back(t);
		pthread_mutex_unlock(&add_thread);
		////////////////////int rc = pthread creat
		pthread_create(&t,NULL,handle_one_client,(void*)(intptr_t)clientSocket);

		//close(clientSocket);
	}
	while(true);

}

static void* handle_one_client(void *socketId) {

	long clientSocket = (long)socketId;
	char command[COMMAND_SIZE];


	int n = read(clientSocket, &command, sizeof(command));
	if(n==0) {
		cout << "bla" << endl;
	}
	cout << "test: " << command << endl;


	stringstream ss(command);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vCommand(begin, end);


	CommandsManager::getInstance()->executeCommand(vCommand[0],vCommand,clientSocket);
	return (void*)2;
/*

	} else if(vstrings[0] == "join") {
		bool flag = false;
		char str[10];
		int i;
		for (i =0 ; (unsigned) i < vGs.size(); i++) {
			if(vGs[i].counter ==1 && vGs[i].name == vstrings[1]) {
				flag = true;
				vGs[i].sid2 = clientSocket;
				vGs[i].counter =2;
				break;
			}
		}
		if(flag == true) {
			strcpy(str,"good");
			n = write(clientSocket, &str, strlen(str) + 1);
			strcpy(str1,"connect");
			n = write(vGs[i].sid1, &str1, strlen(str1) + 1);
			handleClients(vGs[i].sid1,vGs[i].sid2);
		} else {
			strcpy(str,"notgood");
			n = write(clientSocket, &str, strlen(str) + 1);
		}

	}

	 */
}






// Handle requests from a specific client
void Server::handleClients(int clientSocket1, int clientSocket2) {

	cout << "entered handle 2 clients" << endl;
	int n;
	int buf[2];
	while (true) {

		//read from player 1
		cout << "read from 1 client:" << endl;
		n = read(clientSocket1, &buf, sizeof(buf));
		if (n == -1) {
			cout << "Error reading move from client1" << endl;
			break;
		}
		if (n == 0) {
			cout << "Client1 disconnected" << endl;
			break;
		}

		n = write(clientSocket2, &buf, sizeof(buf));

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
			break;
		}
		n = write(clientSocket1, &buf, sizeof(buf));


	}
}

void Server::stop() {
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "server stop" << endl;
}
