/*
 * File: Random.hpp
 * Author: Elias Forsberg
 *
 * Created on August 8, 2014, 10:15
 */

#ifndef UTILITY_RANDOM_HPP
#define UTILITY_RANDOM_HPP

template<typename T>
T Random::uniform(T min, T max){
	std::uniform_real_distribution<> r_dist(min, max);
	return r_dist(gen);
}

template<typename T>
T Random::normal(T mean, T stddev){
	return n_dist(gen) * stddev + mean;
}

#endif /* UTILITY_RANDOM_HPP */
