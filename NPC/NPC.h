#ifndef NPC_H
#define NPC_H

#include "NPC.h"
#include "../Geometry/PointVector.h"
#include <time.h>
#include "../Physics/PhysObject.h"
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES

class NPC{

public:

private:

	
	PointVector<> position;
	double CAx; //Climbing Ability
	double CAy;
	double CAz;
	
	bool randomBool(); /*NPC moving towards or away from player*/
	int randomInt();

	double velocityx();
	double velocityy();
	double velocityz();

	double climbingAbilityx();
	double climbingAbilityy();
	double climbingAbilityz();

	double getPosition(); 
	void makePosition();
	double updatePosition(double deltaT);
};

#endif /*NPC_H*/
