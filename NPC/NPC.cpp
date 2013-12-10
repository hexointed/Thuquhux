#include "NPC.h"

static PointVector<> PLACEHOLDER_PLAYER_POSITION{130, 50, 28};
static PointVector<> PLACEHOLDER_TMP{80,90,35};
static PointVector<> DDD{100,25,79};
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL{DDD, PLACEHOLDER_TMP, PLACEHOLDER_PLAYER_POSITION};
PointVector<> GRAVITY_CENTER{0,0,0};
double RADIUS = 25.0;

NPC::NPC(){
	position = makePosition();
	velocityx = makeVelocityx();
	velocityy = makeVelocityy();
	velocityz = makeVelocityz();
	climbingAbilityx = makeClimbingAbilityx();
	climbingAbilityy = makeClimbingAbilityy();
	climbingAbilityz = makeClimbingAbilityz();
}

PointVector<> NPC::makePosition(){
	srand(time(0));
	position.setdx(RADIUS + rand() % 50);
	position.setdy(RADIUS + rand() % 50);
	position.setdz(RADIUS + rand() % 50);

	return position;
}


double NPC::makeClimbingAbilityx(){
	return rand() % 40;
}


double NPC::makeClimbingAbilityy(){
	return rand() % 40;
}


double NPC::makeClimbingAbilityz(){
	return rand() % 40;
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
	int e = rand() % 30;
	return e == 1 ? 0 : 1;
}


int NPC::randomInt(){
	return rand() % 50;
}



PointVector<> NPC::updatePosition(double deltaT){
	
	double infinity = 1.0/0.0;
	
	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;

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

		
			static int p = PLACEHOLDER_LINE_OF_TRAVEL.size()-1;
			static int q = PLACEHOLDER_LINE_OF_TRAVEL.size()-1;
			static int r = PLACEHOLDER_LINE_OF_TRAVEL.size()-1;

		
			if(position.getdx() != PLACEHOLDER_LINE_OF_TRAVEL[p].getdx()){

				if(sx<climbingAbilityx){

					if((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + sx)) > 0){
						position.setdx(position.getdx() + sx);
					}
					
					else if((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + k*sx)) < 0){
						position.setdx(position.getdx() - sx);
					}
					
					else if((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + k*sx)) < 0){
						position.setdx(position.getdx() - k*sx);
					}

					else{
						position.setdx(PLACEHOLDER_LINE_OF_TRAVEL[p].getdx());

					}
				}
		
				else{
					position.setdx(position.getdx());	
				}
			
			}
			
			else{
				position.setdx(position.getdx());

				if((p)<PLACEHOLDER_LINE_OF_TRAVEL.size()){
					if(p>=1){
						p--;
					}

				}
			}
			
			
			if(position.getdy() != PLACEHOLDER_LINE_OF_TRAVEL[q].getdy()){

				if(sy<climbingAbilityy){

					if((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + sy)) > 0){
						position.setdy(position.getdy() + sy);
					}

					else if((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + sy)) < 0){
						position.setdy(position.getdy() - sy);
					}

					else if((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + k*sy)) < 0){
						position.setdy(position.getdy() - k*sy);
					}

					else{
						position.setdy(PLACEHOLDER_LINE_OF_TRAVEL[q].getdy());
					}
				}
		
				else{
					position.setdy(position.getdy());	
				}
			
			}
			
			else{
				position.setdy(position.getdy());

				if((q)<PLACEHOLDER_LINE_OF_TRAVEL.size()){
					if(q>=1){
						q--;
					}

				}
			}			
		
		
			if(position.getdz() != PLACEHOLDER_LINE_OF_TRAVEL[r].getdz()){

				if(sz<climbingAbilityz){

					if((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + k*sz)) > 0){
						position.setdz(position.getdz() + sz);
					}

					else if((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + sz)) < 0){
						position.setdz(position.getdz() - sz);
					}

					else if((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + k*sz)) < 0){
						position.setdz(position.getdz() - k*sz);
					}

					else{
						position.setdz(PLACEHOLDER_LINE_OF_TRAVEL[r].getdz());
						r++; 
					}
				}
		
				else{
					position.setdz(position.getdz());	
				}
			
			}
			
			else{
				position.setdz(position.getdz());

				if((r)<PLACEHOLDER_LINE_OF_TRAVEL.size()){
					if(r>=1){
						r--;
					}

				}
			}

	return position;
}

