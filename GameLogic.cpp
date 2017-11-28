/*
 * GameLogic.cpp
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic(int chooise): should_stop(false) {
	this->board = new Board(InputTest::get_size_from_user());
	this->players[0] = new HumanPlayer("player_1",'X');
	switch(chooise){
	case 1: {
		this->players[1] = new HumanPlayer("player_2",'O');
		break;
	}
	case 2: {
		this->players[1] = new AIPlayer("computer",'O');
		break;
	}
	}

}


GameLogic::~GameLogic() {
	delete board;
	delete players[0];
	delete players[1];
}

bool GameLogic::is_should_stop() const {
	return should_stop;
}

void GameLogic::set_should_stop(bool shouldStop) {
	should_stop = shouldStop;
}

void GameLogic::print_board() const {
	this->board->print_matrix();
}


Player* GameLogic::get_player(int i) const {
	return players[i-1];
}

void GameLogic::set_on_board(int row, int col, Player* player) {
	this->board->set_matrix(row, col ,player->getSymbol());
}

int GameLogic::play_one_turn(Player* p1) {
	vector<Point> start_points, end_points;
	vector<int> flip_number;

		cout << p1->getName() << " - '" << p1->getSymbol() << "' turn" <<endl;
	this->find_options(p1,start_points,end_points,flip_number);
	//order all points to print
	if (start_points.empty() == true) {
		return 1;
	}
	//order all points in set (without duplicates)
	set<Point> s;
	std::vector<Point>::iterator it1;
	 for (it1=start_points.begin(); it1!=start_points.end(); ++it1) {
		 s.insert(*it1);
	 }

	 //print options -- only for human player.
	 if (p1->get_type() == "PLAYER") {
		 while(true){
		 		cout << p1->getName() << " options are:";
		 		for (std::set<Point>::iterator it=s.begin(); it!=s.end(); ++it) {
		 			cout << " " << *it;
		 		}
		 		cout << endl;
		 		cout << "choose row index, ";
		 		int row = InputTest::get_index_from_user(this->board->get_size());
		 		cout << "choose column index, ";
		 		int col = InputTest::get_index_from_user(this->board->get_size());
		 		if (is_point_in_set(Point(row-1,col-1),s) == true) {
		 			change_all_points(p1,Point(row-1,col-1),start_points,end_points,flip_number);
		 			break;
		 		}
		 		cout << "not good option - try again."<< endl;
		 	 } // if AI plays
	 } else if(p1->get_type() == "AI") {
		 Point best_point = Point(-1,-1);
		 int temp =0,max= 0;

         // set of points that AI can play
		 for (std::set<Point>::iterator it=s.begin(); it!=s.end(); ++it) {



/*
 *
 *
 *
 */
        //     temp = check_point_for_AI(Point *it,Palyer p1, Player p2);

			 temp = count_flops_for_spesific_point(*it,start_points,flip_number);
			 if (temp > max){
				 best_point = *it;
				 max = temp;
			 }
		 }
			change_all_points(p1,best_point,start_points,end_points,flip_number);

	 }


	return 0;

}

