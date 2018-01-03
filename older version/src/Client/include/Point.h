/*
 * Point.h
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#ifndef POINT_H_
#define POINT_H_
#include <iostream>
using namespace std;

class Point {
public:
	Point(int x, int y);
	int getX() const;
	int getY() const;
	/**
	 * for a bad point x&Y <0,
	 * @return false if point not good, else return true
	 */
	bool valid_point() const;
	/**
	 * p1.x == p2.x && p1.y == p2.y
	 * return true if equals else false
	 */
	bool operator ==(const Point &p) const;
	/**
	 * need to define for (== is !(a<b) && !(b<a))
	 */
	bool operator <(const Point &p) const;
	friend ostream &operator << (ostream &out, const Point &p);

private:
	int x;
	int y;
};

#endif /* POINT_H_ */
