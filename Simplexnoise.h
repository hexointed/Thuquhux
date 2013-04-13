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
    float octave_noise_3d(const float octaves, const float persistence, const float scale,
                        const float x, const float y, const float z);
    float raw_noise_3d(const float x, const float y, const float z);

private:
    int perm[512];
    const int grad3[12][3];
    
    float dot(const int* g, const float x, const float y, const float z);
    int fastfloor(const float x);

};

#endif	/* SIMPLEXNOISE_H */

