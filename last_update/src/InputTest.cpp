/*
 * InputTest.cpp
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "../include/InputTest.h"
#include <iostream>
#include <limits>
using namespace std;


int InputTest::get_number_from_user() {
    int num;
    while (true) {
        cin >> num;

        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return num;
        }

        // user didn't input a number
        cout << "Please enter numbers only." << endl;
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    }
}
void InputTest::press_any_key() {
    char c;
    cout<< "Press Any Key To Continue...";
        cin.get(c);
        if(c == '\n'){
        	return;
        }

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return;

}

int InputTest::get_size_from_user() {
	int size = 0;
	bool flag = false;

	do{
		if ( flag == true) {
			cout << "NOT GOOD - choose a good size" <<endl;
		}
		cout<< "choose a board size (2<size<14 and even): ";

		size = get_number_from_user();
		flag = true;
	}
	while (size <4 || size >12 || size%2 !=0);

	return size;
}

int InputTest::get_index_from_user(int max_index) {
	int index = 0;
		bool flag = false;

		do{
			if ( flag == true) {
				cout << "NOT GOOD - out of boundary" <<endl;
			}
			cout<< "choose index (1<= index <=" << max_index << "): ";

			index = get_number_from_user();
			flag = true;
		}
		while (index <1 || index > max_index + 1);

		return index;
}

int InputTest::get_number_for_menu() {
	int index = 0;
		bool flag = false;


		do{
			if ( flag == true) {
				cout << "please choose a valide option!" <<endl;
			}

			index = get_number_from_user();
			flag = true;
		}
		while (index < 1 || index > 2);

		return index;
}
