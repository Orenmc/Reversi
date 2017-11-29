/*
 * test_Board.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: snirhazan
 */

#include "gtest/gtest.h"
#include "Board.h"

TEST(Test_Board,Test_init_Board){
	Board* b = new Board(8);
	b->print_matrix();
	for(int i = 0 ; i < b->get_size() ; i++){
		for(int j = 0 ; j < b->get_size(); j++){
				EXPECT_EQ(b->get_cell(i,j),' ');
			}
		}
	delete b;
}


TEST(Test_Board,Test_Score_Player){
	Board* b = new Board(8);
	b->set_matrix(2,2,'X');
	b->set_matrix(2,4,'O');
	b->set_matrix(5,6,'O');
	EXPECT_EQ(b->o_points(),4);
	EXPECT_EQ(b->x_points(),3);
	delete b;
}

TEST(Test_Board,Test_Set_In_Board){
	Board* b = new Board(8);
	b->set_matrix(2,2,'X');
	b->set_matrix(7,7,'O');
	EXPECT_EQ(b->get_cell(2,2),'X');
	EXPECT_EQ(b->get_cell(7,7),'O');
	delete b;
}
