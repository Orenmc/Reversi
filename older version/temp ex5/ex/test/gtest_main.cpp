/*
 * gtest_main.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: oren
 */
#include "gtest/gtest.h"

GTEST_API_ int main1( int argc, char** argv) {
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}



