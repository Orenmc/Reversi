/*
 * Board.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Oren Cohen
 *      user: cohenorx
 *      id: 305164295
 */

#include "../include/Board.h"
#include <iostream>

using namespace std;

Board::Board(int size): size(size) {
	matrix = new char* [size];
	this->init_matrix();
}




void Board::set_matrix(int row, int col, char symbol) {
	if (symbol != 'X' && symbol != 'O' && symbol != ' ') {
		cout << "Board.cpp - unrecognized symbol" << endl;
		return;
	}
		this->matrix[row][col] = symbol;

}

void Board::print_matrix() {
	//print first row
	cout << " |";
	for (int i = 0; i < size; i++) {
		cout << " " << i + 1 << " |";
	}

	cout << endl << string(4 * size + 2, '-') << endl;
	for ( int i = 0; i < size; i++) {
		cout << i + 1 << "|";
		// run all columns in the row
		for ( int j = 0; j < size; j++) {
			cout << " " << this->matrix[i][j] << " |";
		}
		//print an empty row
		cout << endl << string(4 * size + 2, '-') << endl;
	}

}

Board::~Board(){
	for (int w = 0; w < size; w++)
	    delete[] matrix[w];
	delete[] matrix;
}

const char Board::get_cell(int row, int col) const {
	return this->matrix[row][col];
}

int Board::get_size() const {
	return size;
}

int Board::x_points() const {
	int points=0;
	for(int i = 0; i< size; i++){
		for(int j=0; j<size; j++) {
			if(matrix[i][j] == 'X'){
				points++;
			}
		}
	}
	return points;
}

int Board::o_points() const {
	int points=0;
	for(int i = 0; i< size; i++){
		for(int j=0; j<size; j++) {
			if(matrix[i][j] == 'O'){
				points++;
			}
		}
	}
	return points;
}

void Board::init_matrix() {
	for (int i = 0; i < size; ++i)
	    matrix[i] = new char[size];

	//initilized spaces ion matrix
	for (int i = 0; i < size; i++) {
		for(int j = 0; j< size; j++)
			this->matrix[i][j] = ' ';
	}

}

