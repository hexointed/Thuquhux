/* 
 * File:   Simplexnoise.h
 * Author: elias
 *
 * Created on April 7, 2013, 3:43 PM
 */

#ifndef SIMPLEXNOISE_H
#define	SIMPLEXNOISE_H

class Simplexnoise{
public:
    Simplexnoise(int seed);
    double octave_noise_3d(const double x, const double y, const double z);
    
private:
    double raw_noise_3d(const double x, const double y, const double z);
    double dot(const int* g, const double x, const double y, const double z);
    int fastfloor(const double x);
    
private:
    double noise_octaves;
    double noise_persistence;
    double noise_frequency;
    
    int perm[512];
    const int grad3[12][3];
};

#endif	/* SIMPLEXNOISE_H */

