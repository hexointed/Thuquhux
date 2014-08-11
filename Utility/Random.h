/*
 * File: Random.h
 * Author Elias Forsberg
 *
 * Created on August 8, 2014, 9:03
 *
 * This class, right?
 */

#ifndef UTILITY_RANDOM
#define UTILITY_RANDOM

#include <random>

class Random {
public:
	Random();

private:
	std::random_device rd;
	std::ranlux48_base gen;
	std::normal_distribution<> n_dist;

public:
	template<typename T>
	T uniform(T min, T max);
	
	template<typename T>
	T normal(T mean, T stddev);
};

#endif /* UTILITY_RANDOM */

#include "Random.hpp"
