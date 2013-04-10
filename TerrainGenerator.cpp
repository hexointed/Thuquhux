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
        ground_detail(0.3)
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
    int counter = 0;
    for(double z = -depth/2; z < depth/2 - ground_detail; z += 2.0 * ground_detail){
        for(double x = -width/2; x < width/2; x += ground_detail){
            result[counter][0] = x;
            result[counter][1] = octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, x/noise_size, z/noise_size, 0);
            result[counter][2] = z;
            result[counter+1][0] = x;
            result[counter+1][1] = octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, x/noise_size, (z+ground_detail)/noise_size, 0);
            result[counter+1][2] = z + ground_detail;
        }
        for(double x = width/2; x > -width/2; x -= ground_detail){
            result[counter+1][0] = x;
            result[counter+1][1] = octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, x/noise_size, (z+ground_detail)/noise_size, 0);
            result[counter+1][2] = z + ground_detail;
            result[counter+2][0] = x;
            result[counter+2][1] = octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, x/noise_size, (z+2*ground_detail)/noise_size, 0);
            result[counter+2][2] = z + 2 * ground_detail;
        }
        counter += 2;
    }
}

float TerrainGenerator::getGround(int x, int y){
    return this->ground[x][y];
}