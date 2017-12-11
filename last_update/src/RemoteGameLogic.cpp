/*
 * RemoteGameLogic.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemoteGameLogic.h"

RemoteGameLogic::RemoteGameLogic() {
	ifstream myFILE;
	int port;
	string ip;

	myFILE.open("./ClientConfig.txt");
	if(myFILE.is_open()) {
		cout << "opened" << endl;
		myFILE>>port;
		myFILE>>ip;
	} else {
		cout << "not opened" << endl;
	}

	this->players[0] = new RemotePlayer(ip.c_str(),port);
	this->players[1] = new DummyPlayer();
	this->board = new Board(4);
	this->waiting_to_player = true;
	this->init_start_board();
}

RemoteGameLogic::~RemoteGameLogic() {


}
int RemoteGameLogic::play_one_turn(Player* p1) {
	bool end_game_flag =false;
	int buffer[2] = {0,0};

	vector<Point> start_points, end_points;
	vector<int> flip_number;
	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	try {
		rp->readFromServer(buffer);

	} catch (const char *msg) {
		cout << "Failed to send exercise to server. Reason: " << msg << endl;
	}


	//if =-2 means first player connected swap players
	if(buffer[0] == INIT){
		cout << endl;
		// set player X, O in the right order
		this->change_players();
	} else if(buffer[0] == NO_MOVE) {
		end_game_flag = true;
		cout<<endl << players[1]->getSymbol() << " not played - no available move"<<endl<<endl;
	} else if(buffer[0] == END_OF_GAME){
		//end game - no play
		cout << "No available moves for both of the player- Game Over!" << endl;
		return 1;

	} else if(buffer[0] == DISCONNECTED) {

		cout << "other play Disconnected" << endl<<endl;
		return 1;

	}else {
		find_options(this->board,players[1],start_points,end_points,flip_number);
		Point point = Point(buffer[0]-1,buffer[1]-1);
		change_all_points(this->board,players[1],point,start_points,end_points,flip_number);
		this->print_board();
		cout<<endl << players[1]->getSymbol() << " played: " << point<<endl<<endl;
	}

	start_points.clear();
	end_points.clear();
	flip_number.clear();

	this->find_options(this->board,p1,start_points,end_points,flip_number);
	//order all points to print
	if (start_points.empty() == true) {
		buffer[0]=-1;
		buffer[1]=-1;
		if(end_game_flag == true) {
			rp->writeToServer(buffer);
			return 1;
		}
		cout << "no available moves other player move" << endl;
		cout<< "waiting for opponent plays..." <<endl<<endl;

		InputTest::press_any_key();

	} else {
		//order all points in set (without duplicates)
		set<Point> s;
		std::vector<Point>::iterator it1;
		for (it1=start_points.begin(); it1!=start_points.end(); ++it1) {
			s.insert(*it1);
		}
		while(true){
			if(p1->getSymbol() == 'X' && waiting_to_player == true){
				cout<<"Another player connected!"<<endl;
				waiting_to_player = false;
			}
			this->print_board();
			cout << p1->getSymbol() << " options are:";
			for (std::set<Point>::iterator it=s.begin(); it!=s.end(); ++it) {
				cout << " " << *it;
			}
			cout << endl;
			cout << "choose row index, ";
			int row = InputTest::get_index_from_user(this->board->get_size());
			cout << "choose column index, ";
			int col = InputTest::get_index_from_user(this->board->get_size());
			if (is_point_in_set(Point(row-1,col-1),s) == true) {
				buffer[0]= row;
				buffer[1] = col;
				change_all_points(this->board,p1,Point(row-1,col-1),start_points,end_points,flip_number);
				cout << endl << p1->getSymbol() << " Played Point: " << Point(row-1,col-1) <<endl<<endl;
				this->print_board();
				break;
			}
			cout << "not good option - try again."<< endl;
		}
	}
	cout<< "waiting for opponent plays..." <<endl;
	rp->writeToServer(buffer);
	return 0;
}
void RemoteGameLogic::change_players(){
	this->players[0]->set_name("player_1");
	this->players[0]->set_symbol('X');
	this->players[1]->set_name("player_2");
	this->players[1]->set_symbol('O');
}
