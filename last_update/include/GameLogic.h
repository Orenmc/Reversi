/*
 * GameLogic.h
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Point.h"
#include <set>
#include <vector>
#include "InputTest.h"

class GameLogic {
public:
	GameLogic(int chooise);
	virtual ~GameLogic();
	/**
	 * play 1 turn for specific player.
	 * @param - Player player
	 * @return - int 0 if played, 1 if not
	 */
	int play_one_turn(Player* p1);
	/**
	 * check if game should stop.
	 * @return - true stop, false continue
	 */
	bool is_should_stop() const;
	/**
	 * Standard set.
	 */
	void set_should_stop(bool shouldStop);
	/**
	 * print board.
	 */
	void print_board();
	/**
	 * sets players symbol on board.
	 * @param - int row - row to set on board, int col - col to set on board, Player player - player to put symbol
	 */
	void set_on_board(Board* b,int row, int col, Player* player);
	/**
	 * get player number i (starting from 1).
	 * @param int i - is number of player
	 * @return - Player player.
	 */
	Player* get_player(int i) const;
	/**
	 * find all available cell to put symbol player in board.
	 * for each good point - save in vector point start, point end, and
	 * @param - Player* p - pointer to player.
	 * @param - vector<Point> &starts - contain all good cells (with duplicates)
	 * @param - vector<points &end - to each start point, save in the same index the point end
	 * @param - vector<int> &v3 - to each start point, save in the same index the number of flops between p start and point end
	 */
	void find_options(Board* b,Player* player, vector<Point>& start, vector<Point>& end,vector<int>& flips) const;
	/**
	 * for 2 points, and player - change all other player symbols between them.
 	 * @param Point p1 - start point ,Point p2 - end point, Player* player point.
 	 */
	void change_board_point_to_point(Board* b,Point p1, Point p2, Player* p);
    /**
     *
     * @param it
     * @param p1
     * @param p2
     * @return
     */
    int check_point_for_AI(Point p, vector<Point> start_points, vector<Point> end_points, vector<int> flip_ctr);
	/**
	 * for a given point change all point in vector<Point> how match.
	 * @param Playe* p - pointer to player, Point p_choose -point to change
	 * @param vector<Point> start - contain all available points (with duplicates)
	 * @param - vector<points &end - to each start point, save in the same index the point end
	 * @param - vector<int> &v3 - to each start point, save in the same index the number of flops between p start and point end
	 */
	void change_all_points(Board* b,Player *p, Point p_choose, vector<Point> start_points, vector<Point> end_points, vector<int> flip_ctr);
	/**
	 * for a specific point find total flip number.
	 *@param Point p - point
	 * @param vector<Point> start - contain all available points (with duplicates)
	 * @param - vector<int> &v3 - to each start point, save in the same index the number of flops between p start and point end
	* @return total number of flips.
	*/
	int const count_flops_for_spesific_point(Point p,vector<Point> start,vector<int> flip_number) const;
	/**
	 * check if board is full;
	 * @return true - if full, else false
	 */
	bool board_full();
	int player1_points(Board* b);
	int player2_points(Board* b);
	int player1_points();
	int player2_points();
	void print_board(Board* b);

private:
	/**
	 * check if Point is on set.
	 * @return true if point in set, else false
	 */
	bool is_point_in_set(Point p, set<Point> s);
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_right(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_left(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_up(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_down(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_up_right(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_down_right(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_up_left(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	/**
	 * for specific row,col check if specific symbol can be placed there
	 * @param row,col - specific "point",
	 * @param Player* - pointer to player
	 * @param int& flip_ctr
	 * @return (-1,-1) if not good point, else return the end point (that verify good cell)
	 */
	Point check_down_left(Board* b,int row, int col, Player* player, int &flip_ctr) const;
	bool should_stop;
	Board *board;
	Player *players[2];
};

#endif /* GAMELOGIC_H_ */
