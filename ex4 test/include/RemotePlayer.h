/*
 * RemotePlayer.h
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include "Player.h"

class RemotePlayer: public Player {
public:
	RemotePlayer();
	virtual ~RemotePlayer();
	virtual string get_type() const;
};

#endif /* REMOTEPLAYER_H_ */
