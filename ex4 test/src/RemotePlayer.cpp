/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemotePlayer.h"

RemotePlayer::RemotePlayer():Player("remote",'X') {

}

RemotePlayer::~RemotePlayer() {

}

string RemotePlayer::get_type() const {
	return "REMOTE";
}
