/*
 * Player.h
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>
using namespace std;

class Player {
public:
	Player(const string &name, char symbol);
	virtual ~Player();
	char getSymbol() const;
	const string& getName() const;
	int getPoints() const;
	void setPoints(int points);
	/**
	 * add points to player.
	 * @param - x number of points to add/sub.
	 */
	void add_points(int x);
	/**
	 * Different type of players returns different string
	 * @return string - "PLAYER" for Human type, and "AI" for AIPlayer
	 */
	virtual string get_type() const;
	void set_name(const string& name);
	void set_symbol(char symbol);

private:
	char symbol;
	string name;
	int points;

};

#endif /* PLAYER_H_ */
