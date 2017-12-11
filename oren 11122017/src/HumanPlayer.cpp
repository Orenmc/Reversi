/*
 * HumanPlayer.cpp
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "../include/HumanPlayer.h"


HumanPlayer::HumanPlayer(const string& name, char symbol) : Player(name,symbol){
}

string HumanPlayer::get_type() const {
	return "PLAYER";
}
