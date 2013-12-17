/*
 * File: Physics.cpp
 * Author: Charles Gilljam
 *
 * Created on November 19, 2013, 12:21 PM
 */
#include "PhysHandler.h"
#include "PhysObject.h"
#include "../NPC/NPC.h"

PhysHandler::PhysHandler(){


}
PointVector<> collide_at(Parametric_Surface a, Parametric_Surface b){
	return a.position + (b.position - a.position)/2.0;
}

PointVector<> collision_normal(Parametric_Surface a, Parametric_Surface b){
	return 2.0*a.position - b.position;
}

void PhysHandler::handle(double time){
	
	for(PhysObject& i : physObjects){
		std::vector<int> to_delete;
		for(unsigned int j = 0; j < i.impulses().size() ; j++){
			if(i.impulses()[j].second <= time){
				i.accelerate(i.impulses()[j].first*time);
				to_delete.push_back(j);
			}else{
				i.accelerate(i.impulses()[j].first);
				i.impulses()[j].second = i.impulses()[j].second - time;
			}
		}

		//Removing impulses that have finished
		for(unsigned int j = 0; j < to_delete.size() ; j++){
			std::pair<PointVector<>, double> temp = i.impulses()[i.impulses().size()-1];
			i.impulses().back() = i.impulses()[to_delete[to_delete.size()-j-1]];
			i.impulses()[to_delete[to_delete.size()-j-1]] = temp;			
			i.impulses().pop_back();
		}
		i.previous_position() = i.position();
		i.position() = i.position() + i.velocity() * time + i.acceleration()*time*time / 2.0;
		i.velocity() = i.velocity() + i.acceleration() * time;
		i.acceleration() = PointVector<>{0,0,0};
		
		//i.surface().rotate(i.rotation().first, i.rotation().second*time);
	}

	for(unsigned int i = 0; i < physObjects.size() ; i++){
		for(unsigned int j = i+1 ; j < physObjects.size() ; j++){
			if(physObjects[i].surface().isIntersecting(physObjects[j].surface())){
				physObjects[i].position() = physObjects[i].previous_position();
				physObjects[j].position() = physObjects[j].previous_position();
				PhysObject::collision(physObjects[i], physObjects[j], collide_at(physObjects[i].surface(), physObjects[j].surface()), collision_normal(physObjects[i].surface(), physObjects[j].surface()));
			}
		}
	}
	
	for(std::pair<NPC, PhysObject>& i : NPCs){
		i.first.position = i.second.position();
		i.first.updatePosition(time);
		i.second.position() = i.first.position;
	}

}

void PhysHandler::addPhysObject(PhysObject a){
	physObjects.push_back(a);
}
