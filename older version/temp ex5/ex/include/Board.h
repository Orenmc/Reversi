/*
 * Board.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Oren Cohen
 *      user: cohenorx
 *      id: 305164295
 *
 */

#ifndef BOARD_H_
#define BOARD_H_
#define SIZE 8
/**
 * Board is a sized matrix which u can place 'X' and 'O' in Board
 */
class Board {
public:
	/**
	 *constructor to build a Board object
	 */
	Board(int size);
	virtual ~Board();
	/**
	 * set a 'X' or 'O' (depend on player), in a specific place in matrix
	 * row.
	 * @param - int row - row of the cell in matrix, int col - column in matrix
	 *  char symbol - 'X' or 'O', which player is setting on this cell
	 *  @return - void type
	 */
	void set_matrix(int row, int col,char symbol);
	/**
	 * print matrix.
	 * @ return - void type.
	 */
	void print_matrix();
	/**
	 * free allocated memory (for the matrix).
	 */
	const char get_cell(int row, int col) const;
	/**
	 * @return - size of matrix.
	 */
	int get_size() const;
	int x_points() const;
	int o_points() const;
private:
	int size;
	char** matrix;
	void init_matrix();
};

#endif /* BOARD_H_ */
