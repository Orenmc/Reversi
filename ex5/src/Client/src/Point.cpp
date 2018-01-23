/*
 * Point.cpp
 *
 *  Created on	: Nov 14, 2017
 *    	Author	: Oren Cohen
 *      user	: cohenorx
 *      id		: 305164295
 */

#include "../include/Point.h"

int Point::getX() const {
	return x;
}

Point::Point(int x, int y): x(x), y(y) {
}

int Point::getY() const {
	return y;
}

bool Point::operator ==(const Point& p) const {
	if(this->x == p.getX() && this->y == p.getY()) {
		return true;
	}
	return false;
}

bool Point::valid_point() const {
	if (this->getX() < 0 || this->getY() < 0){
		return false;
	}
	return true;
}


bool Point::operator <(const Point& p) const {
	return !(*this == p);
}

ostream &operator <<(ostream &out, const Point &p) {
	out <<"(" <<p.getX() + 1 << "," << p.getY() + 1 << ")";
	return out;
}
