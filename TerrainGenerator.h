/* 
 * File:   TerrainGenerator.h
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:44 PM
 */

#ifndef TERRAINGENERATOR_H
#define	TERRAINGENERATOR_H

#define ground_size 1600
#define ground_detail 1

class TerrainGenerator{
public:
    TerrainGenerator();
    void genGround();
    float getGround(int x, int y);
    
//private:
    float ground[ground_size][ground_size];
};

#endif	/* TERRAINGENERATOR_H */