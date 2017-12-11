/*
 * test_GameLogic.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: snirhazan
 */

#include "../include/GameLogic.h"
#include "gtest/gtest.h"
#include <vector>


TEST(Test_GameLogic,Test_Find_Options){

	Board* b = new Board(8);
	b->set_matrix(3,3,'O'),b->set_matrix(4,4,'O');
	b->set_matrix(3,4,'X'),b->set_matrix(4,3,'X');

	Player* p = new Player("Player",'X');
	vector<Point> start_points, end_points;
	vector<int> flip_number;
	GameLogic* g = new GameLogic(1,8);
	g->find_options(b,p, start_points, end_points, flip_number);

	vector<Point> start_points_good;
	std::vector<Point>::iterator it;
	it = start_points_good.begin();
	Point p1(2,3);
	Point p2(3,2);
	Point p3(4,5);
	Point p4(5,4);
	start_points_good.push_back(p1);
	start_points_good.push_back(p2);
	start_points_good.push_back(p3);
	start_points_good.push_back(p4);

	vector<Point> end_points_good;
	Point p5(4,3);
	Point p6(3,4);
	end_points_good.push_back(p5);
	end_points_good.push_back(p6);
	end_points_good.push_back(p5);
	end_points_good.push_back(p6);


	for(int i = 0; i < (int)start_points.size(); i++){
		EXPECT_TRUE(start_points[i].operator ==(start_points_good[i]));
	}
	for(int i = 0; i < (int)end_points.size(); i++){
		EXPECT_TRUE(end_points[i].operator ==(end_points_good[i]));
	}
	delete b;
	delete p;
	delete g;
}
TEST(Test_GameLogic,Test_Find_Options_Empty_Board){

	Board* b = new Board(8);
	Player* p = new Player("Player",'O');
	vector<Point> start_points, end_points;
	vector<int> flip_number;
	GameLogic* g = new GameLogic(1,8);
	g->find_options(b,p, start_points, end_points, flip_number);

	EXPECT_TRUE(start_points.size() == 0);
	EXPECT_TRUE(end_points.size() == 0);
	delete b;
		delete p;
		delete g;

}
TEST(Test_GameLogic,Test_number_of_flips_to_point){
	vector<Point> start_points, end_points;
	vector<int> flip_number;
	GameLogic* g = new GameLogic(1,8);

	g->set_on_board(0,0,g->get_player(1));
	g->set_on_board(0,1,g->get_player(1));
	g->set_on_board(0,2,g->get_player(1));
	g->set_on_board(1,1,g->get_player(2));

	start_points.push_back(Point(1,1));
	start_points.push_back(Point(1,2));
	start_points.push_back(Point(1,3));

	flip_number.push_back(1);
	flip_number.push_back(2);
	flip_number.push_back(3);

	int i = g->count_flops_for_spesific_point(Point(1,1),start_points,flip_number);
	int k = g->count_flops_for_spesific_point(Point(1,2),start_points,flip_number);
	int j = g->count_flops_for_spesific_point(Point(5,1),start_points,flip_number);

	EXPECT_EQ(i,1);
	EXPECT_EQ(j,0);
	EXPECT_EQ(k,2);
delete g;
}

TEST(Test_GameLogic,Test_Find_Options_Full_Board){

	Board* b = new Board(8);
	Player* p = new Player("Player",'O');
	vector<Point> start_points, end_points;
	vector<int> flip_number;
	GameLogic* g = new GameLogic(1,8);
	g->find_options(b,p, start_points, end_points, flip_number);
	for(int i= 0; i<8;i++){
		for(int j=0; j<8; j++){
			b->set_matrix(i,j,'X');
		}
	}
	EXPECT_TRUE(start_points.size() == 0);
	EXPECT_TRUE(end_points.size() == 0);
	delete b;
		delete p;
		delete g;
}

