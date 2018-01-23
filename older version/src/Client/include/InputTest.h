/*
 * InputTest.h
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef INPUTTEST_H_
#define INPUTTEST_H_

class InputTest {
public:
	/**
	 * return an integer from user - no letters.
	 */
	static int get_number_from_user();
	/**
	 * return int between 2 to 12 (accept only even numbers) reject anything else
	 */
	static int get_size_from_user();
/**
 * return integer (between 0 to max index) - and reject anything else
 */
	static int get_index_from_user(int max_index);
/**
 * press any key to continue - till enter
 */
	static void press_any_key();
	/**
	 * return integer (1 OR 2 for now) - and reject anything else
	 */
	static int get_number_for_menu();
};

#endif /* INPUTTEST_H_ */
