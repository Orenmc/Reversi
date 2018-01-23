/*
 * test_Point.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: snirhazan
 */

#include "gtest/gtest.h"
#include "Point.h"

TEST(Test_Point,Test_Valid_Point){
	Point p1(-2,3);
	EXPECT_FALSE(p1.valid_point());
	Point p2(0,0);
    EXPECT_TRUE(p2.valid_point());
	Point p3(5,2);
	EXPECT_TRUE(p3.valid_point());

}

TEST(Test_Point,Test_Equals_Point){
	Point p1(-2,3);
	Point p2(-2,3);
	Point p3(-2,10);

	EXPECT_TRUE(p1.operator ==(p2));
	EXPECT_FALSE(p1.operator ==(p3));
}

