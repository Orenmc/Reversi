/*
 * DummyPlayer.h
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#ifndef DUMMYPLAYER_H_
#define DUMMYPLAYER_H_

#include "Player.h"

class DummyPlayer: public Player {
public:
	DummyPlayer();
	virtual ~DummyPlayer();
	virtual string get_type() const;
};

#endif /* DUMMYPLAYER_H_ */
