/*
 * AIPlayer.h
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Player.h"

class AIPlayer: public Player {
public:
	AIPlayer(const string &name, char symbol);
	virtual string get_type() const;

};

#endif /* AIPLAYER_H_ */
