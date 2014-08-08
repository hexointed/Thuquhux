/*
 * File: Random.hpp
 * Author: Elias Forsberg
 *
 * Created on August 8, 2014, 10:15
 */

#ifndef UTILITY_RANDOM
#define UTILITY_RANDOM

template<typename T>
T Random::uniform(T min, T max){
	std::uniform_real_distribution<> r_dist(min, max);
	return r_dist(gen);
}

template<>
int Random::unifom(int min, int max){
	std::uniform_int_distribution<> i_dist(min, max);
	return i_dist(gen);
}

template<typename T>
T Random::normal(T mean, T stddev){
	return n_dist(gen) * stddev + mean;
}

#endif /* UTILITY_RANDOM */
