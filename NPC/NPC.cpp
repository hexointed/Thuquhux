#include "NPC.h"
#include "../Physics/Object.h"

std::vector<Geometry::Vector<>> PLACEHOLDER_LINE_OF_TRAVEL{};
//Geometry::Vector<> GRAVITY_CENTER{0, 0, 0};
double RADIUS;

NPC::NPC(){
	position =  makePosition();
	velocityx = 1;// makeVelocityx();
	velocityy = 1;//makeVelocityy();
	velocityz =  1;//makeVelocityz();
	climbingAbilityx = 1.1/0.0;// makeClimbingAbilityx();
	climbingAbilityy = 1.1/0.0;//makeClimbingAbilityy();
	climbingAbilityz =  1.1/0.0;//makeClimbingAbilityz();
	//make_physObject();
	p = 0;//PLACEHOLDER_LINE_OF_TRAVEL.size()-1;
	q = 0;//PLACEHOLDER_LINE_OF_TRAVEL.size()-1;
	r = 0;//PLACEHOLDER_LINE_OF_TRAVEL.size()-1;
}

Geometry::Vector<> NPC::makePosition(){
	srand(time(0));
	position[0] = RADIUS + rand() % 8;
	position[1] = RADIUS + rand() % 8;
	position[2] = RADIUS + rand() % 8;

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
	return rand() % 5;
}


int NPC::makeVelocityy(){
	return rand() % 5;
}


int NPC::makeVelocityz(){
	return rand() % 5;
}

int NPC::randomInt(){
	return rand() % 50;
}

/*void NPC::make_physObject(){
	Physics::Object::default_handler.NPCs.push_back(std::make_pair(*this,Physics::Object::create_return(0)));

}*/

Geometry::Vector<> NPC::updatePosition(double deltaT){
	
	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;

		/*if(GRAVITY_CENTER[0] > position[0]){
			climbingAbilityx = infinity;
		}
	
	
		if(GRAVITY_CENTER[1] > position[1]){
			climbingAbilityy = infinity;
		} 


		if(GRAVITY_CENTER[2] > position[2]){
			climbingAbilityz = infinity;
		}
*/
		
			if(position[0] != PLACEHOLDER_LINE_OF_TRAVEL[p][0]){

				if(sx<climbingAbilityx){

					if(((PLACEHOLDER_LINE_OF_TRAVEL[p][0] - (position[0] + sx)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[p][0] - position[0] >0){
						position[0] = position[0] + sx;
					}
					
					else if(((PLACEHOLDER_LINE_OF_TRAVEL[p][0] - (position[0] + sx)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[p][0] - position[0] <0){
						position[0] = position[0] - sx;
					}
					

					else{
						position[0] = PLACEHOLDER_LINE_OF_TRAVEL[p][0];

					}
				}
		
				else{
					position[0] = position[0];	
				}
			
			}
			
			else{
				position[0] = position[0];

				if((p)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						p++;
					

				}
			}
			
			
			if(position[1] != PLACEHOLDER_LINE_OF_TRAVEL[q][1]){

				if(sy<climbingAbilityy){

					if(((PLACEHOLDER_LINE_OF_TRAVEL[q][1] - (position[1] + sy)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[q][1] - position[1] >0){
						position[1] = position[1] + sy;
					}

					else if(((PLACEHOLDER_LINE_OF_TRAVEL[q][1] - (position[1] + sy)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[q][1] - position[1] <0){
						position[1] = position[1] - sy;
					}

					else{
						position[1] = PLACEHOLDER_LINE_OF_TRAVEL[q][1];
					}
				}
		
				else{
					position[1] = position[1];	
				}
			
			}
			
			else{
				position[1] = position[1];

				if((q)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						q++;
					

				}
			}			
		
		
			if(position[2] != PLACEHOLDER_LINE_OF_TRAVEL[r][2]){

				if(sz<climbingAbilityz){

					if(((PLACEHOLDER_LINE_OF_TRAVEL[r][2] - (position[2] + sz)) > 0) && PLACEHOLDER_LINE_OF_TRAVEL[r][2] - position[2] >0){
						position[2] = position[2] + sz;
					}

					else if(((PLACEHOLDER_LINE_OF_TRAVEL[r][2] - (position[2] + sz)) < 0) && PLACEHOLDER_LINE_OF_TRAVEL[r][2] - position[2] <0){
						position[2] = position[2] - sz;
					}


					else{
						position[2] = PLACEHOLDER_LINE_OF_TRAVEL[r][2];
						r++; 
					}
				}
		
				else{
					position[2] = position[2];	
				}
			
			}
			
			else{
				position[2] = position[2];

				if((r)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						r++;
					

				}
			}


	return position;
}

