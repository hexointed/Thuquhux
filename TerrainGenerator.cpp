/* 
 * File:   TerrainGenerator.cpp
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:48 PM
 */

#include "Simplexnoise.h"
#include "TerrainGenerator.h"
#include <math.h>
#define PI 3.1415926535897932
#include <iostream>

TerrainGenerator::TerrainGenerator():
        noise_octaves(16.0),
        noise_persistence(0.5),
        noise_frequency(1.0),
        noise_size(200.0),
        ground_detail(0.3),
        planet_radius(0.5)
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
    int count = 0;
    for(double theta = 0; theta < 2 * PI; theta += PI/16.0){
        for(double phi = 0; phi < 2 * PI; phi += PI/16.0){
            result[count][0] = sin(theta) * cos(phi) * planet_radius;
            result[count][1] = sin(theta) * sin(phi) * planet_radius;
            result[count][2] = cos(theta) * planet_radius;
            count++;
            std::cout<<count<<std::endl;
        }
    }
}

float TerrainGenerator::getGround(int x, int y){
    return this->ground[x][y];
}