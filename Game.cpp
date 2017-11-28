/*
 * Game.cpp
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "Game.h"
#include <iostream>

Game::Game() {
	init_game_logic();
}
Game::~Game(){
	delete gl;
}

void Game::init_game_logic() {
	cout << "choose game: " << endl << "1. PvP" <<endl <<"2. player VS AI" << endl;

	this->gl = new GameLogic(InputTest::get_number_for_menu());
}

void Game::run() {
	//before play - print board
	this->gl->print_board();
	int counter = 0; // count numbers if "don't play rows" - if =2 stop game
	while(this->gl->is_should_stop() == false) { //as long some player can play
		//no player can play - check if board full - if yes stop.
		if(this->gl->board_full() == true){
			this->gl->set_should_stop(true);
			break;
		}
		//first player try to play
		if (this->gl->play_one_turn(gl->get_player(1)) == 0) {
			print_score(gl);
			this->gl->print_board();
			counter = 0; // if played initialize counter strikes
		} else { // if didn't play - counter =1
			if (counter == 1) {
				cout << "no more moves" << endl;
				this->gl->set_should_stop(true);
				break;
			}
			//if not full try next player
			cout << "no available moves - other player move" << endl;
			InputTest::press_any_key();
			counter = 1;
		}
		//no player can play - check if board full - if yes stop.
		if(this->gl->board_full() == true){
			this->gl->set_should_stop(true);
			break;
		}
		// now second player
		if (this->gl->play_one_turn(gl->get_player(2)) == 0) {
			print_score(gl);
			this->gl->print_board();
			counter = 0;
		} else { // if didnt play - end game if counter =1, or next player plays
			if (counter == 1) {
				cout << "no more moves" << endl;
				this->gl->set_should_stop(true);
				break;
			}
			//no player can play
			if(this->gl->board_full() == true){
				this->gl->set_should_stop(true);
				break;
			}
			cout << "no available moves - other player move" << endl;
			InputTest::press_any_key();
			counter = 1;
			}
	}//end of while

	end_of_game(gl);
}

void Game::print_score(GameLogic* gameLogic) const {
// first player points
	cout<< gameLogic->get_player(1)->getName() << " points: " <<gameLogic->player1_points()<< endl;
// second player points
	cout<< gameLogic->get_player(2)->getName() << " points: " << gameLogic->player2_points() << endl;
}

void Game::end_of_game(GameLogic* gl) const {
	int points1 = gl->player1_points();
	int points2 = gl->player2_points();

	cout << "~~~~~~~~~ End Of Game ~~~~~~~~~" << endl;
	if(points1==points2){
		cout << "Equal no one wins"<<endl;
	}else if(points1>points2){
			cout <<"###### " << gl->get_player(1)->getName()<< " WINS ######" <<endl;
		} else {
			cout <<"###### " << gl->get_player(2)->getName()<< " WINS ######" <<endl;
		}
	print_score(gl);
}
