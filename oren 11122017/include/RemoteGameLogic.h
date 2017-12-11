/*
 * RemoteGameLogic.h
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#ifndef REMOTEGAMELOGIC_H_
#define REMOTEGAMELOGIC_H_

#include "GameLogic.h"
#define END_OF_GAME -3
#define DISCONNECTED -4
#define NO_MOVE -1
#define INIT -2

class RemoteGameLogic: public GameLogic {
public:
	RemoteGameLogic();
	virtual ~RemoteGameLogic();
	int play_one_turn(Player* p1);
private:
	void change_players();
	bool waiting_to_player;
};

#endif /* REMOTEGAMELOGIC_H_ */
