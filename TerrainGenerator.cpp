/* 
 * File:   TerrainGenerator.cpp
 * Author: Elias Forsberg
 *
 * Created on April 7, 2013, 7:48 PM
 */

#include "Simplexnoise.h"
#include "TerrainGenerator.h"
#include <math.h>
#include <iostream>


#define PI 3.1415926535897932
#define fov_length 6
#define fov_near 6.5


TerrainGenerator::TerrainGenerator():
        noise_octaves(16.0),
        noise_persistence(0.5),
        noise_frequency(1.0),
        noise_size(200.0),
        ground_detail(70),
        planet_radius(70.0),
        height_scale(def_height_scale)
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
    double d_phi = fov_near/planet_radius/ground_detail;
    double d_theta = fov_length/planet_radius/ground_detail;
    double r_fov = (PI - fov_near/planet_radius)/2;
    double l_fov = fov_near/planet_radius + (PI - fov_near/planet_radius)/2;
    int count = 0;
    
    for(double theta = PI/2; theta <= fov_length/planet_radius + PI/2; theta += d_theta){
        for(double phi = r_fov; phi <= l_fov; phi += d_phi){
            double height = height_scale(octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, 
                                         sin(theta) * cos(phi) * planet_radius,
                                         sin(theta) * sin(phi) * planet_radius,
                                         cos(theta) * planet_radius));
            
            result[count][0] = sin(theta) * cos(phi) * planet_radius + height;
            result[count][1] = sin(theta) * sin(phi) * planet_radius + height;
            result[count][2] = cos(theta) * planet_radius + height;
            
            height = height_scale(octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, 
                                  sin(theta + d_theta) * cos(phi + d_phi) * planet_radius,
                                  sin(theta + d_theta) * sin(phi + d_phi) * planet_radius,
                                  cos(theta + d_theta) * planet_radius));
            
            result[count+1][0] = sin(theta + d_theta) * cos(phi + d_phi) * planet_radius + height;
            result[count+1][1] = sin(theta + d_theta) * sin(phi + d_phi) * planet_radius + height;
            result[count+1][2] = cos(theta + d_theta) * planet_radius + height;
            
            count += 2;
        }
        for(double phi = l_fov; phi >= r_fov; phi -= d_phi){
            double height = height_scale(octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, 
                                         sin(theta) * cos(phi) * planet_radius,
                                         sin(theta) * sin(phi) * planet_radius,
                                         cos(theta) * planet_radius));
            
            result[count][0] = sin(theta) * cos(phi) * planet_radius + height;
            result[count][1] = sin(theta) * sin(phi) * planet_radius + height;
            result[count][2] = cos(theta) * planet_radius + height;
            
            height = height_scale(octave_noise_3d(noise_octaves, noise_persistence, noise_frequency, 
                                  sin(theta + d_theta) * cos(phi + d_phi) * planet_radius,
                                  sin(theta + d_theta) * sin(phi + d_phi) * planet_radius,
                                  cos(theta + d_theta) * planet_radius));
            
            result[count+1][0] = sin(theta + d_theta) * cos(phi + d_phi) * planet_radius + height;
            result[count+1][1] = sin(theta + d_theta) * sin(phi + d_phi) * planet_radius + height;
            result[count+1][2] = cos(theta + d_theta) * planet_radius + height;
            
            count += 2;
        }
    }
    std::cout<<count<<std::endl;
}

float TerrainGenerator::getGround(int x, int y){
    return this->ground[x][y];
}

double def_height_scale(float height){
    return (double) height * 0.3;
}