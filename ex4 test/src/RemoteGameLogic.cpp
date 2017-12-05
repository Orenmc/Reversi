/*
 * RemoteGameLogic.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemoteGameLogic.h"

RemoteGameLogic::RemoteGameLogic():GameLogic(1) {
	this->players[0] = new RemotePlayer();
	this->players[1] = new DummyPlayer();
}

RemoteGameLogic::~RemoteGameLogic() {

}


int RemoteGameLogic::play_one_turn(Player* p1) {
	/**
	 * CHECK LATER IF RETURN 1 OR 0
	 */

	if(p1->get_type()== "DUMMY"){
		return 0;
	}


	vector<Point> start_points, end_points;
	vector<int> flip_number;

	cout << p1->getName() << " - '" << p1->getSymbol() << "' turn" <<endl;
	this->find_options(this->board,p1,start_points,end_points,flip_number);
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
			change_all_points(this->board,p1,Point(row-1,col-1),start_points,end_points,flip_number);
			cout << p1->getName() << " Played Point: " << Point(row-1,col-1) <<endl;
			break;
		}
		cout << "not good option - try again."<< endl;
	 }


return 0;
}
