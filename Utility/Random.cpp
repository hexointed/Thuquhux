/*
 * File: Random.cpp
 * Author: Elias Forsberg
 *
 * Created on August 8, 2014, 9:07
 */

#include "Random.h"

Random::Random():
	rd(),
	gen(rd()),
	n_dist(0,1)
{}
