/* 
 * File:   TerrainGenerator.h
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:44 PM
 */

#ifndef TERRAINGENERATOR_H
#define	TERRAINGENERATOR_H

#define ground_size 1600

double def_height_scale(double height);

class TerrainGenerator{
public:
    TerrainGenerator();
    void genGround(double width, double depth, double alpha, double beta, double result[][3]);
    const int getGroundVertexSize();
    
private:
    Simplexnoise *noise_object;
    
    double ground_detail;
    double planet_radius;
    double (*height_scale)(double);
};

#endif	/* TERRAINGENERATOR_H */