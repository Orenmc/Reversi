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

struct ThreadArgs {
	int serverSocketArgs;
	ThreadPool* pool;
	//vector<Task*> tasks;
};


Server::Server():port(0), serverSocket(0), serverThreadId(0){
	ifstream Info;
	Info.open("./ServerConfig.txt");

	if(Info.is_open()){
		Info>>port;
		Info.close();
	} else {
		cout << "Unable to open the file" << endl;
	}
	this->pool = new ThreadPool(5);

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

	ThreadArgs *ta;
	ta->serverSocketArgs = serverSocket;
	ta->pool = this->pool;
	//ta->tasks = tasks;

	pthread_create(&serverThreadId,NULL, acceptClients , (void*)ta);

}
static void* acceptClients(void* tArgs) {

	struct ThreadArgs *args = (struct ThreadArgs*) tArgs;
	int serverSocket = args->serverSocketArgs;
	ThreadPool * pool = args->pool;
	//vector<Task*> tasks = args->tasks;

	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen ;//= sizeof(clientAddress);

	do{
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		cout << "maybe here???"<< endl;
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "accept?" << endl;
		if (clientSocket == -1){
			throw "Error on accept";
		}

		cout << "Client  connected" << endl;
		/*
		pthread_t t;
		pthread_create(&t,NULL,handle_one_client,(void*)(intptr_t)clientSocket);
		 */
		Task* t = new Task(handle_one_client,(void *)(intptr_t) clientSocket);
		//tasks.push_back(t);
		pool->addTask(t);
	}
	while(true);

}

static void* handle_one_client(void *socketId) {
	cout << "gets here"<<endl;
	long clientSocket = (long)socketId;
	char command[COMMAND_SIZE];
int i = 8;
	cout << "here" << i <<endl;

	int n = read(clientSocket, &command, sizeof(command));
	if(n==0) {
		cout << "Error reading command from client." << endl;
		return (void*)2;
	}

	cout << "here????"<<endl;

	stringstream ss(command);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;

	vector<string> vCommand(begin, end);
	cout<<"something: "<< vCommand[0] << endl;

	CommandsManager::getInstance()->executeCommand(vCommand[0],vCommand,clientSocket);
	return (void*)2;

}

void Server::stop() {
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "server stop" << endl;
}
