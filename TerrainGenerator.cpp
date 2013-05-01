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
#include <ctime>


#define PI 3.1415926535897932

TerrainGenerator::TerrainGenerator():
        ground_detail(150),
        planet_radius(80.0),
        height_scale(def_height_scale)
{
    noise_object = new Simplexnoise(time(0));
}

void TerrainGenerator::genGround(double fov_near, double fov_length, double alpha, double beta, double result[][3]){
    double d_phi = fov_near/planet_radius/ground_detail;
    double d_theta = fov_length/planet_radius/ground_detail;
    double r_fov = (PI - fov_near/planet_radius)/2;
    double l_fov = fov_near/planet_radius + (PI - fov_near/planet_radius)/2;
    int count = 0;
    
    for(double theta = PI/2; theta <= fov_length/planet_radius + PI/2; theta += d_theta){
        for(double phi = r_fov; phi <= l_fov; phi += d_phi){
            
            double unit_x = sin(theta) * cos(phi);
            double unit_y = sin(theta) * sin(phi);
            double unit_z = cos(theta);
            
            double height = height_scale(noise_object->octave_noise_3d(
                                         unit_x * planet_radius * cos(beta) + unit_y * planet_radius * sin(beta),
                                         (unit_y * planet_radius * cos(alpha) + unit_z * planet_radius * sin(alpha)) * cos(beta) + unit_x * planet_radius * -sin(beta),
                                         unit_z * planet_radius * cos(alpha) + unit_y * planet_radius *-sin(alpha) ));
            
            result[count][0] = unit_x * planet_radius + height * unit_x;
            result[count][1] = unit_y * planet_radius + height * unit_y - planet_radius;
            result[count][2] = unit_z * planet_radius + height * unit_z;
                    
            unit_x = sin(theta + d_theta) * cos(phi);
            unit_y = sin(theta + d_theta) * sin(phi);
            unit_z = cos(theta + d_theta);
            
            height = height_scale(noise_object->octave_noise_3d( 
                                         unit_x * planet_radius * cos(beta) + unit_y * planet_radius * sin(beta),
                                         (unit_y * planet_radius * cos(alpha) + unit_z * planet_radius * sin(alpha)) * cos(beta) + unit_x * planet_radius * -sin(beta),
                                         unit_z * planet_radius * cos(alpha) + unit_y * planet_radius *-sin(alpha) ));
            
            result[count + 1][0] = unit_x * planet_radius + height * unit_x;
            result[count + 1][1] = unit_y * planet_radius + height * unit_y - planet_radius;
            result[count + 1][2] = unit_z * planet_radius + height * unit_z;
            
            count += 2;
        }
        for(double phi = l_fov; phi >= r_fov; phi -= d_phi){
            
            double unit_x = sin(theta) * cos(phi);
            double unit_y = sin(theta) * sin(phi);
            double unit_z = cos(theta);
            
            double height = height_scale(noise_object->octave_noise_3d( 
                                         unit_x * planet_radius * cos(beta) + unit_y * planet_radius * sin(beta),
                                         (unit_y * planet_radius * cos(alpha) + unit_z * planet_radius * sin(alpha)) * cos(beta) + unit_x * planet_radius * -sin(beta),
                                         unit_z * planet_radius * cos(alpha) + unit_y * planet_radius *-sin(alpha) ));
            
            result[count][0] = unit_x * planet_radius + height * unit_x;
            result[count][1] = unit_y * planet_radius + height * unit_y - planet_radius;
            result[count][2] = unit_z * planet_radius + height * unit_z;
                    
            unit_x = sin(theta + d_theta) * cos(phi);
            unit_y = sin(theta + d_theta) * sin(phi);
            unit_z = cos(theta + d_theta);
            
            height = height_scale(noise_object->octave_noise_3d( 
                                         unit_x * planet_radius * cos(beta) + unit_y * planet_radius * sin(beta),
                                         (unit_y * planet_radius * cos(alpha) + unit_z * planet_radius * sin(alpha)) * cos(beta) + unit_x * planet_radius * -sin(beta),
                                         unit_z * planet_radius * cos(alpha) + unit_y * planet_radius *-sin(alpha) ));
            
            result[count + 1][0] = unit_x * planet_radius + height * unit_x;
            result[count + 1][1] = unit_y * planet_radius + height * unit_y - planet_radius;
            result[count + 1][2] = unit_z * planet_radius + height * unit_z;
            
            count += 2;
        }
    }
}

const int TerrainGenerator::getGroundVertexSize(){
    return (const int) 4*ground_detail*ground_detail + 8 * ground_detail + 4;
}

void TerrainGenerator::get_distrib_points(int points, double result[][3], double solid_angle){
	double inc = PI * (3 - sqrt(5));
	double off = 2.0/points/(solid_angle/(2*PI));
	for(int i = 0; i < points; i++){
		double y = i * off - 1 + (off/2.0);
		double r = sqrt(1 - y*y);
		double phi = i * inc;
		result[i][0] = cos(phi)*r;
		result[i][1] = y;
		result[i][2] = sin(phi)*r;
	}
}

double def_height_scale(double height){
    return (double) height * 4;
}
