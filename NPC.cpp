#include "NPC.h"
#include "PointVector.h"
#include <time.h>
#include "PhysObject.h"
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES

PointVector<> PLACEHOLDER_PLAYER_POSITION;
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL;
PointVector<> GRAVITY_CENTER;
double RADIUS;

PointVector<> NPC::getPosition(){

	for(;;){
		return PLACEHOLDER_PLAYER_POSITION;
	}

} 



void NPC::makePosition(){
	
	srand(time(0));
	position.getdx = rand();
	position.getdy = rand();
	position.getdz = rand();

}

bool randomBool{
srand(time(0));
for( int i = 0; i < 1000000; ++i )
{
    assert( 0 == ( rand() % 2 ) );
}
}

double NPC::climbingAbilityx(){
	srand ( time(NULL) );
	climbingAbilityx = rand() % 11;
	
	return climbingAbilityx;
}


double NPC::climbingAbilityy(){
	srand ( time(NULL) );
	climbingAbilityy = rand() % 11;
	
	return climbingAbilityy;
}


double NPC::climbingAbilityz(){
	srand (time(NULL));
	climbingAbilityz = rand() % 11;
	
	return climbingAbilityz;
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
		srand (time(NULL));
		int d = 2 + (rand() % 5);
		PointVector<> u = PointVector<>::make_unit(d + RADIUS - CENTER_OF_GRAVITY);		
		

/*
		static const int c = position.getdx();



		if(position.getdx<(c+2)){
			position.setdx(position.getdx()+sx);
		} 		


		else if(sqrt((position.getdx())*(position.getdx()) + (position.getdy())*(position.getdy()) + (position.getdz())*(position.getdz())) > RADIUS + d){
			


		}

		else{
			static double b = 0;
			static const double a = position.getdx();		
			position.setdx(a+sin(b*M_PI/90));
			b++;
		}
 	}*/
	
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
}























}
