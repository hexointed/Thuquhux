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

void PhysHandler::handle(double time){
	for(unsigned int i = 0; i < physObjects.size() ; i++){
		for(unsigned int j = i+1 ; j < physObjects.size() ; j++){
			if(physObjects[i].surface().isIntersecting(physObjects[j].surface())){
				PhysObject::collision(physObjects[i],physObjects[j]);
			}
		}
	}
	
	for(PhysObject& i : physObjects){
		/*
		for(auto& j : i.impulses()){
			if(j.second < time){
				i.accelerate(j.first*time);
				j.second = -1.0;
			}else{
				i.accelerate(j.first);
				j.second = j.second - time;
			}
		}
		*/
		
		i.position() = i.position() + i.velocity() * time + i.acceleration()*time*time / 2.0;
		i.velocity() = i.velocity() + i.acceleration() * time;
		i.acceleration() = PointVector<>{0,0,2};
		
		i.surface().rotate(i.rotation().first, i.rotation().second*time);
	}


}

void PhysHandler::addPhysObject(PhysObject a){
	physObjects.push_back(a);
}
