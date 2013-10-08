#include "NPC.h"
#include "PointVector.h"
#include <time.h>
#include "PhysObject.h"
#include <vector>
#include <iostream>

PointVector<> PLACEHOLDER_PLAYER_POSITION;
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL;
PointVector<> GRAVITY_CENTER;

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

bool NPC::randomness(){
	srand (time(NULL));
	int randomInt = rand() % 50;
	
	randomness = randomInt == 2 ?  1 : 0;
}


double NPC::updatePosition(deltaT){

	double infinity = 1.0/0.0;

	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;


	if(random == 1){
		static double b;
		konstant double a = position.getdx();		
		position.setdx(a+sin(b));
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
}























}
