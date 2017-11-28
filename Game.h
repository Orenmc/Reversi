/*
 * Game.h
 *
 *  Created on	: Nov 11, 2017
 *      Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef GAME_H_
#define GAME_H_


#include "GameLogic.h"
/**
 * Game is a class how can deal with running games.
 */
class Game {
public:
	Game();
	~Game();
	/**
	 * initialized a game logic (with all the paramters he needs).
	 */
	void init_game_logic();
	/**
	 * run game.
	 */
	void run();
	/*
	 * print score to console.
	 */
	void print_score(GameLogic *gl) const;
	/**
	 * print end of game to console (how wins and points to each player)
	 */
	void end_of_game(GameLogic *gl) const;

private:
	GameLogic *gl;

};

#endif /* GAME_H_ */
