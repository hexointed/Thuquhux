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
    double octave_noise_3d(const double octaves, const double persistence, const double scale,
                        const double x, const double y, const double z);
    double raw_noise_3d(const double x, const double y, const double z);

private:
    int perm[512];
    const int grad3[12][3];
    
    double dot(const int* g, const double x, const double y, const double z);
    int fastfloor(const double x);

};

#endif	/* SIMPLEXNOISE_H */

