#include "NPC.h"

static PointVector<> PLACEHOLDER_PLAYER_POSITION{70,15,35};
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL{PLACEHOLDER_PLAYER_POSITION};
PointVector<> GRAVITY_CENTER{0,0,0};
double RADIUS = 25.0;

NPC::NPC(){
	position = {4,600,17845};
	//position = makePosition();
	direction = 0; //randomBool();
	velocityx = 8; //makeVelocityx();
	velocityy = 3; //makeVelocityy();
	velocityz = 4; //makeVelocityz();
	climbingAbilityx = 1.0/0.0; //makeClimbingAbilityx();
	climbingAbilityy = 1.0/0.0; //makeClimbingAbilityy();
	climbingAbilityz = 1.0/0.0; //makeClimbingAbilityz();
}

PointVector<> NPC::makePosition(){
	srand(time(0));
	position.setdx(rand());
	position.setdy(rand());
	position.setdz(rand());

	return position;
}


double NPC::makeClimbingAbilityx(){
	return rand() % 11;
}


double NPC::makeClimbingAbilityy(){
	return rand() % 11;
}


double NPC::makeClimbingAbilityz(){
	return rand() % 11;
}


int NPC::makeVelocityx(){
	return rand() % 30;
}


int NPC::makeVelocityy(){
	return rand() % 30;
}


int NPC::makeVelocityz(){
	return rand() % 30;
}


bool NPC::randomBool(){
	return rand() % 2;
}


int NPC::randomInt(){
	return rand() % 50;
}



PointVector<> NPC::updatePosition(double deltaT){
	
	double infinity = 1.0/0.0;
	
	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;


	/*if(randomInt() == 2){
		position.setdx(position.getdx());
		position.setdy(position.getdy());
		position.setdz(position.getdz());
 	}
	
	else{*/
		int k = direction == 1 ? 1 : -1;

		if(GRAVITY_CENTER.getdx() > position.getdx()){
			climbingAbilityx = infinity;
		}
	
	
		if(GRAVITY_CENTER.getdy() > position.getdy()){
			climbingAbilityy = infinity;
		} 


		if(GRAVITY_CENTER.getdz() > position.getdz()){
			climbingAbilityz = infinity;
		}

		
			static int p = 0;
			static int q = 0;
			static int r = 0;

		
			if(position.getdx() != PLACEHOLDER_LINE_OF_TRAVEL[p].getdx()){

				if(sx<climbingAbilityx){

					if((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + k*sx)) >= 0){
						position.setdx(position.getdx() + k*sx);
					}

					else{
						position.setdx(PLACEHOLDER_LINE_OF_TRAVEL[p].getdx());
					}
				}
		
				else{
					position.setdx(position.getdx() - k*sx);	
				}
			
			}
			
			else{
				position.setdx(position.getdx());
			}
			
			
			if(position.getdy() != PLACEHOLDER_LINE_OF_TRAVEL[q].getdy()){

				if(sy<climbingAbilityy){

					if((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + k*sy)) >= 0){
						position.setdy(position.getdy() + k*sy);
					}

					else{
						position.setdy(PLACEHOLDER_LINE_OF_TRAVEL[q].getdy());
					}
				}
		
				else{
					position.setdy(position.getdy() - k*sy);	
				}
			
			}
			
			else{
				position.setdy(position.getdy());
			}			
		
		
			if(position.getdz() != PLACEHOLDER_LINE_OF_TRAVEL[r].getdz()){

				if(sz<climbingAbilityz){

					if((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + k*sz)) >= 0){
						position.setdz(position.getdz() + k*sz);
					}

					else{
						position.setdz(PLACEHOLDER_LINE_OF_TRAVEL[r].getdz());
					}
				}
		
				else{
					position.setdz(position.getdz() - k*sz);	
				}
			
			}
			
			else{
				position.setdz(position.getdz());
			}		
		
		
		
		
		

	
	//}
	return position;
}

