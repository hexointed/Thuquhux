/* 
 * File:   TerrainGenerator.cpp
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:48 PM
 */

#include "Simplexnoise.h"
#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator():
        noise_octaves(16.0),
        noise_persistence(0.5),
        noise_frequency(1.0),
        noise_size(200.0),
        ground_detail(0.03)
{
    
}

void TerrainGenerator::genGround(){
    for(int i = 0; i < ground_size; i++){
        for(int n = 0; n < ground_size; n++){
            ground[i][n] = octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, (float)i/noise_size,(float)n/noise_size,0);
        }
    }
}

void TerrainGenerator::genGround(double width, double depth, double result[][3]){
    for(double x = -width/2.0; x <= width/2.0; x += ground_detail){
        for(double z = -depth/2.0; z <= depth/2.0; z += ground_detail){
            result[]
        }
    }
}

float TerrainGenerator::getGround(int x, int y){
    return this->ground[x][y];
}