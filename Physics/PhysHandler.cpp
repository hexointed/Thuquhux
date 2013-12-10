/*
 * File: Physics.cpp
 * Author: Charles Gilljam
 *
 * Created on November 19, 2013, 12:21 PM
 */
#include "PhysHandler.h"
#include "PhysObject.h"


PhysHandler::PhysHandler(){


}
PointVector<> collide_at(Parametric_Surface a, Parametric_Surface b){
	return a.position;
}

void PhysHandler::handle(double time){
	for(unsigned int i = 0; i < physObjects.size() ; i++){
		for(unsigned int j = i+1 ; j < physObjects.size() ; j++){
			if(physObjects[i].surface().isIntersecting(physObjects[j].surface())){
				PhysObject::collision(physObjects[i],physObjects[j], collide_at(physObjects[i].surface(),physObjects[j].surface()));
			}
		}
	}
	
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
		for(unsigned int j = 0; j < to_delete.size() ; j++){
			std::pair<PointVector<>, double> temp = i.impulses()[i.impulses().size()-1];
			i.impulses().back() = i.impulses()[to_delete[to_delete.size()-j-1]];
			i.impulses()[to_delete[to_delete.size()-j-1]] = temp;			
			i.impulses().pop_back();
		}
		
		i.position() = i.position() + i.velocity() * time + i.acceleration()*time*time / 2.0;
		i.velocity() = i.velocity() + i.acceleration() * time;
		i.acceleration() = PointVector<>{0,0,0};
		
		//i.surface().rotate(i.rotation().first, i.rotation().second*time);
	}


}

void PhysHandler::addPhysObject(PhysObject a){
	physObjects.push_back(a);
}
