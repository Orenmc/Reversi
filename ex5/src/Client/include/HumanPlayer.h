/*
 * HumanPlayer.h
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer: public Player {
public:
	HumanPlayer(const string &name, char symbol);
	virtual string get_type() const;

};

#endif /* HUMANPLAYER_H_ */
