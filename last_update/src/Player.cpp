/*
 * Player.cpp
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "../include/Player.h"
#include <iostream>
/**
 * create player with name and symbol.
 */
Player::Player(const string& name, char symbol): symbol(symbol), name(name), points(2) {
}



char Player::getSymbol() const {
	return symbol;
}

const string& Player::getName() const {
	return name;
}

int Player::getPoints() const {
	return points;
}

void Player::setPoints(int points) {
	this->points = points;
}

void Player::add_points(int x) {
	this->points += x;
}

Player::~Player() {
}

string Player::get_type() const {
	return NULL;
}
