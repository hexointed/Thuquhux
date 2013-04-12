/* 
 * File:   TerrainGenerator.h
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:44 PM
 */

#ifndef TERRAINGENERATOR_H
#define	TERRAINGENERATOR_H

#define ground_size 1600

double def_height_scale(float height);

class TerrainGenerator{
public:
    TerrainGenerator();
    void genGround();
    void genGround(double width, double depth, double result[][3]);
    float getGround(int x, int y);
    
private:
    float ground[ground_size][ground_size];
    
    double noise_size;
    float noise_octaves;
    float noise_persistence;
    float noise_frequency;
    
    double ground_detail;
    double planet_radius;
    double (*height_scale)(float);
};

#endif	/* TERRAINGENERATOR_H */