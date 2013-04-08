/* 
 * File:   TerrainGenerator.cpp
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:48 PM
 */

#include "Simplexnoise.h"
#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(){
    
}

void TerrainGenerator::genGround(){
    for(int i = 0; i < ground_size; i++){
        for(int n = 0; n < ground_size; n++){
            ground[i][n] = octave_noise_3d(15.0, 0.5, 1, (float)i/200.0,(float)n/200.0,0);
        }
    }
}

float TerrainGenerator::getGround(int x, int y){
    return this->ground[x][y];
}