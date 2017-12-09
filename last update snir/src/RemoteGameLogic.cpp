/*
 * RemoteGameLogic.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemoteGameLogic.h"

RemoteGameLogic::RemoteGameLogic() {
	this->players[0] = new RemotePlayer("127.0.0.1", 8000);
	this->players[1] = new DummyPlayer();
	this->board = new Board(4);
	this->waiting_to_player = true;
	this->init_start_board();
}

RemoteGameLogic::~RemoteGameLogic() {


}
int RemoteGameLogic::play_one_turn(Player* p1) {
	if(p1->get_type()== "DUMMY"){
		return 1;
	}
	int buffer[2] = {0,0};

	vector<Point> start_points, end_points;
	vector<int> flip_number;
	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	try {
		//rp->sendNumber();
		rp->readFromServer(buffer);


	} catch (const char *msg) {
		cout << "Failed to send exercise to server. Reason: " << msg << endl;
	}
	//if =-2 means first player connected swap players
	if(buffer[0] == -2){
		//cout << "read -2 from server - swap" <<endl;
		cout << endl;
		this->change_players();
	} else if(buffer[0] == -1) {
		this->print_board();
		cout<<endl << players[1]->getSymbol() << " not played - no available move"<<endl<<endl;
	} else if(buffer[0] == -3){
		buffer[0] = -1;
		buffer[1] = -1;
		rp->writeToServer(buffer);
		return 1;

	}else{
		find_options(this->board,players[1],start_points,end_points,flip_number);
		Point point = Point(buffer[0]-1,buffer[1]-1);
		change_all_points(this->board,players[1],point,start_points,end_points,flip_number);
		//cout << "RemoteGameLogic - when getting from server"<<endl;
		this->print_board();
		cout<<endl << players[1]->getSymbol() << " played: " << point<<endl<<endl;

	}
	start_points.clear();
	end_points.clear();
	flip_number.clear();

	//	cout << p1->getName() << " - '" << p1->getSymbol() << "' turn" <<endl;
	this->find_options(this->board,p1,start_points,end_points,flip_number);
	//order all points to print
	if (start_points.empty() == true) {
		//return 1;
		buffer[0]=-1;
		buffer[1]=-1;
		cout << "no available moves - other player move" << endl;
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

				//	cout << "RemoteGameLogic - befor writeToServer" << endl;
				break;
			}
			cout << "not good option - try again."<< endl;
		}
	}
	this->print_board();
	rp->writeToServer(buffer);
	return 0;
}
void RemoteGameLogic::change_players(){
	this->players[0]->set_name("player_1");
	this->players[0]->set_symbol('X');
	this->players[1]->set_name("player_2");
	this->players[1]->set_symbol('O');
}
