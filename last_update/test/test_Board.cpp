/*
 * test_Board.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: snirhazan
 */

#include "gtest/gtest.h"
#include "Board.h"
#include "GameLogic.h"

TEST(Test_Board,Test_init_Board){
	Board* b = new Board(8);
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
	EXPECT_EQ(b->o_points(),2);
	EXPECT_EQ(b->x_points(),1);
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

TEST(Test_Board,Test_Point_To_Point){
	Board* b = new Board(8);
	b->set_matrix(2,2,'X');
	b->set_matrix(4,4,'X');
	Player* p = new Player("Player",'X');
	Point p1(2,2);
	Point p2(4,4);

	GameLogic* g = new GameLogic(1,8);
	g->change_board_point_to_point(b,p1,p2,p);

	for(int i=2; i< 5; i++){
	EXPECT_EQ('X',b->get_cell(i,i));
	}
	delete b;
	delete p;
	delete g;
}
