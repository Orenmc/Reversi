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
int RemoteGameLogic::play_one_turn(Player* p1 , int buf[]) {



	vector<Point> start_points, end_points;
	vector<int> flip_number;

	if(buf[0] == -2) {// -2 is no play - no need to change board


	} else if (buf[0] == -1) {

	}else {
		find_options(this->board,players[1],start_points,end_points,flip_number);
		Point point = Point(buf[0]-1,buf[1]-1);
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
		buf[0]=-1;
		buf[1]=-1;
		cout << "no available moves other player move" << endl;
		InputTest::press_any_key();

		cout<< "waiting for opponent plays..." <<endl<<endl;
		return 1;
	} else {
		//order all points in set (without duplicates)
		set<Point> s;
		std::vector<Point>::iterator it1;
		for (it1=start_points.begin(); it1!=start_points.end(); ++it1) {
			s.insert(*it1);
		}
		while(true){
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
				buf[0]= row;
				buf[1] = col;
				change_all_points(this->board,p1,Point(row-1,col-1),start_points,end_points,flip_number);
				cout << endl << p1->getSymbol() << " Played Point: " << Point(row-1,col-1) <<endl<<endl;
				this->print_board();
				break;
			}
			cout << "not good option - try again."<< endl;
		}
	}
	cout<< "waiting for opponent plays..." <<endl;

	return 0;
}

void RemoteGameLogic::connectAndCommand() {
	char command[COMMAND_SIZE];
	char answer[COMMAND_SIZE];

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	while(true) {
		do{
			strcpy(command,"--");
			cout << "please enter command:"
					<< endl << "1. start <name>" << endl << "2. join <name>" <<endl <<
					"3. list_games" << endl << "4. close" << endl << endl;
			cin.getline(command,COMMAND_SIZE);

			vector<string> vcommand = commandToVector(command);
			unsigned size =vcommand.size();
			if(size == 0) {
				cout << "not valid command - try again." <<endl << endl;
				continue;
			}
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

		rp->readStringFromServer(answer);


		if(vcommand[0]=="list_games") {
			if(strcmp(answer,"") == 0){
				cout << endl << "There are no exists games." << endl << endl;
			} else {
				print_list_games(answer);
			}

		} else if(vcommand[0] == "start") {

			if(strcmp(answer,"notgood") == 0) {
				cout << "Game is already exist - please try again." << endl << endl;
			} else {
				play_start_game();
			}
		} else if(vcommand[0] == "join"){

			if(strcmp(answer,"notgood") == 0) {
				cout << "Game isn't exist - please try again." << endl << endl;
			} else {
				play_join_game();
			}
		}
		close(rp->getClientSocket());
	}

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
	for(int i = 0; (unsigned)i < size; i++){
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

	cout << endl << "Waiting for another player to connect! " << endl;

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);

	rp->readStringFromServer(str);

	cout << "Other player connected" << endl;
	int counter = 0;
	int buff[2] = {-2,-2};
	print_board();
	cout << "waiting for opponent to play..." << endl;
	while(!this->board_full()){

		rp->writeToServer(buff);

		rp->readFromServer(buff);
		if(buff[0]==-1) { // read -1 only when other player not played
			if(counter == 1){ // should stop
				cout<< "End Game" << endl;
				break;
			} else {
				counter = 1;
			}
		} else {
			counter = 0;
		}
		play_one_turn(players[0],buff);
		if(buff[0]==-1) { // read -1 only when other player not played
			if(counter == 1){ // should stop
				cout<< "End Game " << endl;
				rp->writeToServer(buff);
				break;
			} else {
				counter = 1;
			}
		} else {
			counter = 0;
		}

	}
	end_of_game();

}
void RemoteGameLogic::play_join_game() {

	RemotePlayer* rp = dynamic_cast<RemotePlayer*>(players[0]);
	change_players(); // change name and symbol of players - player[0] is still my remote player

	int buff[2];

	int counter = 0;
	while(!board_full()){
		rp->readFromServer(buff);
		if(buff[0]==-1) { // read -1 only when other player not played
			if(counter == 1){ // should stop
				cout<< "End Game" << endl;
				break;
			} else {
				counter = 1;
			}
		} else {
			counter = 0;
		}
		play_one_turn(players[0],buff);
		if(buff[0] == -1) {
			if(counter == 1 ) { // should stop
				cout<< "End Game" << endl;
				rp->writeToServer(buff);
				break;
			} else {
				counter = 1;
			}

		} else {
			counter = 0;
		}
		rp->writeToServer(buff);

	}
	end_of_game();
}

void RemoteGameLogic::end_of_game() {

	system("clear");
	cout<<"Final Board:"<<endl;
	this->print_board();
	int points1 = player1_points();
	int points2 = player2_points();

	cout << "~~~~~~~~~ End Of Game ~~~~~~~~~" << endl;
	if(points1 == points2){
		cout << "Equal - no one wins"<<endl;
	}else if(points1>points2){
		cout <<"###### " << "X"<< " WINS ######" <<endl;
	} else {
		cout <<"###### " << "O"<< " WINS ######" <<endl;
	}
	cout<< "X points: " << points1 << endl;
	cout<< "O points: " << points2 << endl;

	cout<<"Thank you for playing Reversi!"<<endl << endl;

	delete this->board;
	this->board = new Board(8);
	this->init_start_board();
}

