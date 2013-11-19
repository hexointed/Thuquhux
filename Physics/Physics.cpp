/*
 * File: Physics.cpp
 * Author: Charles Gilljam
 *
 * Created on November 19, 2013, 12:21 PM
 */


std::vector<PhysObject> physObjects;


void physics(double time){
	
	for(PhysObject i : physObjects){
		for(std::pair j : i.impulses()){
			if(j.second < time){
				i.accelerate(j.first/time)
			}else{
				i.accelerate(j.first);
				j.second = j.second - time;
			}
		}
		
		i.position() = i.position() + i.velocity() * time + i.acceleraion()*time^2 / 2
		i.velocity() = i.velocity() + i.acceleration() * time
		i.acceleration() = PointVector<>{0,0,0}

	}


}