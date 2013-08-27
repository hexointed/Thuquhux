#include "NPC.h"
#include "PointVector.h"
#include <time.h>
#include "PhysObject.h"
#include <vector>

PointVector<> PLACEHOLDER_PLAYER_POSITION;
std::vector<PhysObject> PLACEHOLDER_STUFF;

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

double NPC::changePosition{

	while(position.getdx()>PLACEHOLDER_PLAYER_POSITION.getdx()){
		if(position.getdx()-PLACEHOLDER_STUFF.getdx() < 1){
			
} 		
		position.setdx(position.getdx()-1);
}

	while(position.getdy()>PLACEHOLDER_PLAYER_POSITION.getdy()){
		position.setdy(position.getdx()-1);
}

	while(position.getdz()>PLACEHOLDER_PLAYER_POSITION.getdz()){
		position.setdz(position.getdz()-1);
}

	while(position.getdx()<PLACEHOLDER_PLAYER_POSITION.getdx()){
		position.setdx(position.getdx()-1);
}

	while(position.getdy()<PLACEHOLDER_PLAYER_POSITION.getdy()){
		position.setdy(position.getdx()-1);
}

	while(position.getdz()<PLACEHOLDER_PLAYER_POSITION.getdz()){
		position.setdz(position.getdz()-1);
}



}