void GameLogic::find_options(Player* player, vector<Point>& start, vector<Point>& end,
		vector<int>& flips) const {


	int size = this->board->get_size();

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++ ) {

			Point p = Point(-1,-1);
			if (this->board->get_cell(row,col) == ' ') {
				//check 8 directions for each dir -> save start point, end point and flip count
				int flip_ctr = 0;
				p = this->check_right(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_left(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_up(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_down(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_up_right(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_down_right(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_up_left(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}
				p = this->check_down_left(row,col,player,flip_ctr);
				if (p.valid_point() == true) {
					start.push_back(Point(row,col));
					end.push_back(p);
					flips.push_back(flip_ctr);
				}

			}
		}
	}
}

void GameLogic::change_board_point_to_point(Point p1, Point p2, Player* player) {
	this->set_on_board(p1.getX(),p1.getY(),player);
	int x_s = p1.getX();
	int y_s = p1.getY();
	int x_e = p2.getX();
	int y_e = p2.getY();

	if(x_s == x_e) {
		if(y_s < y_e){
			for(int i = y_s + 1; i < y_e; i++){
				set_on_board(x_s,i,player);
			}
		} else {
			for(int i = y_s -1; i > y_e; i--){
				set_on_board(x_s,i,player);
			}
		}
	} else if(y_s == y_e) {
		if(x_s < x_e){
			for(int i = x_s + 1; i < x_e; i++){
				set_on_board(i,y_s,player);
			}
		} else {
			for(int i = x_s -1; i > x_e; i--){
				set_on_board(i,y_s,player);
			}
		}
	} else if(x_s > x_e) {
		if(y_s < y_e){
			for(int i = x_s - 1, j = y_s + 1 ; i > x_e; i--,j++){
				set_on_board(i,j,player);
			}
		} else {
			for(int i = x_s - 1, j = y_s - 1 ; i > x_e; i--,j--){
				set_on_board(i,j,player);
			}
		}
	} else {
		if(y_s < y_e){
			for(int i = x_s + 1, j = y_s +1 ; i < x_e; i++,j++){
				set_on_board(i,j,player);
			}
		} else {
			for(int i = x_s + 1, j = y_s - 1 ; i < x_e; i++,j--){
				set_on_board(i,j,player);
			}
		}

	}

}

void GameLogic::change_all_points(Player* p, Point p_choose,
		vector<Point> start_points, vector<Point> end_points,
		vector<int> flip_ctr) {
	cout << p->getName() << " played: " << p_choose << endl;
	p->add_points(1); // add 1 points to player
		 for (unsigned int i = 0; i < start_points.size(); i++) {
			 if(start_points[i] == p_choose) {
				 change_board_point_to_point(start_points[i],end_points[i],p);
				 p->add_points(flip_ctr[i]); // ass points to player
				 if(p->getSymbol() == 'O'){ //reduce points from second player
					 this->get_player(1)->add_points(-(flip_ctr[i]));

				 } else {
					 this->get_player(2)->add_points(-(flip_ctr[i]));
				 }
			 }
		 }

}

const int GameLogic::count_flops_for_spesific_point(Point p, vector<Point> start,
		vector<int> flip_number) const {

	int counter = 0;
	for(unsigned i = 0; i< start.size(); i++){
		if(start[i] == p){
			counter += flip_number[i];
		}
	}
	return counter;
}

bool GameLogic::board_full() {
	int size = this->board->get_size();
	if(this->players[0]->getPoints() + this->players[1]->getPoints() == size*size) {
		return true;
	}
	return false;
}

Point GameLogic::check_right(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row;
	int j = col + 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	for(; j < this->board->get_size() - 1; j++) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_left(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row;
	int j = col - 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	for(; j > 0; j--) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_up(int row, int col, Player* player, int& flip_ctr) const {
	int i = row - 1;
	int j = col;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	for(; i > 0; i--) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_down(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row + 1;
	int j = col;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	for(; i < this->board->get_size() - 1; i++) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_up_right(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row - 1;
	int j = col + 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	int size = this->board->get_size();
	for(; j < size - 1 && i > 0; j++, i--) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_down_right(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row + 1;
	int j = col + 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	int size =this->board->get_size();
	for(; j < size - 1 && i < size -1; j++, i++) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_up_left(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row - 1;
	int j = col - 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}

	for(; j > 0 && i > 0; j--,i--) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

Point GameLogic::check_down_left(int row, int col, Player* player,
		int& flip_ctr) const {
	int i = row + 1;
	int j = col - 1;
	flip_ctr = 0;
	char flip_symbol;
	char player_symbol = player->getSymbol();
	if (player_symbol == 'X') {
		flip_symbol = 'O';
	} else {
		flip_symbol = 'X';
	}
	int size = this->board->get_size();
	for(; j > 0 && i < size - 1; j--,i++) {
		if (this->board->get_cell(i,j) == flip_symbol) {
			flip_ctr++;
		} else {
			break;
		}
	}
	if (flip_ctr > 0 && this->board->get_cell(i,j) == player_symbol) {
		return Point(i,j);
	}
	flip_ctr = 0;
	return Point(-1,-1);
}

bool GameLogic::is_point_in_set(Point p, set<Point> s) {
	for (std::set<Point>::iterator it=s.begin(); it!=s.end(); ++it) {
				if(p == *it) {
					return true;
				}
			}
	return false;
}


int GameLogic::check_point_for_AI(Point p, Player p1, Player p2) {

	vector<Point> start_points, end_points;
	vector<int> flip_number;


	Board b_copy = this->board->coppy_board();

	b_copy.set_matrix(p.getX(),p.getY(),'O');

	this->find_options(this->get_player(1),start_points,end_points,flip_number);
		//order all points to print
		if (start_points.empty() == true) {
			return (this->get_player(1)->getPoints() - this->get_player(2)->getPoints());
		}




}

