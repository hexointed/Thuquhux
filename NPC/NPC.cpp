#include "NPC.h"

static PointVector<> PLACEHOLDER_PLAYER_POSITION{};
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
	return rand() % 11;
}


double NPC::climbingAbilityy(){
	return rand() % 11;
}


double NPC::climbingAbilityz(){
	return rand() % 11;
}


double NPC::velocityx(){
	return rand() % 30;
}


double NPC::velocityy(){
	return rand() % 30;
}


double NPC::velocityz(){
	return rand() % 30;
}


bool randomBool(){
	return rand() % 2;
}


int NPC::randomInt(){
	return rand() % 50;
}


double NPC::updatePosition(double deltaT){
	
	double infinity = 1.0/0.0;

	double sx = deltaT*velocityx();
	double sy = deltaT*velocityy();
	double sz = deltaT*velocityz();


	if(randomInt() == 2){
		position.setdx(position.getdx());
		position.setdy(position.getdy());
		position.setdz(position.getdz());
 	}
	
	else{
		int k = randomBool() == 1 ? 1 : -1;

		if(GRAVITY_CENTER.getdx() > position.getdx()){
			CAx = infinity;
		}
	
	
		if(GRAVITY_CENTER.getdy() > position.getdy()){
			CAy = infinity;
		} 


		if(GRAVITY_CENTER.getdz() > position.getdz()){
			CAz = infinity;
		}

		for(;;){
			int p = 1;
			int q = 1;
			int r = 1;
		
			if(position.getdx() != PLACEHOLDER_LINE_OF_TRAVEL[p].getdx()){

				if(sx<CAx){

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
				p++;
			}
			
			
			if(position.getdy() != PLACEHOLDER_LINE_OF_TRAVEL[q].getdy()){

				if(sy<CAy){

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
				q++;
			}			
		
		
			if(position.getdz() != PLACEHOLDER_LINE_OF_TRAVEL[r].getdz()){

				if(sz<CAz){

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
				r++;
			}		
		
		
		}
		
		

	return position.getdx();
	return position.getdy();
	return position.getdz();
	}


