/*
 * RemoteGameLogic.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: oren
 */

#include "../include/RemoteGameLogic.h"
#include <string.h>
#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <unistd.h>
#define COMMAND_SIZE 50

RemoteGameLogic::RemoteGameLogic() {
	ifstream myFILE;
	int port;
	string ip;

	myFILE.open("./ClientConfig.txt");
	if(myFILE.is_open()) {
		myFILE>>port;
		myFILE>>ip;
		myFILE.close();
	} else {
		cout << "Unable to open the file" << endl;
	}

	this->players[0] = new RemotePlayer(ip.c_str(),port);
	this->players[1] = new DummyPlayer();
	this->board = new Board(8);
	this->waiting_to_player = true;
	this->init_start_board();

	connectAndCommand();	// start getting commandes


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

void RemoteGameLogic::connectAndCommand() {
	char command[COMMAND_SIZE];

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	while(true) {
		do{
			cout << "please enter command:"
					<< endl << "1. start <name>" << endl << "2. join <name>" <<endl <<
					"3. list_games" << endl << "4. close" << endl << endl;
			cin.getline(command,COMMAND_SIZE);
			vector<string> vcommand = commandToVector(command);
			unsigned size =vcommand.size();
			if((vcommand[0] == "close" && size == 1) ||
					(vcommand[0] == "start" && size == 2) ||
					(vcommand[0] == "list_games" && size == 1) ||
					(vcommand[0] == "join" && size == 2)) {
				break;
			}
			cout << "not valid command - try again." <<endl << endl;
		} while(true);

		vector<string> vcommand = commandToVector(command);
		if(vcommand[0] == "close") {
			return;
		}
		//accept valid command - sent to server

		//connect to server
		try {
			rp->connectToServer();
		} catch (const char* msg) {
			cout << "failed connect to server reaseon: " << msg<< endl;
			exit(-1);
		}

		rp->writeStringToServer(command);
		rp->readStringFromServer(command);



		if(vcommand[0]=="list_games") {
			if(strcmp(command,"") == 0){
				cout << endl << "There are no exists games." << endl << endl;
			} else {
				print_list_games(command);
			}

		} else if(vcommand[0] == "start") {

			if(strcmp(command,"notgood") == 0) {
				cout << "Game is already exist - please try again." << endl << endl;
			} else {
				play_start_game();
			}
		} else if(vcommand[0] == "join"){

			if(strcmp(command,"notgood") == 0) {
				cout << "Game isn't exist - please try again." << endl << endl;
			} else {

				play_join_game();
			}
		}
		close(rp->getClientSocket());
	}

	/*
	} else if(vstrings[0] == "join") {
		rp->writeStringToServer(str);
		vector<string> answer = rp->readStringFromServer();
		if(answer[0] == "notgood") {
			cout << "game not exist" << endl;
		} else if(answer[0] == "good") {
			play_join_game();

		}
	}
	cout << "finished 1 loop" << endl;
}
	 */
}

void RemoteGameLogic::change_players(){
	this->players[0]->set_name("player_1");
	this->players[0]->set_symbol('X');
	this->players[1]->set_name("player_2");
	this->players[1]->set_symbol('O');
}

void RemoteGameLogic::print_list_games(char* str) {
	vector<string> vcommand = commandToVector(str);
	unsigned size = vcommand.size();

	cout << endl<<  "Game List: " << endl;
	for(int i = 0; (unsigned)i < vcommand.size(); i++){
		cout << i+1 << ". " << vcommand[i]<< endl;
	}
	cout << endl;
}

vector<string> RemoteGameLogic::commandToVector(char* str) {
	stringstream ss(str);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vcommand(begin, end);
	return vcommand;
}

void RemoteGameLogic::play_start_game() {
	char str[COMMAND_SIZE];
	int x,y;

	cout << endl << "Waiting for another player to connect! " << endl;
	change_players(); // change name and symbol of players - player[0] is still my remote player

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);

	rp->readStringFromServer(str);
	rp->readStringFromServer(str);

	cout << "other player connected" << endl;

	int buff[2];
	while(true){
		cout << "eneter x y" << endl;
		cin >> buff[0] >> buff[1];
		rp->writeToServer(buff);
		rp->readFromServer(buff);
		cout << "start player: " << buff[0] << " , " << buff[1]<< endl;

	}


}
void RemoteGameLogic::play_join_game() {

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	cout << "entered play join player" << endl;

	int buff[2];


	while(true){
		rp->readFromServer(buff);

		cout << "start player: " << buff[0] << " , " << buff[1]<< endl;
		cout << "eneter x y" << endl;
		cin >> buff[0] >> buff[1];
		rp->writeToServer(buff);
	}
	/*
	cout <<"Start Game:" << endl;
	print_board();
	cout <<"Player "<< rp->getName() << " has " << player2_points() << " points" << endl;
	 */

}

