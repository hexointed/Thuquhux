/* 
 * File:   TerrainGenerator.h
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:44 PM
 */

#ifndef TERRAINGENERATOR_H
#define	TERRAINGENERATOR_H

#include <vector>
#include "PhysObject.h"

#define TERRAIN_TREES 0
#define TERRAIN_RIVERS 1
#define TERRAIN_MOUNTAINS 2

double def_height_scale(double height);

class TerrainGenerator{
public:
    TerrainGenerator();
    
    void genGround(double width, double depth, double alpha, double beta, double result[][3]);
    const int getGroundVertexSize();
    
    std::vector<PhysObject> operator()(double alpha, double beta);
    const TerrainGenerator& operator= (const TerrainGenerator& v) const;
    
    void enable (int TERRAIN_TYPE);
    void disable(int TERRAIN_TYPE);
    
private:
    Simplexnoise *noise_object;
    
    double ground_detail;
    double planet_radius;
    double (*height_scale)(double);
    
    double generate_length;
    double generate_width;
    double generate_depth;
};

#endif	/* TERRAINGENERATOR_H */