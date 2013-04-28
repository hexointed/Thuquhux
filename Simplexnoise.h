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
    double octave_noise_4d(const double x, const double y, const double z, const double w);
    
private:
    double raw_noise_3d(const double x, const double y, const double z);
    double raw_noise_4d(const double x, const double y, const double z, const double w);
    double dot(const int* g, const double x, const double y, const double z);
    int fastfloor(const double x);
    
private:
    double noise_octaves;
    double noise_persistence;
    double noise_frequency;
    
    int perm[512];
    
    int grad3[12][3];
    int grad4[32][4];
    
    int simplex[64][4];
};

#endif	/* SIMPLEXNOISE_H */

