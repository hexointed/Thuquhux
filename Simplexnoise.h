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
    Simplexnoise(int seed, double frequency=0.09, int octaves=8);
    
    double operator()(double x, double y, double z);
    double operator()(double x, double y, double z, double w);
    
    void setOctaves(double o);
    void setFrequency(double f);
    
private:
    double raw_noise_3d(const double x, const double y, const double z);
    double raw_noise_4d(const double x, const double y, const double z, const double w);
    
    double dot(const int* g, const double x, const double y, const double z);
    double dot(const int* g, const double x, const double y, const double z, const double w);
    
    int fastfloor(const double x);
    
private:
    int noise_octaves;
    double noise_persistence;
    double noise_frequency;
    
    int perm[512];
    
    int grad3[12][3];
    int grad4[32][4];
    
    int simplex[64][4];
};

#endif	/* SIMPLEXNOISE_H */

