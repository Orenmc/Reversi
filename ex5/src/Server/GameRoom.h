/*
 * GameRoom.h
 *
 *  Created on: Jan 1, 2018
 *      Author: oren
 */

#ifndef GAMEROOM_H_
#define GAMEROOM_H_
#include <string.h>
#include <string>
using namespace std;

class GameRoom {
public:
	GameRoom(int sid1, int sid2, int counter, string name);
	virtual ~GameRoom();
	int getCounter() const;
	void setCounter(int counter);
	const string& getName() const;
	void setName(const string& name);
	int getSid1() const;
	void setSid1(int sid1);
	int getSid2() const;
	void setSid2(int sid2);

private:
	int sid1;
	int sid2;
	int counter;
	string name;
};

#endif /* GAMEROOM_H_ */
