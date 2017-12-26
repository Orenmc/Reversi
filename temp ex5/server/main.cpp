/*
 * main.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: snirhazan
 */

#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

#include <pthread.h>
#include <cstdlib>

using namespace std;
#define THREADS_NUM 5




int main() {
	Server server = Server();

	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}


