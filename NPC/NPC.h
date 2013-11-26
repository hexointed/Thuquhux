#ifndef NPC_H
#define NPC_H

#include "../Geometry/PointVector.h"
#include <time.h>
#include "../Physics/PhysObject.h"
#include <vector>
#include <iostream>

class NPC{

public:

	NPC();
	PointVector<> updatePosition(double deltaT);
	PointVector<> position;
private:

	bool direction;
	bool randomBool(); /*NPC moving towards or away from player*/
	int randomInt();

	int velocityx;
	int velocityy;
	int velocityz;

	int makeVelocityx();
	int makeVelocityy();
	int makeVelocityz();

	double climbingAbilityx;
	double climbingAbilityy;
	double climbingAbilityz;

	double makeClimbingAbilityx();
	double makeClimbingAbilityy();
	double makeClimbingAbilityz();

	double getPosition(); 
	PointVector<> makePosition();

};

#endif /*NPC_H*/
