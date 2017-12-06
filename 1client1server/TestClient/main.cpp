/*
 * main.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */

#include "Client.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	Client client("127.0.0.1", 5123);
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason:" << msg << endl;
				exit(-1);
	}

	while (true) {

		try {
			client.sendNumber();
		} catch (const char *msg) {
			cout << "Failed to send exercise to server. Reason: " << msg << endl;
		}
	}
}


