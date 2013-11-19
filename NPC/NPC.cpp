#include "NPC.h"
#include "PointVector.h"
#include <time.h>
#include "PhysObject.h"
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES

PointVector<> position;		//Position of the NPC
PointVector<> PLACEHOLDER_PLAYER_POSITION;
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL;
PointVector<> GRAVITY_CENTER;
double RADIUS;

void NPC::makePosition(){
	srand(time(0));
	position.setdx(rand());
	position.setdy(rand());
	position.setdz(rand());
}


double NPC::climbingAbilityx(){
	srand (time(NULL));
	climbingAbilityx = rand() % 11;
	
	return climbingAbilityx;
}


double NPC::climbingAbilityy(){
	srand (time(NULL));
	climbingAbilityy = rand() % 11;
	
	return climbingAbilityy;
}


double NPC::climbingAbilityz(){
	srand (time(NULL));
	climbingAbilityz = rand() % 11;
	
	return climbingAbilityz;
}


int NPC::velocityx(){
	srand (time(NULL));
	velocityx = rand() % 30;
	return velocityx;
}


int NPC::velocityy(){
	srand (time(NULL));
	velocityy = rand() % 30;
	return velocityy;
}


int NPC::velocityz(){
	srand (time(NULL));
	velocityz = rand() % 30;
	return velocityz;
}


bool randomBool{
srand(time(NULL));
randomBool = rand() % 2;

return randomBool;
}


int NPC::randomInt(){
	srand (time(NULL));
	int randomInt = rand() % 50;
	
	return randomInt;
}


double NPC::updatePosition(deltaT){
	
	double infinity = 1.0/0.0;

	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;


	if(randomInt == 2){
		position.setdx(position.getdx());
		position.setdy(position.getdy());
		position.setdz(position.getdz());
 	}
	
	else{
		int k = randomBool == 1 ? 1 : -1;

		if(GRAVITY_CENTER.getdx() > position.getdx()){
			climbingAbilityx = infinity;
		}
	
	
		if(GRAVITY_CENTER.getdy() > position.getdy()){
			climbingAbilityy = infinity;
		} 


		if(GRAVITY_CENTER.getdz() > position.getdz()){
			climbingAbilityz = infinity;
		}

		
		if(position.getdx() < PLACEHOLDER_LINE_OF_TRAVEL.getdx()){
			if(sx<climbingAbilityx){

				if((PLACEHOLDER_LINE_OF_TRAVEL.getdx() - (position.getdx() + k*sx)) >= 0){
					position.setdx(position.getdx() + k*sx);
				}

				else{
					position.setdx(PLACEHOLDER_LINE_OF_TRAVEL.getdx());
				}
			}
		
			else{
				position.setdx(position.getdx() - k*sx);	
			}
		}

		
		if(position.getdy() < PLACEHOLDER_LINE_OF_TRAVEL.getdy()){
			if(sy<climbingAbilityy){
		
				if(PLACEHOLDER_LINE_OF_TRAVEL.getdy() - (position.getdy() + k*sy) >= 0){
					position.setdy(position.getdy() + k*sy);
				}	
				else{
					position.setdy(PLACEHOLDER_LINE_OF_TRAVEL.getdy())
				}
			}
		
			else{
					position.setdy(position.getdy() - k*sy,);	
			}
		}

		
		if(position.getdz() < PLACEHOLDER_LINE_OF_TRAVEL.getdz()){
			if(sz<climbingAbilityz){
			
				if(PLACEHOLDER_LINE_OF_TRAVEL.getdz() - (position.getdz() + k*sz) >= 0){
					position.setdz(position.getdz() + k*sz);
				}	
				else{
					position.setdz(PLACEHOLDER_LINE_OF_TRAVEL.getdz())
				}
			}
			
			else{
					position.setdz(position.getdz() - k*sz,);	
			}
		}
	}	

	return position.getdx();
	return position.getdy();
	return position.getdz();
	}

}
