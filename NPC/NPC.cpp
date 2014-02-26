#include "NPC.h"
#include "../Physics/PhysObject.h"

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
	PhysObject::default_handler.NPCs.push_back(std::make_pair(*this,PhysObject::create_return(0)));

}*/

Geometry::Vector<> NPC::updatePosition(double deltaT){
	
	double sx = deltaT*velocityx;
	double sy = deltaT*velocityy;
	double sz = deltaT*velocityz;

		/*if(GRAVITY_CENTER.getdx() > position.getdx()){
			climbingAbilityx = infinity;
		}
	
	
		if(GRAVITY_CENTER.getdy() > position.getdy()){
			climbingAbilityy = infinity;
		} 


		if(GRAVITY_CENTER.getdz() > position.getdz()){
			climbingAbilityz = infinity;
		}
*/
		
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

				if((p)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						p++;
					

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

				if((q)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						q++;
					

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

				if((r)<(signed)PLACEHOLDER_LINE_OF_TRAVEL.size()){
					
						r++;
					

				}
			}


	return position;
}

