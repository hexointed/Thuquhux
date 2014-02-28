#ifndef NPC_H
#define NPC_H

#include "../Geometry/Geometry.h"
#include <time.h>
#include <vector>
#include <iostream>

class NPC{

public:

	NPC();
	Geometry::Vector<> updatePosition(double deltaT);
	Geometry::Vector<> position;

private:

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

	int p;
	int q;
	int r;

	double getPosition(); 
	Geometry::Vector<> makePosition();

	void make_physObject();
};

#endif /*NPC_H*/
