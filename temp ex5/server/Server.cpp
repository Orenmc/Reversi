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
////////////////////////////
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "CommandsManager.h"
#include <algorithm>
#include <sstream>
#include <istream>
#include <iterator>
#define THREADS_NUM 5

struct Args {
	int sid1;
};
struct GameStruct {
	int sid1;
	int sid2;
	string name;
	int counter;
};
////////////////////////////////////
#define END_OF_GAME -3
#define DISCONNECTED -4
#define NO_MOVE -1
#define INIT -2
#define FIRST_PLAYER 1
#define SECONDE_PLAYER 2
#define MAX_CONNECTED_CLIENTS 2

GameStruct gs[6];
pthread_t global_thread[6];
using namespace std;

Server::Server():port(0), serverSocket(0) {
	ifstream Info;
	Info.open("./ServerConfig.txt");

	if(Info.is_open()){
		Info>>port;
		Info.close();
	} else {
		cout << "Unable to open the file" << endl;
	}
	//initalized gs.counter = 0
	for(int i = 0; i<6;i++){
		gs[i].counter=0;
	}
	cout << "Server" << endl;
}
void Server::start() {

	Args args[3];
	pthread_t t[10];

	int i = 0;


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
	//########################################################################3//
	// Accept a new client connection
	do{
	int clientSocket1 = accept(serverSocket, (struct
			sockaddr *)&clientAddress, &clientAddressLen);

	if (clientSocket1 == -1)
		throw "Error on accept";

	cout << "Client 1 connected" << endl;
	int player1[2] = {FIRST_PLAYER,0};
	int n = write(clientSocket1, &player1, sizeof(player1));
	if (n == -1) {
		cout << "Error writing to client1" << endl;
	}

	args[i].sid1 = clientSocket1;
/*
	int clientSocket2 = accept(serverSocket, (struct
			sockaddr *)&clientAddress, &clientAddressLen);

	if (clientSocket1 == -1)
		throw "Error on accept";
	int player2[2] = {SECONDE_PLAYER,0};
	n = write(clientSocket2, &player2, sizeof(player2));
	if (n == -1) {
		cout << "Error writing to client2" << endl;
	}

	cout << "Client 2 connected" << endl;
	args[i].sid2 = clientSocket2;
*/

	int rc = pthread_create(&t[i],NULL,handle,&args[i]);
	cout << "Server " << i << endl;
	i++;
	/*
		int rc = pthread_create(&threads[i],NULL,printHello,(void *)i);
		if(rc) {
			cout << "bla bla" << endl;
			exit(-1);
		}
	 */
	/*
		//Accept a new client connection
		int clientSocket2 = accept(serverSocket, (struct
				sockaddr *)&clientAddress, &clientAddressLen);

		if (clientSocket2 == -1)
			throw "Error on accept";

		cout << "Client 2 connected" << endl;

		int player2[2] = {SECONDE_PLAYER,0};
		n = write(clientSocket2, &player2, sizeof(player2));
		if (n == -1) {
			cout << "Error writing to client2" << endl;
		}
	 */
	//	handleClients(clientSocket1,clientSocket2);
	//close(clientSocket1);
	//close(clientSocket2);


	} while(true);



}

void* Server::handle(void * args) {

	struct Args * args1 = (struct Args *) args;
//	CommandsManager cm = CommandsManager();
	char str1[100];


	int n = read(args1->sid1, &str1, sizeof(str1));


	if (n == -1) {
		cout << "Error read move from client1" << endl;
	}
	if (n == 0) {
		cout << "Client2 disconnected" << endl;
	}
/*
	long tid = (long)(args1->id);
	cout << "Hello world. It's me, thread "<< tid << endl;
	cout << "string is: " << str1 << "size of" << sizeof(str1) << "strlen : "
			<< strlen(str1) << endl;
*/
	stringstream ss(str1);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vstrings(begin, end);
	//copy(vstrings.begin(), vstrings.end(), ostream_iterator<string>(cout, "\n"));



	//cout << str1 << endl;
	int i;
	if(vstrings[0] == "start"){
		for(i =0; i< 6 ; i++){
			if(gs[i].counter == 0){
				gs[i].counter=1;
				gs[i].name=vstrings[1];
				gs[i].sid1 = args1->sid1;
				break;
			}
		}
		cout << "start to room - " <<i << endl;

	} else if(vstrings[0] == "join") {
		for(i =0; i< 6 ; i++){
			if(gs[i].name == vstrings[1]){
				gs[i].counter=2;
				gs[i].sid2 = args1->sid1;
				break;
			}
		}
		cout << "join to thread : "<< i << "name: " << gs[i].name<< endl;
		pthread_create(&global_thread[i],NULL,handleClients,&gs[i]);


///////////////////////////////////////////////////////////
	} else if(vstrings[0] == "list_games") {
		for(int i = 0; i < 6; i++){
			if(gs[i].counter ==1) {
				cout << "game name is: " << gs[i].name << " in room: " << i << endl;
			}
		}
	}

}

// Handle requests from a specific client
void* Server::handleClients(void * args) {

	struct GameStruct * gs1 = (struct GameStruct *) args;
	int clientSocket1 = gs1->sid1;
	int clientSocket2 = gs1->sid2;
	int n;
	/*
	int player1[2] = {FIRST_PLAYER,0};
	int n = write(clientSocket1, &player1, sizeof(player1));
	if (n == -1) {
		cout << "Error writing to client1" << endl;
	}

	int player2[2] = {SECONDE_PLAYER,0};
	n = write(clientSocket2, &player2, sizeof(player2));
	if (n == -1) {
		cout << "Error writing to client2" << endl;
	}
	 */

	int buf[2];
	bool flag = true;

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
}

void Server::stop() {
	close(serverSocket);
}
/*
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
}
*/
