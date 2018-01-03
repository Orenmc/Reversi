/*
 * GameRoom.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: oren
 */

#include "GameRoom.h"



GameRoom::GameRoom(int sid1, int sid2, int counter, string name)
: sid1(0), sid2(0),counter(0), name(""){
	this->sid1 = sid1;
	this->sid2 = sid2;
	this->counter = counter;
	this-> name = name;
}

GameRoom::~GameRoom() {
}

int GameRoom::getCounter() const {
	return counter;
}

void GameRoom::setCounter(int counter) {
	this->counter = counter;
}

const string& GameRoom::getName() const {
	return name;
}

void GameRoom::setName(const string& name) {
	this->name = name;
}

int GameRoom::getSid1() const {
	return sid1;
}

void GameRoom::setSid1(int sid1) {
	this->sid1 = sid1;
}

int GameRoom::getSid2() const {
	return sid2;
}

void GameRoom::setSid2(int sid2) {
	this->sid2 = sid2;
}
