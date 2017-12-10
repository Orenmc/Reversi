/*
 * Game.cpp
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "../include/Game.h"
#include <iostream>
#include <stdlib.h>

Game::Game() {
	init_game_logic();
}
Game::~Game(){
	delete gl;
}

void Game::init_game_logic() {
	cout<<"**Reversi Game**"<<endl<<endl;
	cout << "Choose an opponent type: " << endl << "1. Human local player" <<endl <<"2. AI player" << endl<< "3. Remote player" << endl;
	int choise = InputTest::get_number_for_menu();
	if(choise < 3) {
		this->gl = new GameLogic(choise);
	} else {
		this->gl = new RemoteGameLogic();
	}
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
			/*
			print_score(gl);
			this->gl->print_board();
			 */
			counter = 0; // if played initialize counter strikes
		} else { // if didn't play - counter =1
			if (counter == 1) {
				cout << "No available moves for both of the player- Game Over!" << endl;
				//end of Game
				this->gl->set_should_stop(true);
				break;
			}
			//if not full try next player
		//	cout << "No available moves - other player move -GAME" << endl;
			//	InputTest::press_any_key();
			counter = 1;
		}

		//no player can play - check if board full - if yes stop.
		if(this->gl->board_full() == true){
			this->gl->set_should_stop(true);
			break;
		}

		// now second player
		if(this->gl->get_player(2)->get_type() == "DUMMY") {
			counter = 1;
		} else {
			if (this->gl->play_one_turn(gl->get_player(2)) == 0) {

				//print_score(gl);
				//this->gl->print_board();

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
				//InputTest::press_any_key();
				counter = 1;
			}
		}
	}
	//end of while
	end_of_game(gl);
	startOrExit();
}

void Game::print_score(GameLogic* gameLogic) const {
	/*
// first player points
	cout<< gameLogic->get_player(1)->getName() << " points: " <<gameLogic->player1_points()<< endl;
// second player points
	cout<< gameLogic->get_player(2)->getName() << " points: " << gameLogic->player2_points() << endl;

	 */
	cout << "X points: " << gameLogic->player1_points()<<endl;;
	cout << "O points: " << gameLogic->player2_points()<<endl;
}

void Game::end_of_game(GameLogic* gl) const {
	//system("clear");
	cout<<"Final Board:"<<endl;
	this->gl->getBoard()->print_matrix();
	int points1 = gl->player1_points();
	int points2 = gl->player2_points();

	cout << "~~~~~~~~~ End Of Game ~~~~~~~~~" << endl;
	if(points1 == points2){
		cout << "Equal - no one wins"<<endl;
	}else if(points1>points2){
		cout <<"###### " << gl->get_player(1)->getSymbol()<< " WINS ######" <<endl;
	} else {
		cout <<"###### " << gl->get_player(2)->getSymbol()<< " WINS ######" <<endl;
	}
	print_score(gl);
}

void Game::startOrExit() {
	cout<<endl;
	char symbol;
	cout<<"Play Again - please press n and than Enter"<<endl;;
	cout<<"Quit - please press q and than Enter"<<endl;;
	cin>>symbol;
	if(symbol != 'n') {
		cout<<"Thank you for playing Reversi!"<<endl;;
	}
	if(symbol == 'n') {
		delete gl;
		init_game_logic();
		run();
	}
}
