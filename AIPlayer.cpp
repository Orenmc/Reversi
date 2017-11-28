/*
 * AIPlayer.cpp
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "AIPlayer.h"


AIPlayer::AIPlayer(const string& name, char symbol):Player(name,symbol){
}

string AIPlayer::get_type() const {
	return "AI";
}
