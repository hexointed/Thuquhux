#include "NPC.h"
#include "../Physics/PhysObject.h"

static PointVector<> PLACEHOLDER_PLAYER_POSITION{2, 1, 0};
static PointVector<> PLACEHOLDER_TMP{5,0,0};
static PointVector<> DDD{10,0,0};
std::vector<PointVector<>> PLACEHOLDER_LINE_OF_TRAVEL{DDD, PLACEHOLDER_PLAYER_POSITION, PLACEHOLDER_TMP};
PointVector<> GRAVITY_CENTER{};
double RADIUS;

NPC::NPC(){
	position = makePosition();
	velocityx = makeVelocityx();
	velocityy = makeVelocityy();
	velocityz = makeVelocityz();
	climbingAbilityx = makeClimbingAbilityx();
	climbingAbilityy = makeClimbingAbilityy();
	climbingAbilityz =  makeClimbingAbilityz();
	make_physObject();
}

PointVector<> NPC::makePosition(){
	srand(time(0));
	position.setdx(RADIUS + rand() % 8);
	position.setdy(RADIUS + rand() % 8);
	position.setdz(RADIUS + rand() % 8);

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

void NPC::make_physObject(){
	PhysObject::default_handler.NPCs.push_back(std::make_pair(*this,PhysObject::create_return(0)));

}

PointVector<> NPC::updatePosition(double deltaT){
	
	double infinity = 1.0/0.0;
	
	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;

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

					if(((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + sx)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - position.getdx() >0){
						position.setdx(position.getdx() + sx);
					}
					
					else if(((PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - (position.getdx() + sx)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[p].getdx() - position.getdx() <0){
						position.setdx(position.getdx() - sx);
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

					if(((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + sy)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - position.getdy() >0){
						position.setdy(position.getdy() + sy);
					}

					else if(((PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - (position.getdy() + sy)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[q].getdy() - position.getdy() <0){
						position.setdy(position.getdy() - sy);
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

					if(((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + sz)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - position.getdz() >0){
						position.setdz(position.getdz() + sz);
					}

					else if(((PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - (position.getdz() + sz)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[r].getdz() - position.getdz() <0){
						position.setdz(position.getdz() - sz);
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

