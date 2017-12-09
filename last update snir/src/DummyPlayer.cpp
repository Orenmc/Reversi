/*
 * DummyPlayer.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/DummyPlayer.h"

DummyPlayer::DummyPlayer():Player("player_1",'X'){

}

DummyPlayer::~DummyPlayer() {
}

string DummyPlayer::get_type() const {
	return "DUMMY";
}
