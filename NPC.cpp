#include "NPC.h"
#include "PointVector.h"
#include <time.h>
#include "PhysObject.h"
#include <vector>

PointVector<> PLACEHOLDER_PLAYER_POSITION;
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL;
PointVector<> GRAVITY_CENTER;

double NPC::getPosition{

	for(;;){
		return PLACEHOLDER_PLAYER_POSITION;
	}

} 



double NPC::makePosition{
	
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

double NPC::updatePosition(deltaT){

	if(GRAVITY_CENTER.getdx() > position.getdx()){
		climbingAbilityx = INFINITY;
	}

	if(GRAVITY_CENTER.getdy() > position.getdy()){
		climbingAbilityy = INFINITY;
	}

	if(GRAVITY_CENTER.getdz() > position.getdz()){
		climbingAbilityz = INFINITY;
	}


	int k{
		if(randomBool == 1){
			k=1;
		}

		if(randomBool == 0){
			k=(-1);
		}
	}

	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;

	if(position.getdx() < PLACEHOLDER_LINE_OF_TRAVEL.getdx()){

		if(PLACEHOLDER_LINE_OF_TRAVEL.getdx() - (position.getdx() + k*sx) >= 0){
			position.setdx(position.getdx() + k*sx);
		}
		else{
			position.setdx(PLACEHOLDER_LINE_OF_TRAVEL.getdx());
		}
	}

	if(position.getdy() < PLACEHOLDER_LINE_OF_TRAVEL.getdy()){
		if(PLACEHOLDER_LINE_OF_TRAVEL.getdy() - (position.getdy() + k*sy) >= 0){
			position.setdy(position.getdy() + k*sy);
		}	
		else{
			position.setdy(PLACEHOLDER_LINE_OF_TRAVEL.getdy())
		}

	}

	if(position.getdz() < PLACEHOLDER_LINE_OF_TRAVEL.getdz()){
		if(PLACEHOLDER_LINE_OF_TRAVEL.getdz() - (position.getdz() + k*sz) >= 0){
			position.setdz(position.getdz() + k*sz);
		}
		else{
			position.setdz(PLACEHOLDER_LINE_OF_TRAVEL.getdz());
		}
	}

}




if(GRAVITY_CENTER.getdx() > position.getdx()){
	climbingAbilityx = INFINITY;
}

if(GRAVITY_CENTER.getdy() > position.getdy()){
	climbingAbilityy = INFINITY;
}

if(GRAVITY_CENTER.getdz() > position.getdz()){
	climbingAbilityz = INFINITY;
}
























}
